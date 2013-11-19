def say_hello_to(name):
    print("Hello %s!" % name)
    return 1344
    
def edit_distance(a, b):
    m=len(a)
    n=len(b)
    d=[]
    for i in xrange(m+1):
        d.append([0]*(n+1))
        
    for i in xrange(m+1):
        d[i][0]=i
    for j in xrange(n+1):
        d[0][j]=j
    for i in xrange(m):
        for j in xrange(n):
            d[i+1][j+1]=min(
                d[i+1][j]+1,
                d[i][j+1]+1,
                d[i][j]+(a[i]!=b[j])
            )
            
    # for i in xrange(m+1):
        # for j in xrange(n+1):
            # print d[i][j], '\t',
        # print
        
    return d[m][n]
    
def edit_distance2(char* a, char *b):
    cdef int m=len(a)
    cdef int n=len(b)
    d=[]
    for i in xrange(m+1):
        d.append([0]*(n+1))
        
    for i in xrange(m+1):
        d[i][0]=i
    for j in xrange(n+1):
        d[0][j]=j
    for i in xrange(m):
        for j in xrange(n):
            d[i+1][j+1]=min(
                d[i+1][j]+1,
                d[i][j+1]+1,
                d[i][j]+(a[i]!=b[j])
            )
            
    # for i in xrange(m+1):
        # for j in xrange(n+1):
            # print d[i][j], '\t',
        # print
        
    return d[m][n]