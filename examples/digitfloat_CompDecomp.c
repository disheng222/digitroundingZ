#include <stdio.h>
#include <stdlib.h>
#include <sz.h>
#include <rw.h>
#include <bitshuffle.h>
#include "libdround.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
	size_t r5=0,r4=0,r3=0,r2=0,r1=0, i = 0;
	char outDir[640], oriFilePath[640], outputFilePath[640];
 	int prec;

  	if(argc < 3)
  	{
        printf("Test case: digitfloat_CompDecomp [precision] [srcFilePath] [dimension size]\n");
        printf("Example: digitfloat_CompDecomp 1 testdata/x86/testfloat_8_8_128.dat 8192\n");
        exit(0);
  	}

  	prec = atoi(argv[1]);

  	sprintf(oriFilePath, "%s", argv[2]);
	if(argc>=3)
		r1 = atoi(argv[3]); //8

	size_t nbEle = 0;
	int status = 0;
	float* data = readFloatData(oriFilePath, &nbEle, &status);
	if(nbEle != computeDataLength(r5,r4,r3,r2,r1))
	{
		printf("invalid size or dimension\n");
		return 1;
	}
	size_t block_size = bshuf_default_block_size(nbEle);


	//start compress: the entireu compression includes three steps: digit rounding + bit shuffle + zlib

	//step 1: call digit rounding
	dround_on_flt((void**)&data, nbEle*sizeof(float), prec);
	
	//step 2: call bit shuffle
	char* bitshuffle_compressed = (char*)malloc(nbEle*sizeof(float));
	bshuf_bitshuffle((char*)data, bitshuffle_compressed, nbEle, sizeof(float), block_size);

	//step 3: call zlib (i.e., deflate)
	unsigned char* compressBytes = (unsigned char*)malloc(nbEle*sizeof(float));
	unsigned long outSize = zlib_compress3((unsigned char*)bitshuffle_compressed, nbEle*sizeof(float), compressBytes, 3);

	//start decompress: just need to decompress by zlib + bit unshuffle
	unsigned char* out = NULL;

	zlib_uncompress5(compressBytes, outSize, &out, nbEle*sizeof(float));

	//TODO: call bit unshuffle --> unsigned char* out2
	float* bitshuffle_decompressed = (float*)malloc(nbEle*sizeof(float));
	bshuf_bitunshuffle((char*)out, bitshuffle_decompressed, nbEle, sizeof(float),
                    block_size);

	//free memory
	free(data);
	free(compressBytes);
	free(bitshuffle_compressed);
}
