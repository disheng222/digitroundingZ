#!/bin/bash

aclocal
libtoolize -f -c
autoconf
autoheader
automake -a
