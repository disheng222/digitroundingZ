/**
 *  @file ByteToolkit.c
 *  @author Sheng Di
 *  @date April, 2016
 *  @brief Byte Toolkit
 *  (C) 2016 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */
 
#include <stdlib.h>
#include "ByteToolkit.h"
#include "libdround.h" 	
#include "zlib.h"
#include <stdio.h>
#include <string.h>

inline unsigned short bytesToUInt16_bigEndian(unsigned char* bytes)
{
	int temp = 0;
	unsigned short res = 0;
	
	temp = bytes[0] & 0xff;
	res |= temp;	

	res <<= 8;
	temp = bytes[1] & 0xff;
	res |= temp;
	
	return res;
}	
	
inline unsigned int bytesToUInt32_bigEndian(unsigned char* bytes)
{
	unsigned int temp = 0;
	unsigned int res = 0;
	
	res <<= 8;
	temp = bytes[0] & 0xff;
	res |= temp;	

	res <<= 8;
	temp = bytes[1] & 0xff;
	res |= temp;

	res <<= 8;
	temp = bytes[2] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = bytes[3] & 0xff;
	res |= temp;
	
	return res;
}

inline unsigned long bytesToUInt64_bigEndian(unsigned char* b) {
	unsigned long temp = 0;
	unsigned long res = 0;

	res <<= 8;
	temp = b[0] & 0xff;
	res |= temp;

	res <<= 8;
	temp = b[1] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[2] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[3] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[4] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[5] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[6] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[7] & 0xff;
	res |= temp;						
	
	return res;
}
	
inline short bytesToInt16_bigEndian(unsigned char* bytes)
{
	int temp = 0;
	short res = 0;
	
	temp = bytes[0] & 0xff;
	res |= temp;	

	res <<= 8;
	temp = bytes[1] & 0xff;
	res |= temp;
	
	return res;
}	
	
inline int bytesToInt32_bigEndian(unsigned char* bytes)
{
	int temp = 0;
	int res = 0;
	
	res <<= 8;
	temp = bytes[0] & 0xff;
	res |= temp;	

	res <<= 8;
	temp = bytes[1] & 0xff;
	res |= temp;

	res <<= 8;
	temp = bytes[2] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = bytes[3] & 0xff;
	res |= temp;
	
	return res;
}

inline long bytesToInt64_bigEndian(unsigned char* b) {
	long temp = 0;
	long res = 0;

	res <<= 8;
	temp = b[0] & 0xff;
	res |= temp;

	res <<= 8;
	temp = b[1] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[2] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[3] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[4] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[5] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[6] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[7] & 0xff;
	res |= temp;						
	
	return res;
}

inline int bytesToInt_bigEndian(unsigned char* bytes)
{
	int temp = 0;
	int res = 0;
	
	res <<= 8;
	temp = bytes[0] & 0xff;
	res |= temp;	

	res <<= 8;
	temp = bytes[1] & 0xff;
	res |= temp;

	res <<= 8;
	temp = bytes[2] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = bytes[3] & 0xff;
	res |= temp;
	
	return res;
}

/**
 * @unsigned char *b the variable to store the converted bytes (length=4)
 * @unsigned int num
 * */
inline void intToBytes_bigEndian(unsigned char *b, unsigned int num)
{
	b[0] = (unsigned char)(num >> 24);	
	b[1] = (unsigned char)(num >> 16);	
	b[2] = (unsigned char)(num >> 8);	
	b[3] = (unsigned char)(num);	
	
	//note: num >> xxx already considered endian_type...
//if(dataEndianType==LITTLE_ENDIAN_DATA)
//		symTransform_4bytes(*b); //change to BIG_ENDIAN_DATA
}

inline void int64ToBytes_bigEndian(unsigned char *b, uint64_t num)
{
	b[0] = (unsigned char)(num>>56);
	b[1] = (unsigned char)(num>>48);
	b[2] = (unsigned char)(num>>40);
	b[3] = (unsigned char)(num>>32);
	b[4] = (unsigned char)(num>>24);
	b[5] = (unsigned char)(num>>16);
	b[6] = (unsigned char)(num>>8);
	b[7] = (unsigned char)(num);
}

