/*
How to use :
	import spam
	status = spam.system("ls -l")
dome is C++ Extension
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

/* 
   Function Define and AttributesDefine 
*/
static PyObject* CmdError;
static PyObject* cmd(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

	/*
	int PyArg_ParseTuple(PyObject *args, const char *format, ...) 
	return true or false | exception
	*/
    if (!PyArg_ParseTuple(args, "s", &command))
	{
		PyErr_SetString(CmdError, "System command failed");
		return NULL;
	}
	else{
		printf("run command is:");
 		puts(command); //or use PyObject_Print for debug
	}
    sts = system(command);
	//PyObject* Py_BuildValue(const char *format, ...)
    return Py_BuildValue("i", sts);
}



static PyMethodDef CmdMethods[] = {
    {"cmd", (PyCFunction) cmd, METH_VARARGS},
    {NULL, NULL}
};


/* 
   Initial Modules
*/

PyMODINIT_FUNC
initspam(void)
{
    PyObject *m;
    m = Py_InitModule("spam", CmdMethods);
    if (m == NULL)
        return;
	/*
	PyObject* PyErr_NewException(char *name, PyObject *base, PyObject *dict)
	*/
    CmdError = PyErr_NewException("system.error", NULL, NULL);
    Py_INCREF(CmdError);
    PyModule_AddObject(m, "error", CmdError);
};

extern "C" DL_EXPORT(void) initaggdraw(void)
{
    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Add a static module */
    initspam();

	PyObject* g = PyDict_New();
	PyDict_SetItemString(g, "__builtins__", PyEval_GetBuiltins());
    PyRun_String("print 'welcome!'\n", Py_file_input, g, NULL);
}
