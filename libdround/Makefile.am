#AM_CFLAGS = -I./include -I../zlib
#LDFLAGS=-fPIC -shared

AUTOMAKE_OPTIONS=foreign
include_HEADERS=include/callZlib.h \
		 include/iochain.h  include/libdround.h  include/rw.h include/defines.h include/ByteToolkit.h

lib_LTLIBRARIES=libdround.la
libdround_la_CFLAGS=-I./include -I../zlib
libdround_la_LDFLAGS = -version-info  0:1:0
libdround_la_LIDADD=../zlib/.libs/libzlib.a
libdround_la_SOURCES=src/callZlib.c  src/iochain.c  src/libdround.c  src/rw.c src/ByteToolkit.c

libdround_la_LINK= $(AM_V_CC)$(LIBTOOL) --tag=CC --mode=link $(CCLD) $(libdround_la_CFLAGS) -O3 $(libdround_la_LDFLAGS) -o $(lib_LTLIBRARIES)