inline void int32ToBytes_bigEndian(unsigned char *b, uint32_t num)
{
	b[0] = (unsigned char)(num >> 24);	
	b[1] = (unsigned char)(num >> 16);	
	b[2] = (unsigned char)(num >> 8);	
	b[3] = (unsigned char)(num);		
}

inline void int16ToBytes_bigEndian(unsigned char *b, uint16_t num)
{
	b[0] = (unsigned char)(num >> 8);	
	b[1] = (unsigned char)(num);
}

/**
 * @endianType: refers to the endian_type of unsigned char* b.
 * */
inline long bytesToLong_bigEndian(unsigned char* b) {
	long temp = 0;
	long res = 0;

	res <<= 8;
	temp = b[0] & 0xff;
	res |= temp;

	res <<= 8;
	temp = b[1] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[2] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[3] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[4] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[5] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[6] & 0xff;
	res |= temp;
	
	res <<= 8;
	temp = b[7] & 0xff;
	res |= temp;						
	
	return res;
}

inline void longToBytes_bigEndian(unsigned char *b, unsigned long num) 
{
	b[0] = (unsigned char)(num>>56);
	b[1] = (unsigned char)(num>>48);
	b[2] = (unsigned char)(num>>40);
	b[3] = (unsigned char)(num>>32);
	b[4] = (unsigned char)(num>>24);
	b[5] = (unsigned char)(num>>16);
	b[6] = (unsigned char)(num>>8);
	b[7] = (unsigned char)(num);
//	if(dataEndianType==LITTLE_ENDIAN_DATA)
//		symTransform_8bytes(*b);
}


inline long doubleToOSEndianLong(double value)
{
	ldouble buf;
	buf.value = value;
	return buf.lvalue;
}

inline int floatToOSEndianInt(float value)
{
	lfloat buf;
	buf.value = value;
	return buf.ivalue;
}

//TODO: debug: lfBuf.lvalue could be actually little_endian....
inline short getExponent_float(float value)
{
	//int ivalue = floatToBigEndianInt(value);

	lfloat lbuf;
	lbuf.value = value;
	int ivalue = lbuf.ivalue;
	
	int expValue = (ivalue & 0x7F800000) >> 23;
	expValue -= 127;
	return (short)expValue;
}

inline short getExponent_double(double value)
{
	//long lvalue = doubleToBigEndianLong(value);
	
	ldouble lbuf;
	lbuf.value = value;
	long lvalue = lbuf.lvalue;
	
	int expValue = (int)((lvalue & 0x7FF0000000000000) >> 52);
	expValue -= 1023;
	return (short)expValue;
}

/**
 * By default, the endian type is OS endian type.
 * */
short bytesToShort(unsigned char* bytes)
{
	lint16 buf;
	memcpy(buf.byte, bytes, 2);
	
	return buf.svalue;
}

void shortToBytes(unsigned char* b, short value)
{
	lint16 buf;
	buf.svalue = value;
	memcpy(b, buf.byte, 2);
}

int bytesToInt(unsigned char* bytes)
{
	lfloat buf;
	memcpy(buf.byte, bytes, 4);
	return buf.ivalue;
}

long bytesToLong(unsigned char* bytes)
{
	ldouble buf;
	memcpy(buf.byte, bytes, 8);
	return buf.lvalue;
}

//the byte to input is in the big-endian format
inline float bytesToFloat(unsigned char* bytes)
{
	lfloat buf;
	memcpy(buf.byte, bytes, 4);
	if(sysEndianType==LITTLE_ENDIAN_SYSTEM)
		symTransform_4bytes(buf.byte);	
	return buf.value;
}

inline void floatToBytes(unsigned char *b, float num)
{
	lfloat buf;
	buf.value = num;
	memcpy(b, buf.byte, 4);
	if(sysEndianType==LITTLE_ENDIAN_SYSTEM)
		symTransform_4bytes(b);		
}

//the byte to input is in the big-endian format
inline double bytesToDouble(unsigned char* bytes)
{
	ldouble buf;
	memcpy(buf.byte, bytes, 8);
	if(sysEndianType==LITTLE_ENDIAN_SYSTEM)
		symTransform_8bytes(buf.byte);
	return buf.value;
}

