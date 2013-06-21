/**
 * File: types.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 14:33:55.401000
 * Written In: Peking University, beijing, China
 */


#include "types.h"

#ifdef OS_WIN32
const char* fmtstr_ulong="%I64d";
#elif defined(OS_LINUX)
const char* fmtstr_ulong="%lld";
#endif

