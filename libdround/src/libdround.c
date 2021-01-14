/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "libdround.h"
#include <stdlib.h>
#include <string.h>


#define LOG2_10		   3.321928095		// log2(10)
#define LOG10_2		   0.301029996		// log10(2)

#define SIGN(x)		( (x<0) ? -1 : 1 )

int dataEndianType; //*endian type of the data read from disk
int sysEndianType; //*sysEndianType is actually set automatically.

const float TABLE[5][2] = {
  {0.6, -LOG10_2},
  {0.7,-0.221848749},
  {0.8,-0.154901959},
  {0.9,-0.096910013},
  {1.0,-0.045757490},
};

/*
 * Round the float value keeping nsd significant digits.
 * Fast method that does not uses log10() function.
 */
double droundFast(double v, int nsd)
{
	// compute the number of digits before the decimal point of the input floating-point value v
	// The value v is interpreted as v = 10^d + eps = 2^e + m
	// with 0 <= m < 0.5
	int e;
	double m = frexp(v, &e);	// return the binary exponent e of the input value v = 2^e + m with 0 <= m < 0.5

	// =============
	// --- tabulated method ---
	// tabulate the LOG10(m)
	int i = 0;
	while (TABLE[i][0] < m)
	  {
	    i++;
	  }
	float log10m = TABLE[i][1];
	
	// --- low precision method ---
	// float log10m = -LOG10_2;
	// =============

	// convert the binary exponent to a number of digits: d = floor(e*log10(2) + log10(m)) + 1
	int d = (int) floor(e*LOG10_2 + log10m) + 1;

	// compute the power of the quantization step: q = 2^p
	int p = (int) floor(LOG2_10 * (d - nsd));
	// compute quantization step: q = 2^p
	double q = ldexp(1, p);

	// apply the quantization step depending on the bias
	return SIGN(v) * (floor(fabs(v) / q) + 0.5) * q;
}

// Apply dround filter on a buffer of float values
void dround_on_flt(void **buf, size_t nbytes, int nsd)
{
        // cast the input buffer to float
        float * buf_flt = (float *) *buf;

        // round the data values
        for (size_t i = 0; i < nbytes / sizeof(float); i++)
                buf_flt[i] = (float) droundFast((double) buf_flt[i], nsd);

}


// Apply dround filter on a buffer of double values
void dround_on_dbl(void **buf, size_t nbytes, int nsd)
{
        // cast the input buffer to double
        double * buf_dbl = (double *) *buf;

        // round the data values
        for (size_t i = 0; i < nbytes / sizeof(double); i++)
                buf_dbl[i] = droundFast(buf_dbl[i], nsd);
}


void SHUF(unsigned char* data, unsigned char* shuf_compressed, size_t nbEle, int bytesoftype)
{
    void *dest = shuf_compressed;          /* Buffer to deposit [un]shuffled bytes into */
    unsigned char *_src=NULL;   /* Alias for source buffer */
    unsigned char *_dest=NULL;  /* Alias for destination buffer */
    size_t numofelements = nbEle;       /* Number of elements in buffer */
    size_t i;                   /* Local index variables */
    size_t leftover;            /* Extra bytes at end of buffer */
	size_t nbytes = nbEle*bytesoftype;
	if(bytesoftype > 1 && numofelements > 1)
	{
		/* Compute the leftover bytes if there are any */
		leftover = nbytes % bytesoftype;
		/* Get the pointer to the destination buffer */
		_dest =(unsigned char *)dest;

		/* Output; shuffle */
		for(i=0; i<bytesoftype; i++) {
			_src=data+i;
#define DUFF_GUTS                               \
    *_dest++=*_src;                             \
    _src+=bytesoftype;
		{
			size_t duffs_index; /* Counting index for Duff's device */

			duffs_index = (numofelements + 7) / 8;
			switch (numofelements % 8) {
				default:
					printf("This Should never be executed!\n");
					break;
				case 0:
					do
					  {
						DUFF_GUTS
				case 7:
						DUFF_GUTS
				case 6:
						DUFF_GUTS
				case 5:
						DUFF_GUTS
				case 4:
						DUFF_GUTS
				case 3:
						DUFF_GUTS
				case 2:
						DUFF_GUTS
				case 1:
						DUFF_GUTS
				  } while (--duffs_index > 0);
			} /* end switch */
		}
#undef DUFF_GUTS		
		}//end for	
		if(leftover>0) {
			/* Adjust back to end of shuffled bytes */
			_src -= (bytesoftype - 1);      /*lint !e794 _src is initialized */
			memcpy(_dest, _src, leftover);
		}
	}
}

