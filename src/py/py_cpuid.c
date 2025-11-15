#include <python3.13/Python.h>
#include "py_cpuid.h"
#include "cpuid.h"

static PyObject *py_cpuid(PyObject *self, PyObject *args)
{
	struct cpuid_regs regs;
	
	if (!PyArg_ParseTuple(args, "II", &regs.eax, &regs.ebx))
		return NULL;

	cpuid(&regs);
	struct Py_cpuid_regs *obj = PyObject_New(struct Py_cpuid_regs, &Py_cpuid_regs_type);
	obj->regs = regs;
	
	return (PyObject *)obj;
}

static PyMethodDef cpuid_methods[] = {
	{"cpuid", py_cpuid, METH_VARARGS, "Run CPUID instruction and return registers"},
	{NULL, NULL, 0, NULL},
};

static struct PyModuleDef cpuid_module = {
	PyModuleDef_HEAD_INIT,
	"cpuid",
	"Python module for accessing x86 CPUID",
	-1,
	cpuid_methods
};

PyMODINIT_FUNC PyInit_cpuid(void)
{
	if (PyType_Ready(&Py_cpuid_regs_type) < 0)
		return NULL;

	PyObject *m = PyModule_Create(&cpuid_module);
	if (!m)
		return NULL;

	Py_INCREF(&Py_cpuid_regs_type);
	PyModule_AddObject(m, "cpuid_regs", (PyObject *)&Py_cpuid_regs_type);

	return m;
}
