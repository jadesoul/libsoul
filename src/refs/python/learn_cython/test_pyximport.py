#coding:utf8

import pyximport; pyximport.install()
import hello

if __name__=='__main__':
    print dir(hello)
    print hello.say_hello_to('jadesoul')
    print hello.edit_distance('ab', 'abc')

