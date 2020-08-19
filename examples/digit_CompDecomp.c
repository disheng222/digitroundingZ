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
        printf("Test case: digitfloat_CompDecomp [data type] [precision] [srcFilePath] [dimension size]\n");
        printf("Example: digitfloat_CompDecomp 1 testdata/x86/testfloat_8_8_128.dat 8192\n");
        exit(0);
  	}

  	char* type = argv[1];
  	prec = atoi(argv[2]);

  	sprintf(oriFilePath, "%s", argv[3]);
	if(argc>=3)
		r1 = atoi(argv[4]); //8

	size_t nbEle = 0;
	int status = 0;
	float* data = readFloatData(oriFilePath, &nbEle, &status);
	if(nbEle != computeDataLength(r5,r4,r3,r2,r1))
	{
		printf("invalid size or dimension\n");
		return 1;
	}
	size_t block_size = bshuf_default_block_size(nbEle);
	for(i=0;i<10;i++)
		printf("data[%d]=%f\n", i, data[i]);	
	SZ_Init(NULL);
	//start compress: the entireu compression includes three steps: digit rounding + bit shuffle + zlib
	unsigned long outSize = 0;
	float* out = NULL;
	if(strcmp(type, "-f")==0)
	{
		unsigned char* compressBytes = dround_compress(DIGIT_FLOAT, data, nbEle, prec, &outSize);
		out = dround_decompress(DIGIT_FLOAT, compressBytes, nbEle, outSize);
		out = (float*)out;
	}
	else if(strcmp(type, "-d")==0)
	{
		unsigned char* compressBytes = dround_compress(DIGIT_DOUBLE, data, nbEle, prec, &outSize);
		out = dround_decompress(DIGIT_DOUBLE, compressBytes, nbEle, outSize);
		out = (double*)out;
	}
	

	for(i=0;i<10;i++)
		printf("out[%d]=%f\n", i, out[i]);	
	// //free memory
	free(data);
	free(out);
}