void reverseSHUF(unsigned char* bytes, unsigned char* shuf_decompressed, size_t nbEle, int bytesoftype)
{
    void *dest = shuf_decompressed;          /* Buffer to deposit [un]shuffled bytes into */
    unsigned char *_src=bytes;   /* Alias for source buffer */
    unsigned char *_dest=NULL;  /* Alias for destination buffer */
    size_t numofelements = nbEle;       /* Number of elements in buffer */
    size_t i;                   /* Local index variables */
    size_t leftover;            /* Extra bytes at end of buffer */
	size_t nbytes = nbEle*bytesoftype;
	if(bytesoftype > 1 && numofelements > 1)
	{
		/* Compute the leftover bytes if there are any */
		leftover = nbytes % bytesoftype;
		for(i=0; i<bytesoftype; i++) {
			_dest = ((unsigned char *)dest)+i;
#define DUFF_GUTS                                                      \
    *_dest=*_src++;                                                    \
    _dest+=bytesoftype;
		{
			size_t duffs_index; /* Counting index for Duff's device */

			duffs_index = (numofelements + 7) / 8;
			switch (numofelements % 8) {
				default:
					printf("This Should never be executed!\n");
					break;
				case 0:
					do
					  {
						DUFF_GUTS
				case 7:
						DUFF_GUTS
				case 6:
						DUFF_GUTS
				case 5:
						DUFF_GUTS
				case 4:
						DUFF_GUTS
				case 3:
						DUFF_GUTS
				case 2:
						DUFF_GUTS
				case 1:
						DUFF_GUTS
				  } while (--duffs_index > 0);
			} /* end switch */
		}
#undef DUFF_GUTS    
		} //end for
		/* Add leftover to the end of data */
		if(leftover>0) {
			/* Adjust back to end of shuffled bytes */
			_dest -= (bytesoftype - 1);     /*lint !e794 _dest is initialized */
			memcpy(_dest, _src, leftover);
		}	
	}
}


unsigned char* dround_compress(int DATA_TYPE, void* data, size_t nbEle, int prec, unsigned long* outSize)
{
	if(DATA_TYPE == DIGIT_FLOAT)
	{
		float* data_copy = (float*)malloc(sizeof(float)*nbEle);
		memcpy(data_copy, data, sizeof(float)*nbEle);
		//call digit rounding
		dround_on_flt((void**)&data_copy, nbEle*sizeof(float), prec);
	
		//step 2: call bit shuffle
		unsigned char* bitshuffle_compressed = (unsigned char*)malloc(nbEle*sizeof(float));
		SHUF((unsigned char*)data_copy, bitshuffle_compressed, nbEle, sizeof(float));

		//step 3: call zlib (i.e., deflate)
		unsigned char* compressBytes = (unsigned char*)malloc(nbEle*sizeof(float));
		*outSize = zlib_compress3((unsigned char*)bitshuffle_compressed, nbEle*sizeof(float), compressBytes, 3);
		free(bitshuffle_compressed);
		free(data_copy);
		return compressBytes;
	}
	else if(DATA_TYPE == DIGIT_DOUBLE)
	{
		double* data_copy = (double*)malloc(sizeof(double)*nbEle);
		memcpy(data_copy, data, sizeof(double)*nbEle);

		//call digit rounding
		dround_on_flt((void**)&data_copy, nbEle*sizeof(double), prec);
	
		//step 2: call bit shuffle
		unsigned char* bitshuffle_compressed = (unsigned char*)malloc(nbEle*sizeof(double));
		SHUF((unsigned char*)data_copy, bitshuffle_compressed, nbEle, sizeof(double));

		//step 3: call zlib (i.e., deflate)
		unsigned char* compressBytes = (unsigned char*)malloc(nbEle*sizeof(double));
		*outSize = zlib_compress3((unsigned char*)bitshuffle_compressed, nbEle*sizeof(double), compressBytes, 3);
		free(bitshuffle_compressed);
		free(data_copy);
		return compressBytes;
	}
	else
	{
		return NULL;
	}

}

//DATA_TYPE == 0 means float, ==1 means double
void* dround_decompress(int DATA_TYPE, unsigned char* bytes, size_t nbEle, unsigned long outSize)
{
	if(DATA_TYPE == DIGIT_FLOAT)
	{
		//start decompress: just need to decompress by zlib + bit unshuffle
		unsigned char* out = NULL;

		zlib_uncompress5(bytes, outSize, &out, nbEle*sizeof(float));

		//TODO: call bit unshuffle --> unsigned char* out2
		float* bitshuffle_decompressed = (float*)malloc(nbEle*sizeof(float));
		reverseSHUF(out, (unsigned char*)bitshuffle_decompressed, nbEle, sizeof(float));

		return bitshuffle_decompressed;
	}
	else if(DATA_TYPE == DIGIT_DOUBLE)
	{
		//start decompress: just need to decompress by zlib + bit unshuffle
		unsigned char* out = NULL;

		zlib_uncompress5(bytes, outSize, &out, nbEle*sizeof(double));

		//TODO: call bit unshuffle --> unsigned char* out2
		double* bitshuffle_decompressed = (double*)malloc(nbEle*sizeof(double));
		reverseSHUF(out, (unsigned char*)bitshuffle_decompressed, nbEle, sizeof(double));

		return bitshuffle_decompressed;
	}
	else
	{
		return NULL;
	}
}
