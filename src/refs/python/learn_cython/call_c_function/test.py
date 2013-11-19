#coding:utf8


import pyximport; pyximport.install()
import call_c

print call_c.parse_charptr_to_py_int('123')+1
print call_c.parse_charptr_to_py_int('abc')+1
print call_c.myfunc(12)
print call_c.myfunc(0)


