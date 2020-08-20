/**
 *  @file defines.h
 *  @author Sheng Di
 *  @date July, 2019
 *  @brief Header file for the dataCompression.c.
 *  (C) 2016 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#ifndef _DROUND_DEFINES_H
#define _DROUND_DEFINES_H

#define DROUND_VER_MAJOR 2
#define DROUND_VER_MINOR 1
#define DROUND_VER_BUILD 9
#define DROUND_VER_REVISION 0

#define DROUND_FLOAT 0
#define DROUND_DOUBLE 1
#define DROUND_UINT8 2
#define DROUND_INT8 3
#define DROUND_UINT16 4
#define DROUND_INT16 5
#define DROUND_UINT32 6
#define DROUND_INT32 7
#define DROUND_UINT64 8
#define DROUND_INT64 9

#define DROUND_NSD 0
#define DROUND_DSD 1

#define LITTLE_ENDIAN_DATA 0 //refers to the endian type of the data read from the disk
#define BIG_ENDIAN_DATA 1 //big_endian (ppc, max, etc.) ; little_endian (x86, x64, etc.)

#define LITTLE_ENDIAN_SYSTEM 0 //refers to the endian type of the system
#define BIG_ENDIAN_SYSTEM 1

#define DynArrayInitLen 1024

//SUCCESS returning status
#define DROUND_SCES 0  //successful
#define DROUND_NSCS -1 //Not successful
#define DROUND_FERR -2 //Failed to open input file
#define DROUND_TERR -3 //wrong data type (should be only float or double)
#define DROUND_DERR -4 //dimension error
#define DROUND_MERR -5 //sz_mode error
#define DROUND_BERR -6 //bound-mode error (should be only ABS, REL, ABS_AND_REL, ABS_OR_REL, or PW_REL)

#endif /* _DROUND_DEFINES_H */
