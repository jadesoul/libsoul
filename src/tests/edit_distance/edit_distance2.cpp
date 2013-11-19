/**
 * File: edit_distance2.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-08-22 10:40:13.996000
 * Written In: Peking University, beijing, China
 */

#include <jadesoul.hpp>

uint edit_distance(const str& a, const str& b) {
    uint m=a.size(), n=b.size();
    if (m==0) return n;
    if (n==0) return m;
    
    uint** d=new uint*[m+1];    //动态规划表格
    for_n(i, m+1) d[i]=new uint[n+1];
    
    char** f=new char*[m]; //备忘录表格
    for_n(i, m) f[i]=new char[n];
    for_n(i, m) for_n(j, n) f[i][j]=' ';
    
    for_n(i, m+1) d[i][0]=i;
    for_n(j, n+1) d[0][j]=j;
    
    for_tany(uint, i, 1, m) {
        for_tany(uint, j, 1, n) {
            uint x=d[i-1][j]+1; //删除，上方
            uint y=d[i][j-1]+1; //插入，左方
            uint z=d[i-1][j-1]+(a[i-1]==b[j-1]?0:1); //替换，左上方
            if (x<=y AND x<=z) {
                d[i][j]=x;
                f[i-1][j-1]='d';
            } else if (y<=x AND y<=z) {
                d[i][j]=y;
                f[i-1][j-1]='i';
            } else {
                d[i][j]=z;
                f[i-1][j-1]=(a[i-1]==b[j-1]?'=':'r');
            }
        }
    }
    uint r=d[m][n];
    
    for_n(i, m+1) {
        for_n(j, n+1) {
            cout<<d[i][j];
            if (i!=0 AND j!=0) cout<<' '<<f[i-1][j-1];
            cout<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
    
    uint i=m, j=n;
    while (i>=1 OR j>=1) {
        if (i==0) {
            cout<<"insert "<<b(0, j)<<endl;
            j=0;
        } else if (j==0) {
            cout<<"delete "<<a(0, i)<<endl;
            i=0;
        } else {
            char g=f[i-1][j-1];
            if (g=='=') {
                //pass
                i-=1;
                j-=1;
                cout<<"skip "<<a[i]<<endl;
            } else if (g=='r') {
                i-=1;
                j-=1;
                cout<<"replace "<<a[i]<<"->"<<b[j]<<endl;
            } else if (g=='i') {
                j-=1;
                cout<<"insert "<<b[j]<<endl;
            } else /*d*/ {
                i-=1;
                cout<<"delete "<<a[i]<<endl;
            }
        }
    }
    
    for_n(i, m+1) delete [] d[i];
    delete [] d;
    
    for_n(i, m) delete [] f[i];
    delete [] f;
    
    return r;
}

int main () {
    print(edit_distance("hi, this is my name , jadesoul", "hello, and my name is jadesoul"));
    print(edit_distance("hi, this is my name , jadesoul", "oh, my god, jadesoul"));
    return 0;
}

