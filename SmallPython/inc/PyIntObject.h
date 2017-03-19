#ifndef _PYINTOBJECT_H_
#define _PYINTOBJECT_H_

#include "PyObject.h"
#include "PyTypeObject.h"

typedef struct tagPyIntObject
{
	PyObject_HEAD;
	int value;
}PyIntObject;

extern PyObject* PyInt_Create(int value);

#endif