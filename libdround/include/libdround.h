/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is COPYINGd under MIT-style COPYING (found in the
 * COPYING file in the root directory of this source tree).
 */


#ifndef LIBDROUND_H_
#define LIBDROUND_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "defines.h"
#include "callZlib.h"

#define DIGIT_FLOAT    0
#define DIGIT_DOUBLE   1
extern int prec_user_defined;

typedef union lint16
{
        unsigned short usvalue;
        short svalue;
        unsigned char byte[2];
} lint16;

typedef union lint32
{
        int ivalue;
        unsigned int uivalue;
        unsigned char byte[4];
} lint32;

typedef union lint64
{
        long lvalue;
        unsigned long ulvalue;
        unsigned char byte[8];
} lint64;

typedef union ldouble
{
    double value;
    unsigned long lvalue;
    unsigned char byte[8];
} ldouble;

typedef union lfloat
{
    float value;
    unsigned int ivalue;
    unsigned char byte[4];
} lfloat;

extern int dataEndianType; //*endian type of the data read from disk
extern int sysEndianType; //*sysEndianType is actually set automatically.

/*
 * Round the float value keeping nsd significant digits. Fast computation method.
 *
 * The fast method uses an approximation of the number of digit before the floating point
 * instead of using log10() function.
 *
 */
double droundFast(double v, int nsd);
void dround_on_flt(void **buf, size_t nbytes, int nsd);
void dround_on_dbl(void **buf, size_t nbytes, int nsd);

unsigned char* dround_compress_libpressio(int DATA_TYPE, void* data, size_t nbEle, unsigned long* outSize);
unsigned char* dround_compress(int DATA_TYPE, void* data, size_t nbEle, int prec, unsigned long* outSize);
void* dround_decompress(int DATA_TYPE, unsigned char* bytes, size_t nbEle, unsigned long outSize);

#ifdef __cplusplus
}
#endif


#endif /* LIBDROUND_H_ */
