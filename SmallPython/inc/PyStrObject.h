#ifndef _PYSTROBJECT_H_
#define _PYSTROBJECT_H_

#include "PyObject.h"

typedef struct tagPyStrObject{
    PyObject_HEAD;
    int length;
    long hashValue;
    char value[50];
}PyStringObject;

extern PyObject* PyStr_Create(const char* value);

#endif _PYSTROBJECT_H_