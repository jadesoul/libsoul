#ifndef BOOTSTRAP_H_1356496850_52
#define BOOTSTRAP_H_1356496850_52
/**
 * File: bootstrap.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 12:40:50.517000
 * Written In: Peking University, beijing, China
 */

#include "os.h"
#include "compiler.h"
#include "types.h"
#include "macros.h"

//standard libaries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdarg>
#include <cassert>
#include <ctime>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <fstream>
#include <map>
#include <bitset>
#include <set>
#include <typeinfo>
#include <iterator>
#include <exception>
#include <numeric>
// #include <unordered_map>


#ifdef OS_WIN32
	#include <conio.h>
	#include <windows.h>
	
	//for psapi
	#include <psapi.h>
	#ifdef CPL_MSVC
		#pragma comment(lib,"psapi.lib")
	#endif
#endif

#ifdef OS_LINUX
	#include <unistd.h>
	#include <dirent.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <errno.h>
	#include <string.h>
	#include <stdlib.h>
	#include <time.h>
	#include <ctype.h>
	#include <limits.h>
	#include <pwd.h>
	#include <grp.h>

	#ifdef HAVE_SYS_PARAM_H
		#include <sys/param.h>
	#endif
	
	#ifndef MAXPATHLEN
		#if defined(PATH_MAX) && PATH_MAX > 1024
			#define MAXPATHLEN PATH_MAX
		#else
			#define MAXPATHLEN 1024
		#endif
	#endif
	
#endif

//for hash map
#if (defined CPL_GNUC) && (__GNUC__>2)
	#define _GLIBCXX_PERMIT_BACKWARD_HASH
	#include <ext/hash_set>
	#include <ext/hash_map>
	using namespace __gnu_cxx;
#else
	#include <hash_set>
	#include <hash_map>
	using namespace stdext;
#endif


// platform specific includes
#ifdef OS_WIN32
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x400
	#endif
	#define WIN32_LEAN_AND_MEAN
	// #include <windows.h>
	// #include "gl/GLee.h"
   	// #include "gl/glu.h"
	#define __WINDOWS_DS__
	#define __WINDOWS_MM__
	#if (_MSC_VER)       // microsoft visual studio
		#pragma warning(disable : 4996)    	// disable all deprecation warnings
		#pragma warning(disable : 4068)     	// unknown pragmas
		#pragma warning(disable : 4101)     	// unreferenced local variable
		#pragma	warning(disable : 4312)		// type cast conversion (in qt vp)
		#pragma warning(disable : 4311)		// type cast pointer truncation (qt vp)
		#pragma warning(disable : 4018)		// signed/unsigned mismatch (since vector.size() is a size_t)
		#pragma warning(disable : 4267)		// conversion from size_t to Size warning... possible loss of data
		#pragma warning(disable : 4800)		// 'Boolean' : forcing value to bool 'true' or 'false'
		#pragma warning(disable : 4099)		// for debug, PDB 'vc80.pdb' was not found with...
	#endif

	#define TARGET_LITTLE_ENDIAN			// intel cpu

	// some gl.h files, like dev-c++, are old - this is pretty universal
	#ifndef GL_BGR_EXT
	#define GL_BGR_EXT 0x80E0
	#endif
#endif

#ifdef OS_OSX
	#ifndef __MACOSX_CORE__
		#define __MACOSX_CORE__
	#endif
	#include <unistd.h>
	//#include "GLee.h"
	// #include <OpenGL/glu.h>
	#include <ApplicationServices/ApplicationServices.h>

	#if defined(__LITTLE_ENDIAN__)
		#define TARGET_LITTLE_ENDIAN		// intel cpu
	#endif
#endif

#ifdef OS_LINUX
        #include <unistd.h>
        //#include "GLee.h"
        // #include <GL/glu.h>

	// for some reason, this isn't defined at compile time,
	// so this hack let's us work
	// for 99% of the linux folks that are on intel
	// everyone one else will have RGB / BGR issues.
	//#if defined(__LITTLE_ENDIAN__)
		#define TARGET_LITTLE_ENDIAN		// intel cpu
	//#endif

        // some things for serial compilation:
        #define B14400	14400
        #define B28800	28800
#endif


#ifdef OS_IPHONE
	// #import <OpenGLES/ES1/gl.h>
	// #import <OpenGLES/ES1/glext.h>
#endif

#ifdef OS_WIN32
	#undef MAX
	#undef MIN
    #undef min
	#undef max
#endif

// #ifndef MIN
	// #define MIN(x,y) (((x) < (y)) ? (x) : (y))
// #endif

// #ifndef MAX
	// #define MAX(x,y) (((x) > (y)) ? (x) : (y))
// #endif


//namespaces
// using namespace std;
    
using std::max;
using std::min;
using std::vector;
using std::stack;
using std::queue;
using std::pair;
using std::swap;
using std::map;
using std::string;
using std::stringstream;
using std::ostream;
using std::istream;
using std::boolalpha;
using std::accumulate;
// using std::unordered_map;

// using std::set;
// using std::list;
using std::hex;
using std::cin;
using std::cout;
using std::cerr;
using std::clog;
using std::ios;
using std::istringstream;
using std::ostringstream;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::bitset;
using std::ostream_iterator;
using std::iterator_traits;
using std::insert_iterator;
using std::inserter;
using std::back_inserter;
using std::front_inserter;
using std::back_insert_iterator;
using std::front_insert_iterator;
using std::distance;
using std::advance;
using std::ptrdiff_t;

typedef std::vector<int> vec_int;
typedef vec_int vecint;
typedef std::vector<uint> vec_uint;
typedef vec_uint vecuint;
typedef std::vector<char> vec_char;
typedef vec_char vecchar;
typedef std::vector<string> vecstring;

#endif /* BOOTSTRAP_H_1356496850_52 */
