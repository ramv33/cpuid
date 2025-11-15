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

static PyGetSetDef cpuid_regs_getset[] = {
	{"eax", (getter)Py_cpuid_regs_get_eax, NULL, "eax register", NULL},
	{"ebx", (getter)Py_cpuid_regs_get_ebx, NULL, "ebx register", NULL},
	{"ecx", (getter)Py_cpuid_regs_get_ecx, NULL, "ecx register", NULL},
	{"edx", (getter)Py_cpuid_regs_get_edx, NULL, "edx register", NULL},
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
