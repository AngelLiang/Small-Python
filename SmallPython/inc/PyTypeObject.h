/*
* ��������
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
	PrintFun print;	// �������
	AddFun add;		// �ӷ�����
	HashFun hash;	// hash����
}PyTypeObject;

extern PyTypeObject PyType_Type;

#endif