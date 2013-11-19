#coding:utf8

from libjade import *
from nltk import edit_distance
from string import ascii_letters

if __name__=='__main__':
    ss=fread('test.txt').split();
    s=ss[0]
    time_init()
    for i in xrange(1, len(ss)):
    # for i in xrange(1, 10):
        t=ss[i]
        # print edit_distance(s, t)
        edit_distance(s, t)
    print time_gap('finished')
    
    # l=list(ascii_letters)
    # ss=[]
    # for i in xrange(100000):
        # shuffle(l)
        # s=''.join(l)
        # ss.append(s)
    # fwrite('\n'.join(ss), 'test.txt')
    
    
    
    
    
    
    
    