#
# Makefile
#
# Author: Thales
# Copyright CNES 2018
#
#
# Copyright (c) 2019, CNES.
#
# This source code is licensed under MIT-style license (found in the
# COPYING file in the root directory of this source tree).
#

# Requirements:
# - HDF5_PATH should point on the installation path of HDF5
# - HDF5_PLUGIN_PATH should point on the location where the plugin shall be installed 

# Tips:
#
# Run the following command to see all messages:
#
# 	make test DEBUG=1
#

LDPATH = $(PWD)/libdround

CC = gcc
CFLAGS = -fPIC -W -Wall -ansi -std=c99 -pedantic

# Debug or optimization flag
ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -O2
endif

export

default: libdround

all: libdround

libdround:
	@$(MAKE) -e -C $@

.PHONY: default clean examples libdround 

clean:
	@$(MAKE) -C libdround clean

