#coding:utf8

from libjade import *
import edit_distance
# import nltk
from string import ascii_letters
# import pyximport; pyximport.install()
# import hello
# import sys
# sys.path.insert(0, '/root/.pyxbld/lib.linux-x86_64-2.7/')
# import hello
    
if __name__=='__main__':
    l=list(ascii_letters[:5])
    s=''
    for i in xrange(100):
        shuffle(l)
        s+=''.join(l)
    t=''
    for i in xrange(100):
        shuffle(l)
        t+=''.join(l)
    
    n=20
    print len(s), len(t)
    
    time_init()
    for i in xrange(n):
        b=edit_distance.edit_distance(s, t)
    print time_gap('c.edit_distance')
    
    # for i in xrange(n):
        # a=hello.edit_distance2(s, t)
    # print time_gap('hello.edit_distance2')
    
    # time_init()
    # for i in xrange(n):
        # a=hello.edit_distance(s, t)
    # print time_gap('hello.edit_distance')
    

    