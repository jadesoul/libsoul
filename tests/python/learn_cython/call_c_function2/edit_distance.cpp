typedef unsigned int uint;


uint _edit_distance(char* a, char* b, uint m, uint n) {
    uint r, i, j, x, y, z, t;
    if (m==0) { return n; }
    else if (n==0) { return m; }
    else {
        uint** d=new uint*[m+1];    //动态规划表格
        for_n(i, m+1) d[i]=new uint[n+1];
        
        for(i=0; i<=m; ++i) d[i][0]=i;
        for(j=0; j<=n; ++j) d[0][j]=j;
        
        for(i=1; i<=m; ++i) {
            for(j=1; j<=n; ++j) {
                x=d[i-1][j]+1; //删除，上方
                y=d[i][j-1]+1; //插入，左方
                z=d[i-1][j-1]+(a[i-1]==b[j-1]?0:1); //替换，左上方
                t=(x<y?x:y);
                d[i][j]=(t<z?t:z);
            }
        }
        r=d[m][n];
        for_n(i, m+1) delete [] d[i];
        delete [] d;
        return r;
    }
}