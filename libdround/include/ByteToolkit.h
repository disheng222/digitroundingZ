/**
 *  @file ByteToolkit.h
 *  @author Sheng Di
 *  @date July, 2017
 *  @brief Header file for the ByteToolkit.c.
 *  (C) 2016 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#ifndef _ByteToolkit_H
#define _ByteToolkit_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

//ByteToolkit.c

unsigned short bytesToUInt16_bigEndian(unsigned char* bytes);
unsigned int bytesToUInt32_bigEndian(unsigned char* bytes);
unsigned long bytesToUInt64_bigEndian(unsigned char* b);

short bytesToInt16_bigEndian(unsigned char* bytes);
int bytesToInt32_bigEndian(unsigned char* bytes);
long bytesToInt64_bigEndian(unsigned char* b);
int bytesToInt_bigEndian(unsigned char* bytes);

void intToBytes_bigEndian(unsigned char *b, unsigned int num);

void int64ToBytes_bigEndian(unsigned char *b, uint64_t num);
void int32ToBytes_bigEndian(unsigned char *b, uint32_t num);
void int16ToBytes_bigEndian(unsigned char *b, uint16_t num);

long bytesToLong_bigEndian(unsigned char* b);
void longToBytes_bigEndian(unsigned char *b, unsigned long num);
long doubleToOSEndianLong(double value);
int floatToOSEndianInt(float value);
short getExponent_float(float value);
short getExponent_double(double value);

short bytesToShort(unsigned char* bytes);
void shortToBytes(unsigned char* b, short value);
int bytesToInt(unsigned char* bytes);
long bytesToLong(unsigned char* bytes);

float bytesToFloat(unsigned char* bytes);
void floatToBytes(unsigned char *b, float num);

double bytesToDouble(unsigned char* bytes);
void doubleToBytes(unsigned char *b, double num);

short* convertByteDataToShortArray(unsigned char* bytes, size_t byteLength);
unsigned short* convertByteDataToUShortArray(unsigned char* bytes, size_t byteLength);

void convertShortArrayToBytes(short* states, size_t stateLength, unsigned char* bytes);
void convertUShortArrayToBytes(unsigned short* states, size_t stateLength, unsigned char* bytes);

void convertIntArrayToBytes(int* states, size_t stateLength, unsigned char* bytes);
void convertUIntArrayToBytes(unsigned int* states, size_t stateLength, unsigned char* bytes);
void convertLongArrayToBytes(int64_t* states, size_t stateLength, unsigned char* bytes);
void convertULongArrayToBytes(uint64_t* states, size_t stateLength, unsigned char* bytes);

size_t bytesToSize(unsigned char* bytes);
void sizeToBytes(unsigned char* outBytes, size_t size);

void symTransform_8bytes(unsigned char data[8]);
void symTransform_2bytes(unsigned char data[2]);
void symTransform_4bytes(unsigned char data[4]);

#ifdef __cplusplus
}
#endif

#endif /* ----- #ifndef _ByteToolkit_H  ----- */

