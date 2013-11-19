/**
 * File: edit_distance3.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-08-22 17:54:33.301000
 * Written In: Peking University, beijing, China
 */

#include <jadesoul.hpp>


uint edit_distance(const str& a, const str& b) {
    uint m=a.size(), n=b.size();
    if (m==0) return n;
    if (n==0) return m;
    
    uint** d=new uint*[m+1];    //动态规划表格
    for_n(i, m+1) d[i]=new uint[n+1];
    
    for_n(i, m+1) d[i][0]=i;
    for_n(j, n+1) d[0][j]=j;
    
    for_tany(uint, i, 1, m) {
        for_tany(uint, j, 1, n) {
            uint x=d[i-1][j]+1; //删除，上方
            uint y=d[i][j-1]+1; //插入，左方
            uint z=d[i-1][j-1]+(a[i-1]==b[j-1]?0:1); //替换，左上方
            d[i][j]=min(x, y, z);
        }
    }
    uint r=d[m][n];
    
    for_n(i, m+1) delete [] d[i];
    delete [] d;
    
    return r;
}

int main () {
    list<str> ss=fread("test.txt").split("\n");
    str s=ss[0];
    time_init();
    for_tany(uint, i, 1, ss.size()-1) {
    // for_tany(uint, i, 1, 10-1) {
        str& t=ss[i];
        edit_distance(s, t);
        // cout<<edit_distance(s, t)<<endl;
    }
    // cout<<edit_distance("abc", "def")<<endl;
    // cout<<edit_distance("abc", "acd")<<endl;
    time_gap("finish");
    return 0;
}


