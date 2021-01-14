#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libdround.h>
#include <rw.h>
#include "libdround.h"

int main(int argc, char* argv[])
{
	char oriFilePath[640], cmpFile[640], outputFilePath[640];
 	int prec;

  	if(argc < 3)
  	{
        printf("Test case: digitfloat_CompDecomp [data type] [precision] [srcFilePath]\n");
        printf("Example: digitfloat_CompDecomp -f 1 testdata/x86/testfloat_8_8_128.dat\n");
        exit(0);
  	}

  	char* type = argv[1];
  	prec = atoi(argv[2]);

  	sprintf(oriFilePath, "%s", argv[3]);
	sprintf(cmpFile, "%s.dg", oriFilePath);
	sprintf(outputFilePath, "%s.dg.out", oriFilePath);

	size_t nbEle = 0;
	int status = 0;
	float* data = readFloatData(oriFilePath, &nbEle, &status);
	//for(i=0;i<10;i++)
	//	printf("data[%d]=%f\n", i, data[i]);	
	//start compress: the entireu compression includes three steps: digit rounding + bit shuffle + zlib
	unsigned long outSize = 0;
	void* out = NULL;
	if(strcmp(type, "-f")==0)
	{
		unsigned char* compressBytes = dround_compress(DROUND_FLOAT, data, nbEle, prec, &outSize);
		writeByteData(compressBytes, outSize, cmpFile, &status);
		out = dround_decompress(DROUND_FLOAT, compressBytes, nbEle, outSize);
		writeFloatData_inBytes(out, nbEle, outputFilePath, &status);
	}
	else if(strcmp(type, "-d")==0)
	{
		unsigned char* compressBytes = dround_compress(DROUND_DOUBLE, data, nbEle, prec, &outSize);
		writeByteData(compressBytes, outSize, cmpFile, &status);
		out = dround_decompress(DROUND_DOUBLE, compressBytes, nbEle, outSize);
		writeDoubleData_inBytes(out, nbEle, outputFilePath, &status);
	}


	
	//for(i=0;i<10;i++)
	//	printf("out[%d]=%f\n", i, out[i]);	
	// //free memory
	free(data);
	free(out);
}