inline void doubleToBytes(unsigned char *b, double num)
{
	ldouble buf;
	buf.value = num;
	memcpy(b, buf.byte, 8);
	if(sysEndianType==LITTLE_ENDIAN_SYSTEM)
		symTransform_8bytes(b);
}

short* convertByteDataToShortArray(unsigned char* bytes, size_t byteLength)
{
	lint16 ls;
	size_t i, stateLength = byteLength/2;
	short* states = (short*)malloc(stateLength*sizeof(short));
	if(sysEndianType==dataEndianType)
	{	
		for(i=0;i<stateLength;i++)
		{
			ls.byte[0] = bytes[i*2];
			ls.byte[1] = bytes[i*2+1];
			states[i] = ls.svalue;
		}
	}
	else
	{
		for(i=0;i<stateLength;i++)
		{
			ls.byte[0] = bytes[i*2+1];
			ls.byte[1] = bytes[i*2];
			states[i] = ls.svalue;
		}		
	}
	return states;
} 

unsigned short* convertByteDataToUShortArray(unsigned char* bytes, size_t byteLength)
{
	lint16 ls;
	size_t i, stateLength = byteLength/2;
	unsigned short* states = (unsigned short*)malloc(stateLength*sizeof(unsigned short));
	if(sysEndianType==dataEndianType)
	{	
		for(i=0;i<stateLength;i++)
		{
			ls.byte[0] = bytes[i*2];
			ls.byte[1] = bytes[i*2+1];
			states[i] = ls.usvalue;
		}
	}
	else
	{
		for(i=0;i<stateLength;i++)
		{
			ls.byte[0] = bytes[i*2+1];
			ls.byte[1] = bytes[i*2];
			states[i] = ls.usvalue;
		}		
	}
	return states;
} 

void convertShortArrayToBytes(short* states, size_t stateLength, unsigned char* bytes)
{
	lint16 ls;
	size_t i;
	if(sysEndianType==dataEndianType)
	{
		for(i=0;i<stateLength;i++)
		{
			ls.svalue = states[i];
			bytes[i*2] = ls.byte[0];
			bytes[i*2+1] = ls.byte[1];
		}		
	}
	else
	{
		for(i=0;i<stateLength;i++)
		{
			ls.svalue = states[i];
			bytes[i*2] = ls.byte[1];
			bytes[i*2+1] = ls.byte[0];
		}			
	}
}

void convertUShortArrayToBytes(unsigned short* states, size_t stateLength, unsigned char* bytes)
{
	lint16 ls;
	size_t i;
	if(sysEndianType==dataEndianType)
	{
		for(i=0;i<stateLength;i++)
		{
			ls.usvalue = states[i];
			bytes[i*2] = ls.byte[0];
			bytes[i*2+1] = ls.byte[1];
		}		
	}
	else
	{
		for(i=0;i<stateLength;i++)
		{
			ls.usvalue = states[i];
			bytes[i*2] = ls.byte[1];
			bytes[i*2+1] = ls.byte[0];
		}			
	}
}

void convertIntArrayToBytes(int* states, size_t stateLength, unsigned char* bytes)
{
	lint32 ls;
	size_t index = 0;
	size_t i;
	if(sysEndianType==dataEndianType)
	{
		for(i=0;i<stateLength;i++)
		{
			index = i << 2; //==i*4
			ls.ivalue = states[i];
			bytes[index] = ls.byte[0];
			bytes[index+1] = ls.byte[1];
			bytes[index+2] = ls.byte[2];
			bytes[index+3] = ls.byte[3];
		}		
	}
	else
	{
		for(i=0;i<stateLength;i++)
		{
			index = i << 2; //==i*4
			ls.ivalue = states[i];
			bytes[index] = ls.byte[3];
			bytes[index+1] = ls.byte[2];
			bytes[index+2] = ls.byte[1];
			bytes[index+3] = ls.byte[0];
		}			
	}
}

