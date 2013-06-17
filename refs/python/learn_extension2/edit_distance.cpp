/**
 * File: edit_distance.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-08-23 08:59:58.620000
 * Written In: Peking University, beijing, China
 */

#define VERSION "1.2a3"

#if defined(_MSC_VER)
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "Python.h"

#if defined(PY_VERSION_HEX) && PY_VERSION_HEX >= 0x01060000
#if PY_VERSION_HEX  < 0x02020000 || defined(Py_USING_UNICODE)
/* defining this enables unicode support (default under 1.6a1 and later) */
#define HAVE_UNICODE
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

//for i in 0-n
#define for_n(i, n) for (uint i=0; i<n; ++i)
#define for_tn(type, i, n) for (type i=0; i<n; ++i)

//for i in range start-step-stop
#define for_any(i, start, end) for (int i=start; i<=end; ++i)
#define for_tany(type, i, start, end) for (type i=start; i<=end; ++i)
#define for_in(i, start, end, step) for (int i=start; i<end; i+=step)
#define for_tin(type, i, start, end, step) for (type i=start; i<end; i+=step)

typedef unsigned int uint;

/* 
   Function Define and AttributesDefine 
*/


static PyObject* CmdError;
static PyObject* edit_distance(PyObject *self, PyObject *args)
{
    /*
    int PyArg_ParseTuple(PyObject *args, const char *format, ...) 
    return true or false | exception
    */
    char *a, *b;
    uint m, n, r;
    if (!PyArg_ParseTuple(args, "s#s#", &a, &m, &b, &n)) {
        PyErr_SetString(CmdError, "Bad Input");
        return NULL;
    } else {
        if (m==0) { r=n; }
        else if (n==0) { r=m; }
        else {
            uint** d=new uint*[m+1];    //动态规划表格
            for_n(i, m+1) d[i]=new uint[n+1];
            
            for_n(i, m+1) d[i][0]=i;
            for_n(j, n+1) d[0][j]=j;
            
            for_tany(uint, i, 1, m) {
                for_tany(uint, j, 1, n) {
                    uint x=d[i-1][j]+1; //删除，上方
                    uint y=d[i][j-1]+1; //插入，左方
                    uint z=d[i-1][j-1]+(a[i-1]==b[j-1]?0:1); //替换，左上方
                    uint min_xy=(x<y?x:y);
                    d[i][j]=(min_xy<z?min_xy:z);
                }
            }
            r=d[m][n];
            for_n(i, m+1) delete [] d[i];
            delete [] d;
        }
    }
    //PyObject* Py_BuildValue(const char *format, ...)
    return Py_BuildValue("i", r);
}

static PyMethodDef module_methods[] = {
    {"edit_distance", (PyCFunction)edit_distance, METH_VARARGS},
    {NULL, NULL}
};


/* Initial Modules */
PyMODINIT_FUNC init_my_module(void) {
    PyObject *m=Py_InitModule("edit_distance", module_methods);
    if (m==NULL) return;
    /* PyObject* PyErr_NewException(char *name, PyObject *base, PyObject *dict) */
    CmdError = PyErr_NewException("system.error", NULL, NULL);
    Py_INCREF(CmdError);
    PyModule_AddObject(m, "error", CmdError);
};

extern "C" DL_EXPORT(void) initedit_distance(void) {
    /* Initialize the Python interpreter. Required. */
    Py_Initialize();

    /* Add a static module */
    init_my_module();
}

#ifdef __cplusplus
}
#endif