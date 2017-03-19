#include "user_inc.h"
#include "PyIntObject.h"

extern PyTypeObject PyInt_Type;

/*
 * ������PyInt_Create
 * ������int value -
 * ���أ�PyObject*
 * ˵��������PyInt����
 */
PyObject* PyInt_Create(int value)
{
	PyIntObject* object = new PyIntObject;
	object->refCount = 1;
	object->type = &PyInt_Type;
    object->value = value;
    return (PyObject*)object;
}

/*
* ������int_print
* ������PyObject* object -
* ���أ�void
* ˵����int��ӡ
*/
static void int_print(PyObject* object)
{
    PyIntObject* intObject = (PyIntObject*)object;
    printf("%d\n", intObject->value);
}

/*
 * ������int_add
 * ������PyObject* left - 
 *       PyObject* right -
 * ���أ�PyObject*
 * ˵����int������Ӻ���
 */
static PyObject* int_add(PyObject* left, PyObject* right)
{
	PyIntObject* leftInt = (PyIntObject*)left;
	PyIntObject* rightInt = (PyIntObject*)right;
	PyIntObject* result = (PyIntObject*)PyInt_Create(0);
	if (result == NULL){
		printf("We have no enough memory!!");
		exit(1);
	}
	else{
		result->value = leftInt->value + rightInt->value;
	}
	return (PyObject *)result;
}

/*
* ������int_hash
* ������PyObject* object -
* ���أ�long
* ˵������ȡintֵ
*/
static long int_hash(PyObject* object)
{
	return (long)((PyIntObject*)object)->value;
}

PyTypeObject PyInt_Type =
{
	PyObject_HEAD_INIT(&PyType_Type),
	"int",
	int_print,
	int_add,
	int_hash
};