#include <python3.13/Python.h>
#include "cpuid.h"

struct Py_cpuid_regs {
	PyObject_HEAD
	struct cpuid_regs regs;
};

static PyObject *Py_cpuid_regs_get_eax(struct Py_cpuid_regs *self, void *closure)
{
	return PyLong_FromUnsignedLong(self->regs.eax);
}

static PyObject *Py_cpuid_regs_get_ebx(struct Py_cpuid_regs *self, void *closure)
{
	return PyLong_FromUnsignedLong(self->regs.ebx);
}

static PyObject *Py_cpuid_regs_get_ecx(struct Py_cpuid_regs *self, void *closure)
{
	return PyLong_FromUnsignedLong(self->regs.ecx);
}

static PyObject *Py_cpuid_regs_get_edx(struct Py_cpuid_regs *self, void *closure)
{
	return PyLong_FromUnsignedLong(self->regs.edx);
}

static int Py_cpuid_regs_set_eax(struct Py_cpuid_regs *self, PyObject* value, void *closure)
{
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "cannot delete attribute edx");
		return -1;
	}

	if (!PyLong_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "Value must be an integer");
		return -1;
	}

	unsigned long v = PyLong_AsUnsignedLong(value);
	if (v > 0xffffffff) {
		PyErr_SetString(PyExc_ValueError, "Integer must be a 32-bit unsigned value");
		return -1;
	}
	self->regs.eax = v;

	return 0;
}

static int Py_cpuid_regs_set_ebx(struct Py_cpuid_regs *self, PyObject* value, void *closure)
{
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "cannot delete attribute edx");
		return -1;
	}

	if (!PyLong_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "Value must be an integer");
		return -1;
	}

	unsigned long v = PyLong_AsUnsignedLong(value);
	if (v > 0xffffffff) {
		PyErr_SetString(PyExc_ValueError, "Integer must be a 32-bit unsigned value");
		return -1;
	}
	self->regs.ebx = v;

	return 0;
}

static int Py_cpuid_regs_set_ecx(struct Py_cpuid_regs *self, PyObject* value, void *closure)
{
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "cannot delete attribute edx");
		return -1;
	}

	if (!PyLong_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "Value must be an integer");
		return -1;
	}

	unsigned long v = PyLong_AsUnsignedLong(value);
	if (v > 0xffffffff) {
		PyErr_SetString(PyExc_ValueError, "Integer must be a 32-bit unsigned value");
		return -1;
	}
	self->regs.ecx = v;
	return 0;
}

static int Py_cpuid_regs_set_edx(struct Py_cpuid_regs *self, PyObject* value, void *closure)
{
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "cannot delete attribute edx");
		return -1;
	}

	if (!PyLong_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "Value must be an integer");
		return -1;
	}

	unsigned long v = PyLong_AsUnsignedLong(value);
	if (v > 0xffffffff) {
		PyErr_SetString(PyExc_ValueError, "Integer must be a 32-bit unsigned value");
		return -1;
	}
	self->regs.edx = v;

	return 0;
}

static PyGetSetDef cpuid_regs_getset[] = {
	{"eax", (getter)Py_cpuid_regs_get_eax, (setter)Py_cpuid_regs_set_eax, "eax register", NULL},
	{"ebx", (getter)Py_cpuid_regs_get_ebx, (setter)Py_cpuid_regs_set_ebx, "ebx register", NULL},
	{"ecx", (getter)Py_cpuid_regs_get_ecx, (setter)Py_cpuid_regs_set_ecx, "ecx register", NULL},
	{"edx", (getter)Py_cpuid_regs_get_edx, (setter)Py_cpuid_regs_set_edx, "edx register", NULL},
	{NULL}
};

static PyTypeObject Py_cpuid_regs_type = {
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "cpuid.cpuid_regs",
	.tp_basicsize = sizeof(struct Py_cpuid_regs),
	.tp_flags = Py_TPFLAGS_DEFAULT,
	.tp_doc = "cpuid registers",
	.tp_getset = cpuid_regs_getset,
};
