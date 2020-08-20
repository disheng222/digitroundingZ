AUTOMAKE_OPTIONS=foreign
AM_CFLAGS = -I../libdround/include -I../zlib

bin_PROGRAMS=digit_CompDecomp

digit_CompDecomp_SOURCES=digit_CompDecomp.c
digit_CompDecomp_LDADD=../libdround/.libs/libdround.a ../zlib/.libs/libzlib.a -lm
