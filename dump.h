#ifndef DUMP_H_1356513149_87
#define DUMP_H_1356513149_87
/**
 * File: dump.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 17:12:29.870000
 * Written In: Peking University, beijing, China
 */

#include "datetime.h"

/**************************************************
format: format string to stream
**************************************************/
inline string va_format(const char* fmt, va_list ap);
string c_format(const char* fmt, ...);

#include "dump_format.h"

/**************************************************
log: log massage by format, auto add time
**************************************************/
void log(const char* fmt, ...);

/**************************************************
dump: show a variable in the readable format
**************************************************/
template<class T>
inline void dump(const T& v, ostream& o=cout) {
	o<<v<<endl;
}

#define Macro__over_load_operator_out__SequenceContainer_Left_Deli_Right(Container, left, deli, right)\
template<class T>\
inline ostream& operator<<(ostream& o, const Container<T> c) {\
	o<<left;\
	ostream_iterator<typename Container<T>::value_type> osit(o, deli);\
	copy(c.begin(), c.end(), osit);\
	return o<<right;\
}

Macro__over_load_operator_out__SequenceContainer_Left_Deli_Right(vector, "[ ", ", ", " ]");
Macro__over_load_operator_out__SequenceContainer_Left_Deli_Right(std::list, "( ", ", ", " )");
Macro__over_load_operator_out__SequenceContainer_Left_Deli_Right(std::set, "< ", ", ", " >");


#define Macro__over_load_operator_out__AssociatedContainer_Left_Center_Deli_Right(Container, left, center, deli, right)\
template<class K, class V>\
inline ostream& operator<<(ostream& o, const Container<K, V> c) {\
	o<<left;\
	for (typename Container<K, V>::iterator i=c.begin(), j=c.end(); i!=j; ++i) {\
		o<<i->first<<center<<i->second<<deli;\
	}\
	return o<<right;\
}

Macro__over_load_operator_out__AssociatedContainer_Left_Center_Deli_Right(map, "{ ", ":", ", ", " }");
Macro__over_load_operator_out__AssociatedContainer_Left_Center_Deli_Right(hash_map, "{ ", ":", ", ", " }");



#endif /* DUMP_H_1356513149_87 */
