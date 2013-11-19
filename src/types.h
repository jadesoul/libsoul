#ifndef TYPES_H_1324964318_12
#define TYPES_H_1324964318_12
/**
 * File: types.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-26 18:22:34.362000
 * Written In: Peking University, beijing, China
 */

#include "os.h"

//char
typedef		signed		char		int1;
typedef		signed		char		sint1;
typedef		unsigned	char		uint1;
typedef		unsigned	char		uchar;

//short
typedef		signed		short       int2;
typedef		signed		short       sint2;
typedef		unsigned	short       uint2;
typedef		unsigned	short       ushort;

//int
typedef		signed		int			int4;
typedef		signed		int			sint4;
typedef		unsigned	int			uint4;
typedef		unsigned	int			uint;

//float double
typedef		float					real4;
typedef		double					real8;
// typedef          long double realC;//not often used

#ifdef OS_WIN32
typedef		signed		long long	int8;
typedef		signed		long long	sint8;
typedef		signed		long long	slong;
typedef		unsigned	long long	uint8;
typedef		unsigned	long long	ulong;
extern const char* fmtstr_ulong;
#elif defined(OS_LINUX)
typedef		signed		long long	int8;
typedef		signed		long long	sint8;
typedef		signed		long long	slong;
typedef		unsigned	long long	uint8;
// typedef	unsigned	long long	ulong;
extern const char* fmtstr_ulong;
#endif

//ptr
typedef void* vptr;
typedef char* cptr;

typedef const void* cvptr;
typedef const char* ccptr;

typedef const void* const cvptrc;
typedef const char* const ccptrc;

const	sint1		min_sint1		=	sint1(0x80);
const	sint1		max_sint1		=	0x7F;
const	uint1		min_uint1		=	0x00;
const	uint1		max_uint1		=	0xFF;
const	sint2		min_sint2		=	sint2(0x8000);
const	sint2		max_sint2		=	0x7FFF;
const	uint2		min_uint2		=	0x0000;
const	uint2		max_uint2		=	0xFFFF;
const	sint4		min_sint4		=	0x80000000;
const	sint4		max_sint4		=	0x7FFFFFFF;
const	uint4		min_uint4		=	0x00000000;
const	uint4		max_uint4		=	0xFFFFFFFF;
const	sint8		min_sint8		=	0x8000000000000000LL;
const	sint8		max_sint8		=	0x7FFFFFFFFFFFFFFFLL;
const	uint8		min_uint8		=	0x0000000000000000LL;
const	uint8		max_uint8		=	0xFFFFFFFFFFFFFFFFLL;

#endif /* TYPES_H_1324964318_12 */
