#include "user_inc.h"
#include "PyIntObject.h"

extern PyTypeObject PyInt_Type;

/*
 * 函数：PyInt_Create
 * 参数：int value -
 * 返回：PyObject*
 * 说明：创建PyInt对象
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
* 函数：int_print
* 参数：PyObject* object -
* 返回：void
* 说明：int打印
*/
static void int_print(PyObject* object)
{
    PyIntObject* intObject = (PyIntObject*)object;
    printf("%d\n", intObject->value);
}

/*
 * 函数：int_add
 * 参数：PyObject* left - 
 *       PyObject* right -
 * 返回：PyObject*
 * 说明：int类型相加函数
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
* 函数：int_hash
* 参数：PyObject* object -
* 返回：long
* 说明：获取int值
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