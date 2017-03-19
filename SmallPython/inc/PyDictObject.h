#ifndef _PYDICTOBJECT_H_
#define _PYDICTOBJECT_H_

#include "PyObject.h"
//#include <iostream>
#include <map>

typedef struct tagPyDictObject{
    PyObject_HEAD;
    map<long, PyObject*> dict;
}PyDictObject;

extern PyObject* PyDict_Create(void);
extern PyObject* PyDict_GetItem(PyObject* target, PyObject* key);
extern int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value);

#endif