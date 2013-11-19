from libc.stdlib cimport atoi

cdef extern from r"E:\svnprojects-local\jadesoulpp\apps\python\learn_cython\call_c_function\myc.h":
    int myfunc(int)
    
cpdef parse_charptr_to_py_int(char* s):
    assert s is not NULL, "byte string value is NULL"
    return atoi(s)   # note: atoi() has no error detection!