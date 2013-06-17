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

#include <jadesoul.hpp>
            

#ifdef __cplusplus
extern "C" {
#endif

/* 
   Function Define and AttributesDefine 
*/
static PyObject* CmdError;
static PyObject* _edit_distance(PyObject *self, PyObject *args)
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
        r=edit_distance(a, a+m, b, b+n);
    }
    //PyObject* Py_BuildValue(const char *format, ...)
    return Py_BuildValue("i", r);
}

static PyMethodDef module_methods[] = {
    {"edit_distance", (PyCFunction)_edit_distance, METH_VARARGS},
    {NULL, NULL}
};

/* Initial Modules */
PyMODINIT_FUNC init_my_module(void) {
    PyObject *m=Py_InitModule("edit_distance2", module_methods);
    if (m==NULL) return;
    /* PyObject* PyErr_NewException(char *name, PyObject *base, PyObject *dict) */
    CmdError = PyErr_NewException("system.error", NULL, NULL);
    Py_INCREF(CmdError);
    PyModule_AddObject(m, "error", CmdError);
};

extern "C" DL_EXPORT(void) initedit_distance2(void) {
    /* Initialize the Python interpreter. Required. */
    Py_Initialize();

    /* Add a static module */
    init_my_module();
}

#ifdef __cplusplus
}
#endif