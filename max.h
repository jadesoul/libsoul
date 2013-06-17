#ifndef MAX_H_1345604977_91
#define MAX_H_1345604977_91
/**
 * File: max.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-08-22 11:09:37.908000
 * Written In: Peking University, beijing, China
 */

// template<class T>
// inline const T& max(const T& a, const T& b) {
    // return a>b ? a : b;
// }

template<class T>
inline const T& max(const T& a, const T& b, const T& c) {
    return max(max(a, b), c);
}


#endif /* MAX_H_1345604977_91 */
