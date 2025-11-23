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

static PyObject *py_get_vendor_id(PyObject *self, PyObject *Py_UNUSED(ignored))
{
	char vendor_id[13];

	get_vendor_id(vendor_id);

	return PyUnicode_FromString(vendor_id);
}

static PyObject *py_get_processor_info(PyObject *self, PyObject *Py_UNUSED(ignored))
{
	struct processor_identifier proc_id;

	get_processor_info(&proc_id, NULL);
	PyObject *dict = PyDict_New();
	if (!dict)
		return NULL;

	PyDict_SetItemString(dict, "family", PyLong_FromLong(proc_id.family));
	PyDict_SetItemString(dict, "model", PyLong_FromLong(proc_id.model));
	PyDict_SetItemString(dict, "stepping", PyLong_FromLong(proc_id.stepping));

	return dict;
}

static PyMethodDef cpuid_methods[] = {
	{"cpuid", py_cpuid, METH_VARARGS, "Run CPUID instruction and return registers"},
	{"get_vendor_id", py_get_vendor_id, METH_NOARGS, "Get CPU Vendor ID"},
	{"get_processor_info", py_get_processor_info, METH_NOARGS, "Return cpu model, family, and stepping"},
	{NULL, NULL, 0, NULL},
};

static struct PyModuleDef cpuid_module = {
	PyModuleDef_HEAD_INIT,
	"cpuid",
	"Python module for accessing x86 CPUID",
	-1,
	cpuid_methods
};

static PyObject *make_feature_list(const char *feat_list[32])
{
	PyObject *list = PyList_New(32);
	if (!list)
		return NULL;

	for (int i = 0; i < 32; i++) {
		PyObject *str = PyUnicode_FromString(feat_list[i]);
		if (!str) {
			Py_DECREF(list);
			return NULL;
		}
		PyList_SetItem(list, i, str);
	}

	return list;
}

static void add_feature_list_constants(PyObject *m)
{
	PyObject *list = NULL;

	list = make_feature_list(g_feat_01_intel_ecx);
	if (list)
		PyModule_AddObject(m, "feat_01_intel_ecx", list);

	list = make_feature_list(g_feat_01_intel_edx);
	if (list)
		PyModule_AddObject(m, "feat_01_intel_edx", list);

	list = make_feature_list(g_feat_01_amd_ecx);
	if (list)
		PyModule_AddObject(m, "feat_01_amd_ecx", list);

	list = make_feature_list(g_feat_01_amd_edx);
	if (list)
		PyModule_AddObject(m, "feat_01_amd_edx", list);
}

PyMODINIT_FUNC PyInit_cpuid(void)
{
	if (PyType_Ready(&Py_cpuid_regs_type) < 0)
		return NULL;

	PyObject *m = PyModule_Create(&cpuid_module);
	if (!m)
		return NULL;

	add_feature_list_constants(m);

	Py_INCREF(&Py_cpuid_regs_type);
	PyModule_AddObject(m, "cpuid_regs", (PyObject *)&Py_cpuid_regs_type);

	return m;
}
