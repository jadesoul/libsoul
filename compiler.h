#ifndef COMPILER_H_1324964318_11
#define COMPILER_H_1324964318_11
/**
 * File: compiler.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-26 18:19:11.150000
 * Written In: Peking University, beijing, China
 */

#include "os.h"

//detect compiler types
#if defined(__GNUC__)
	#define CPL_GNUC
	#define CPL_VER __GNUC__
#endif

#if defined(_MSC_VER)
	#define CPL_MSVC
	#define CPL_VER _MSC_VER
#endif

#if (defined OS_WIN32) && (defined CPL_MSVC)
	#define ENV_WIN32_MSVC
#endif

// #if defined(__STDC__) || defined(__cplusplus) || defined(_MSC_EXTENSIONS)
// #else
// #endif

// #if defined(_MSC_VER) && (_MSC_VER >= 1020)
// #pragma once
// #endif

#endif /* COMPILER_H_1324964318_11 */
