#coding:utf8

from libjade import *
import edit_distance
import edit_distance2
import nltk
from string import ascii_letters

if __name__=='__main__':
    l=list(ascii_letters[:10])
    s=''
    for i in xrange(200):
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
    print time_gap('edit_distance.edit_distance')
    
    for i in xrange(n):
        a=edit_distance2.edit_distance(s, t)
    print time_gap('edit_distance2.edit_distance')
    
    for i in xrange(n):
        a=nltk.edit_distance(s, t)
    print time_gap('nltk.edit_distance')
    