void convertUIntArrayToBytes(unsigned int* states, size_t stateLength, unsigned char* bytes)
{
	lint32 ls;
	size_t index = 0;
	size_t i;
	if(sysEndianType==dataEndianType)
	{
		for(i=0;i<stateLength;i++)
		{
			index = i << 2; //==i*4
			ls.uivalue = states[i];
			bytes[index] = ls.byte[0];
			bytes[index+1] = ls.byte[1];
			bytes[index+2] = ls.byte[2];
			bytes[index+3] = ls.byte[3];
		}		
	}
	else
	{
		for(i=0;i<stateLength;i++)
		{
			index = i << 2; //==i*4
			ls.uivalue = states[i];
			bytes[index] = ls.byte[3];
			bytes[index+1] = ls.byte[2];
			bytes[index+2] = ls.byte[1];
			bytes[index+3] = ls.byte[0];
		}			
	}
}

void convertLongArrayToBytes(int64_t* states, size_t stateLength, unsigned char* bytes)
{
	lint64 ls;
	size_t index = 0;
	size_t i;
	if(sysEndianType==dataEndianType)
	{
		for(i=0;i<stateLength;i++)
		{
			index = i << 3; //==i*8
			ls.lvalue = states[i];
			bytes[index] = ls.byte[0];
			bytes[index+1] = ls.byte[1];
			bytes[index+2] = ls.byte[2];
			bytes[index+3] = ls.byte[3];
			bytes[index+4] = ls.byte[4];
			bytes[index+5] = ls.byte[5];
			bytes[index+6] = ls.byte[6];
			bytes[index+7] = ls.byte[7];	
		}		
	}
	else
	{
		for(i=0;i<stateLength;i++)
		{
			index = i << 3; //==i*8
			ls.lvalue = states[i];
			bytes[index] = ls.byte[7];
			bytes[index+1] = ls.byte[6];
			bytes[index+2] = ls.byte[5];
			bytes[index+3] = ls.byte[4];
			bytes[index+4] = ls.byte[3];
			bytes[index+5] = ls.byte[2];
			bytes[index+6] = ls.byte[1];
			bytes[index+7] = ls.byte[0];	
		}			
	}
}

void convertULongArrayToBytes(uint64_t* states, size_t stateLength, unsigned char* bytes)
{
	lint64 ls;
	size_t index = 0;
	size_t i;
	if(sysEndianType==dataEndianType)
	{
		for(i=0;i<stateLength;i++)
		{
			index = i << 3; //==i*8
			ls.ulvalue = states[i];
			bytes[index] = ls.byte[0];
			bytes[index+1] = ls.byte[1];
			bytes[index+2] = ls.byte[2];
			bytes[index+3] = ls.byte[3];
			bytes[index+4] = ls.byte[4];
			bytes[index+5] = ls.byte[5];
			bytes[index+6] = ls.byte[6];
			bytes[index+7] = ls.byte[7];			
		}		
	}
	else
	{
		for(i=0;i<stateLength;i++)
		{
			index = i << 3; //==i*8
			ls.ulvalue = states[i];
			bytes[index] = ls.byte[7];
			bytes[index+1] = ls.byte[6];
			bytes[index+2] = ls.byte[5];
			bytes[index+3] = ls.byte[4];
			bytes[index+4] = ls.byte[3];
			bytes[index+5] = ls.byte[2];
			bytes[index+6] = ls.byte[1];
			bytes[index+7] = ls.byte[0];	
		}			
	}
}


inline size_t bytesToSize(unsigned char* bytes)
{
	size_t result = 0;
	result = bytesToLong_bigEndian(bytes);//8	
	return result;
}

inline void sizeToBytes(unsigned char* outBytes, size_t size)
{
	longToBytes_bigEndian(outBytes, size);//8
}

void symTransform_8bytes(unsigned char data[8])
{
        unsigned char tmp = data[0];
        data[0] = data[7];
        data[7] = tmp;

        tmp = data[1];
        data[1] = data[6];
        data[6] = tmp;

        tmp = data[2];
        data[2] = data[5];
        data[5] = tmp;

        tmp = data[3];
        data[3] = data[4];
        data[4] = tmp;
}

inline void symTransform_2bytes(unsigned char data[2])
{
        unsigned char tmp = data[0];
        data[0] = data[1];
        data[1] = tmp;
}

inline void symTransform_4bytes(unsigned char data[4])
{
        unsigned char tmp = data[0];
        data[0] = data[3];
        data[3] = tmp;

        tmp = data[1];
        data[1] = data[2];
        data[2] = tmp;
}
