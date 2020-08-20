/**
 *  @file callZlib.c
 *  @author Sheng Di
 *  @date June, 2016
 *  @brief gzip compressor code: the interface to call zlib
 *  (C) 2016 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */


#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include "callZlib.h"

#if MAX_MEM_LEVEL >= 8
#define DEF_MEM_LEVEL 8
#else
#define DEF_MEM_LEVEL MAX_MEM_LEVEL
#endif


#define CHECK_ERR(err, msg) { \
    if (err != Z_OK && err != Z_STREAM_END) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        return DROUND_NSCS; \
    } \
}

int isZlibFormat(unsigned char magic1, unsigned char magic2)
{
	if(magic1==104&&magic2==5) //DC+BS
		return 1;
	if(magic1==104&&magic2==129) //DC+DC
		return 1;
	if(magic1==104&&magic2==222) //DC+BC
		return 1;		
	if(magic1==120&&magic2==1) //BC+BS
		return 1;
	if(magic1==120&&magic2==94) //BC+? 
		return 1;		
	if(magic1==120&&magic2==156) //BC+DC
		return 1;
	if(magic1==120&&magic2==218) //BC+BS
		return 1;
	return 0;
}

unsigned long zlib_compress3(unsigned char* data, unsigned long dataLength, unsigned char* compressBytes, int level)
{
        unsigned long outSize = 0;

        z_stream stream = {0};
    int err;

    stream.next_in = data;
    stream.avail_in = dataLength;
#ifdef MAXSEG_64K
    /* Check for source > 64K on 16-bit machine: */
    if ((uLong)stream.avail_in != dataLength) return Z_BUF_ERROR;
#endif

    stream.next_out = compressBytes;
    stream.avail_out = dataLength;
    stream.zalloc = (alloc_func)0;
    stream.zfree = (free_func)0;
    stream.opaque = (voidpf)0;

    //err = deflateInit(&stream, level); //default  windowBits == 15.
    int windowBits = 14; //8-15

    err = deflateInit2(&stream, level, Z_DEFLATED, windowBits, DEF_MEM_LEVEL,
                         Z_DEFAULT_STRATEGY);//Z_FIXED); //Z_DEFAULT_STRATEGY
    if (err != Z_OK) return err;

    err = deflate(&stream, Z_FINISH);
    if (err != Z_STREAM_END) {
        deflateEnd(&stream);
        return err == Z_OK ? Z_BUF_ERROR : err;
    }

    err = deflateEnd(&stream);

    outSize = stream.total_out;
    return outSize;
}


unsigned long zlib_compress5(unsigned char* data, unsigned long dataLength, unsigned char** compressBytes, int level)
{
	int ret, flush;
	unsigned have;
	z_stream strm;
	unsigned char* in = data;

	/* allocate deflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit(&strm, level);
	//int windowBits = 15;
    //ret = deflateInit2(&strm, level, Z_DEFLATED, windowBits, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY);//Z_FIXED); //Z_DEFAULT_STRATEGY

	if (ret != Z_OK)
		return ret;

	size_t p_size = 0, av_in = 0;
    uLong estCmpLen = deflateBound(&strm, dataLength);
   	*compressBytes = (unsigned char*)malloc(sizeof(unsigned char)*estCmpLen);	
	unsigned char* out = *compressBytes; 

	/* compress until end of file */
	do {		
		p_size += DROUND_ZLIB_BUFFER_SIZE;
		if(p_size>=dataLength)
		{
			av_in = dataLength - (p_size - DROUND_ZLIB_BUFFER_SIZE);
			flush = Z_FINISH;
		}
		else
		{
			av_in = DROUND_ZLIB_BUFFER_SIZE;
			flush = Z_NO_FLUSH;
		}
		strm.avail_in = av_in;
		strm.next_in = in;

		/* run deflate() on input until output buffer not full, finish
		   compression if all of source has been read in */
		do {
			strm.avail_out = DROUND_ZLIB_BUFFER_SIZE;
			strm.next_out = out;
			ret = deflate(&strm, flush);    /* no bad return value */

			have = DROUND_ZLIB_BUFFER_SIZE - strm.avail_out;
			out += have;
		} while (strm.avail_out == 0);

		in+=av_in;

		/* done when last data in file processed */
	} while (flush != Z_FINISH);

	/* clean up and return */
	(void)deflateEnd(&strm);	
	
	return strm.total_out;	
}

unsigned long zlib_uncompress5(unsigned char* compressBytes, unsigned long cmpSize, unsigned char** oriData, unsigned long targetOriSize)
{
	int err;
	z_stream d_stream = {0}; /* decompression stream */

	*oriData = (unsigned char*)malloc(sizeof(unsigned char)*targetOriSize);		

    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;

	d_stream.next_in  = compressBytes;
	d_stream.avail_in = 0;
	d_stream.next_out = *oriData;

	err = inflateInit(&d_stream);
	CHECK_ERR(err, "inflateInit");

	while (d_stream.total_out < targetOriSize && d_stream.total_in < cmpSize) {
		d_stream.avail_in = d_stream.avail_out = DROUND_ZLIB_BUFFER_SIZE; /* force small buffers */
		//err = inflate(&d_stream, Z_NO_FLUSH);
		err = inflate(&d_stream, Z_SYNC_FLUSH);
		if (err == Z_STREAM_END) break;
		CHECK_ERR(err, "inflate");
	}
	
	err = inflateEnd(&d_stream);
	
	CHECK_ERR(err, "inflateEnd");

	return d_stream.total_out;
}
