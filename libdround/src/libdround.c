/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define LOG2_10		3.321928095		// log2(10)
#define LOG10_2		0.301029996		// log10(2)

#define SIGN(x)		( (x<0) ? -1 : 1 )

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

unsigned char* dround_compress(int DATA_TYPE, void* data, size_t nbEle)
{

}

//DATA_TYPE == 0 means float, ==1 means double
void* dround_decompress(int DATA_TYPE, unsigned char* bytes, size_t nbEle)
{

}
