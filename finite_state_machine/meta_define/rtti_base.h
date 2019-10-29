#ifndef __CRTTI_BASE_H__
#define __CRTTI_BASE_H__

//运行时类型 只要通过实现接口的方式实现
//将所有类型都放到union中 所有类型都是pod的
//并且通过仿函数继承实现虚函数功能

#include <new>
#include <string.h>
#include <assert.h>

namespace FiniteStateMachineMeta
{
	namespace RTTI
	{
		class CRTTIBase
		{
		public:
			const char* (*GetClassName)();
			int (*GetType)();
		};

		template<typename T>
		class CRTTIInterface : public CRTTIBase
		{
		public:
			typedef T Interface;
		};

	};

}

#define INTERFACE_DECLARE_OPERATORS(InterFaceName) \
public: \
	typedef FiniteStateMachineMeta::RTTI::CRTTIInterface<InterFaceName> Parent;\
	typedef Parent::Interface Interface;\
	enum { DEPTH = 0, };\
	\
	void Construct(const char* (*p_szNameFunc)(), int(*p_dwGetTypeFunc)())\
	{\
		FiniteStateMachineMeta::RTTI::CRTTIBase::GetClassName = p_szNameFunc;\
		FiniteStateMachineMeta::RTTI::CRTTIBase::GetType = p_dwGetTypeFunc;\
	}\

#define INSTANCE_DECLARE_OPERATORS(ParentName, InstanceName, Type) \
public: \
	typedef ParentName Parent;\
	typedef Parent::Interface Interface;\
	enum { DEPTH = Parent::DEPTH + 1, };\
	static const char* GetClassName() { return #InstanceName ; }\
	static int GetType() { return Type; }\

#define INTERFACE_FUNCTION(ReturnType, FunctionName, ...) \
	class FunctionName \
	{ \
	public: \
		virtual ReturnType operator()(##__VA_ARGS__) { assert(0); return ReturnType(); }; \
	}; \

class Test1 : public FiniteStateMachineMeta::RTTI::CRTTIInterface<Test1>
{
	INTERFACE_DECLARE_OPERATORS(Test1);

	INTERFACE_FUNCTION(int, TestFun, int);

	Test1(TestFun &ddd)
	:func1(ddd)
	{}

	TestFun func;
	TestFun& func1;
};

class Test2 : public Test1
{
	INSTANCE_DECLARE_OPERATORS(Test1, Test2, 2);

	class TestFun : public Interface::TestFun
	{
	public:
		virtual int operator()() { return 0; }
	};

	void Construct()
	{
		Interface::Construct(GetClassName, GetType);
	}

private:
	int b;
	TestFun t2;
};

class Test3 : public Test1
{
	INSTANCE_DECLARE_OPERATORS(Test1, Test3, 3);
	
	void Construct()
	{
		Interface::Construct(GetClassName, GetType);
	}

};

class Test4 : public Test3
{
	INSTANCE_DECLARE_OPERATORS(Test3, Test4, 4);

	class TestFun : public Interface::TestFun
	{
	public:
		TestFun(Test4& ref) : refTest4(ref) {}
		virtual int operator()(int a)
		{
			refTest4.d = 30;
			return refTest4.d;
		}
		int b = 0;

		Test4& refTest4;
	};

	void Construct()
	{
		//处理继承的方法
		new(&t2) TestFun(*this);
		//Interface::tt1 = &t2;

		new((Interface*)this) Interface(t2);

		Interface::Construct(GetClassName, GetType);

	}

	int d;

	TestFun t2;
};

union Content
{
	Content() {}
	Test1 t1;
	Test2 t2;
	Test3 t3;
	Test4 t4;
};







#endif // !__CRTTI_BASE_H__
