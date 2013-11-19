cdef extern from r"E:\svnprojects-local\jadesoulpp\apps\python\learn_cython\call_c_function2\edit_distance.cpp":
    unsigned int _edit_distance(char* a, char* b, unsigned int m, unsigned int n)

def edit_distance(s, t):
    assert isinstance(s, str)
    assert isinstance(t, str)
    return _edit_distance(s, t, len(s), len(t))