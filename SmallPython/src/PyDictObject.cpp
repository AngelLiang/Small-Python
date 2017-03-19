#include "user_inc.h"
#include "PyDictObject.h"
#include "PyTypeObject.h"
#include <map>

extern PyTypeObject PyDict_Type;

/*
* 函数：Pydict_Create
* 参数：void
* 返回：PyObject*
* 说明：创建dict对象
*/
PyObject* Pydict_Create(void)
{
    PyDictObject* object = new PyDictObject;
    object->refCount = 1;
    object->type = &PyDict_Type;
    
    return (PyObject*)object;
}

/*
 * 函数：PyDict_GetItem
 * 参数：PyObject* target -
 *       PyObject* key - 
 * 返回：PyObject*
 * 说明：获取dict的value
 */
PyObject* PyDict_GetItem(PyObject* target, PyObject* key)
{
    long keyHashValue = (key->type)->hash(key);
    map<long, PyObject*>& dict = ((PyDictObject*)target)->dict;
    map<long, PyObject*>::iterator it = dict.find(keyHashValue);
    map<long, PyObject*>::iterator end = dict.end();
    if (it == end){
        return NULL;
    }
    return it->second;
}

/*
 * 函数：PyDict_SetItem
 * 参数：PyObject* target -
 *       PyObject* key -
 *       PyObject* value -
 * 返回：int
 * 说明：设置dict的value
 */
int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value)
{
    long keyHashValue = (key->type)->hash(key);
    PyDictObject* dictObject = (PyDictObject*)target;
    (dictObject->dict)[keyHashValue] = value;
    return 0;
}

/*
 * 函数：dict_print
 * 参数：PyObject* object -
 * 返回：void
 * 说明：dict的打印
 */
static void dict_print(PyObject* object)
{
    PyDictObject* dictObject = (PyDictObject*)object;
    printf("{");
    map<long, PyObject*>::iterator it = (dictObject->dict).begin();
    map<long, PyObject*>::iterator end = (dictObject->dict).end();
    for (; it != end; ++it){
        // print key
        printf("%ld : ", it->first);
        // print value
        PyObject* value = it->second;
        printf(", ");
    }
    printf("}\n");
}

PyTypeObject PyDict_Type = {
    PyObject_HEAD_INIT(&PyType_Type),
    "dict",
    dict_print,
    0,
    0
};