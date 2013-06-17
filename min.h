#ifndef MIN_H_1345604972_39
#define MIN_H_1345604972_39
/**
 * File: min.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-08-22 11:09:32.388000
 * Written In: Peking University, beijing, China
 */
 
// template<class T> 
// inline const T& min(const T& a, const T& b) {
    // return a<b ? a : b;
// }

template<class T> 
inline const T& min(const T& a, const T& b, const T& c) {
    return min(min(a, b), c);
}

#endif /* MIN_H_1345604972_39 */
