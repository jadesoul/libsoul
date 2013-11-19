#coding:utf8

# from libjade import *

'''
计算字符串a[1...m]与字符串b[1...n]的编辑距离

插入
删除
替换

的最小次数


定义：

    d(i, j) 为 a[1...i] 与 b[1...j] 的编辑距离

若已知：

    d(1, 1)=[
        1,       a[1]!=b[1]
        0,       a[1]==b[1]
    ]
    d(0, 0)=0
    d(n, 0)=n
    d(0, n)=n

则：
    
    d(i, j)=min {
        d(i-1, j)+1,         # 插入
        d(i, j-1)+1,         # 删除
        d(i-1, j-1),          # 替换，且a[i]==a[j]
        d(i-1, j-1)+1,      # 替换，且a[i]!=a[j]
    }

'''

a='1111111111111111111c11111'
b='dcfg'
m=len(a)
n=len(b)

def d(i, j):
    # if i==0 and j==0: return 0
    if i==0: return j
    if j==0: return i
    
    return min(
        d(i-1, j)+1,
        d(i, j-1)+1,
        d(i-1, j-1)+(0 if a[i-1]==b[j-1] else 1)
    )
    
def edit_distance(a, b):
    pass
    
    
if __name__=='__main__':
	print d(m, n)

