#ifndef DYNBASE_H_
#define DYNBASE_H_

#include <string>
using std::string;
#include <map>
using std::map;

typedef void* (*CREATE_FUNC)();

// ������->��̬��������
// �������ͺ󹤳�����벻��Ҫ���κθĶ�������һ����if-else�á�
// ���Ǿ�̬�ģ�����main֮ǰ�ͳ�ʼ�����ˡ�
class DynObjectFactory
{
public:
	static void* CreateObject(const string& name)
	{
		map<string,CREATE_FUNC>::const_iterator it;
		it = map_cls_.find(name);
		if (it == map_cls_.end()) { // û�ҵ�
			return NULL;
		} else {
			return it->second();
		}
	}

	static void Register(const string& name, CREATE_FUNC func)
	{
		map_cls_[name] = func;
	}
private:
	static map<string, CREATE_FUNC> map_cls_;
};

// vs __declspec(selectany)
__attribute((weak)) map<string, CREATE_FUNC> DynObjectFactory::map_cls_; // ���ﲻ��Ҫ�ټ�static

//
//#define REGISTER_CLASS(class_name) \
//static void* class_name##NewInstance() { \
//	return new class_name;\
//}\
//DynObjectFactory::Register(#class_name, class_name##NewInstance)


class Register
{
public:
	Register(const string& name, CREATE_FUNC func)
	{
		DynObjectFactory::Register(name, func);
	}
};

#define REGISTER_CLASS(class_name) \
class class_name##Register \
{ \
public: \
	static void* NewInstance() \
	{ \
		return new class_name; \
	} \
private: \
	static Register reg_; \
}; \
Register class_name##Register::reg_(#class_name, class_name##Register::NewInstance)

#endif // DYNBASE_H_