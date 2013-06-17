#ifndef OS_H_1324964318_10
#define OS_H_1324964318_10
/**
 * File: os.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-26 18:17:56.788000
 * Written In: Peking University, beijing, China
 */

//detect OS types
#if defined( __WIN32__ ) || defined( _WIN32 )
	#define OS_WIN32
#elif defined( __APPLE_CC__)
	#include <TargetConditionals.h>
	#if (TARGET_OF_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE)
		#define OS_IPHONE
		#define OS_OPENGLES
	#else
		#define OS_OSX
	#endif
#else
	#define OS_LINUX
#endif

#endif /* OS_H_1324964318_10 */
