#include "user_inc.h"
#include "PyDictObject.h"
#include "PyTypeObject.h"
#include <map>

extern PyTypeObject PyDict_Type;

/*
* ������Pydict_Create
* ������void
* ���أ�PyObject*
* ˵��������dict����
*/
PyObject* Pydict_Create(void)
{
    PyDictObject* object = new PyDictObject;
    object->refCount = 1;
    object->type = &PyDict_Type;
    
    return (PyObject*)object;
}

/*
 * ������PyDict_GetItem
 * ������PyObject* target -
 *       PyObject* key - 
 * ���أ�PyObject*
 * ˵������ȡdict��value
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
 * ������PyDict_SetItem
 * ������PyObject* target -
 *       PyObject* key -
 *       PyObject* value -
 * ���أ�int
 * ˵��������dict��value
 */
int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value)
{
    long keyHashValue = (key->type)->hash(key);
    PyDictObject* dictObject = (PyDictObject*)target;
    (dictObject->dict)[keyHashValue] = value;
    return 0;
}

/*
 * ������dict_print
 * ������PyObject* object -
 * ���أ�void
 * ˵����dict�Ĵ�ӡ
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