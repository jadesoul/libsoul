/**
 * File: edit_distance.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-08-22 08:43:57.857000
 * Written In: Peking University, beijing, China
 */

#include <jadesoul.hpp>

uint cnt=0;
uint d(const str& a, const str& b, uint i, uint j) {
    ++cnt;
    
    if (i==0) return j;
    if (j==0) return i;
    uint cost=(a[i-1]==b[j-1] ? 0 : 1);
    
    uint x=d(a, b, i-1, j)+1; //²åÈë
    uint y=d(a, b, i, j-1)+1; //É¾³ı
    uint z=d(a, b, i-1, j-1)+cost; //Ìæ»»
    return min(x, y, z);
}

uint edit_distance(const str& a, const str& b) {
    return d(a, b, a.size(), b.size());
}

int main () {
    print(edit_distance("ÄãºÃ", "Äã²»ºÃaÂğ"));
    print(cnt);
}

