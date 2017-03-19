/*
* 对象类型
*/

#ifndef _PYTYPEOBJECT_H_
#define _PYTYPEOBJECT_H_

#include "PyObject.h"

typedef void(*PrintFun)(PyObject* object);
typedef PyObject* (*AddFun)(PyObject* left, PyObject* right);
typedef long(*HashFun)(PyObject* object);

typedef struct tagPyTypeObject{
	PyObject_HEAD;
	char* name;
	PrintFun print;	// 输出操作
	AddFun add;		// 加法操作
	HashFun hash;	// hash操作
}PyTypeObject;

extern PyTypeObject PyType_Type;

#endif