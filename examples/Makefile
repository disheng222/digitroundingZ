## * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
##   Makefile to compile digit rounding example code.

##   PLEASE SET THIS VARIABLE BEFORE COMPILING
droundPATH	= $(abspath ../libdround)
szPATH		= /home/sdi/Install/sz-2.1.8-install
##   COMPILERS
CC		= gcc

##   FLAGS
# Compiling using shared library
droundFLAG 	= -I$(droundPATH)/include -ldround -L$(droundPATH) -lm -Wl,-rpath,$(droundPATH)
szFLAG		= -I$(szPATH)/include -lSZ -lzlib -lzstd -L$(szPATH)/lib -Wl,-rpath,$(szPATH)/lib

##   TARGETS
all: 		digitfloat_CompDecomp

digitfloat_CompDecomp:	digitfloat_CompDecomp.c
	$(CC)  -g -O3 -o digitfloat_CompDecomp digitfloat_CompDecomp.c  $(droundFLAG) $(szFLAG)

clean:
	rm -f digitfloat_CompDecomp

