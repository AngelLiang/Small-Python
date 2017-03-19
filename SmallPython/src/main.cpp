#include "user_inc.h"

//PyObject *m_LocalEnvironment = new PyDictObject;
PyDictObject *m_LocalEnvironment = new PyDictObject;

extern void ExcuteCommand(string& command);
extern void ExcuteAdd(string &target, string &source);
extern void ExcutePrint(string symbol);
extern PyObject* GetObjectBySymbol(string& symbol);
extern void Excute(void);

/*
 * 函数：ExcuteCommand
 * 参数：string &command -
 * 返回：void
 * 说明：执行命令
 */
void ExcuteCommand(string& command)
{
    string::size_type pos = 0;
    if ((pos = command.find("print ")) != string::npos){
        ExcutePrint(command.substr(6));
    }
    else if ((pos = command.find(" = ")) != string::npos){
        string target = command.substr(0, pos);
        string source = command.substr(pos + 3);
        ExcuteAdd(target, source);
    }
}

bool IsSourceAllDigit(string source)
{
    bool result = true;
    for (int i = 0; i<source.size(); i++)
    {
        result = isdigit(source[i]);
        if (result == false)
            break;
    }
    return result;

}

/*
 * 函数：ExcuteAdd
 * 参数：string &target - 
 *       string &source - 
 * 返回：void
 * 说明：执行相加操作
 */
void ExcuteAdd(string &target, string &source)
{
    string::size_type pos;
    PyObject* strValue = NULL;
    PyObject* resultValue = NULL;
    if (IsSourceAllDigit(source)){
        PyObject* intValue = PyInt_Create(atoi(source.c_str()));
        PyObject* key = PyStr_Create(target.c_str());
        PyDict_SetItem((PyObject*)m_LocalEnvironment, key, intValue);
    }
    else if (source.find("\"")!=string::npos){
        strValue = PyStr_Create(source.substr(1, source.size() - 2).c_str());
        PyObject* key = PyStr_Create(target.c_str());
        PyDict_SetItem((PyObject*)m_LocalEnvironment, key, strValue);
    }
    else if ((pos =source.find("+")) != string::npos){
        PyObject* leftObject = GetObjectBySymbol(source.substr(0, pos));
        PyObject* rightObject = GetObjectBySymbol(source.substr(pos + 1));
        if (leftObject != NULL && right != NULL && leftObject->type == rightObject->type){
            resultValue = (leftObject->type)->add(leftObject, rightObject);
            PyObject* key = PyStr_Create(target.c_str());
            PyDict_SetItem((PyObject*)m_LocalEnvironment, key, resultValue);
        }
        //(m_LocalEnvironment->type)->print((PyObject*)m_LocalEnvironment);
    }
}

PyObject* GetObjectBySymbol(string& symbol)
{
    PyObject* key = PyStr_Create(symbol.c_str());
    PyObject* value = PyDict_GetItem((PyObject*)m_LocalEnvironment, key);
    if (value == NULL){
        cout << "[Error] : " << symbol << " is not defined;!" << endl;
        return NULL;
    }
    return value;
}

/*
* 函数：ExcutePrint
* 参数：string symbol -
* 返回：void
* 说明：执行打印操作
*/
void ExcutePrint(string symbol)
{
    PyObject* object = GetObjectBySymbol(symbol);
    if (object != NULL){
        PyTypeObject* type = object->type;
        type->print(object);
    }
}


const char* info = "******************Python Research******************\n";
const char* prompt = ">>>";
string m_Command;

/*
 * 函数：Excute
 * 参数：void
 * 返回：void
 */
void Excute(void)
{
	cout << info;
	cout << prompt;
	while (getline(cin, m_Command)){
		if (m_Command.size() == 0){
			cout << prompt;
			continue;
		}
		else if (m_Command == "exit"){
			return;
		}
		else{
			ExcuteCommand(m_Command);
		}
		cout << prompt;
	}
}

int main(int argc, char* argv[])
{
	Excute();
    return 0;
}

