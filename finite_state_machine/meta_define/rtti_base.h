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
			CRTTIBase(const char* (*p_szNameFunc)(), int(*p_dwGetTypeFunc)()) 
				: GetClassName(p_szNameFunc)
				, GetType(p_dwGetTypeFunc) {}

			const char* (*GetClassName)();
			int (*GetType)();
		};

		template<typename T>
		class CRTTIInterface : public CRTTIBase
		{
		public:
			CRTTIInterface(const char* (*p_szNameFunc)(), int(*p_dwGetTypeFunc)())
				: CRTTIBase(p_szNameFunc, p_dwGetTypeFunc)
			{}
			typedef T Interface;
		};

	};

}

#define INTERFACE_DECLARE_OPERATORS(InterFaceName) \
public: \
	typedef FiniteStateMachineMeta::RTTI::CRTTIInterface<InterFaceName> Parent; \
	typedef Parent::Interface Interface; \
	enum { DEPTH = 0, }; \
	\
	void Construct(const char* (*p_szNameFunc)(), int(*p_dwGetTypeFunc)()) \
	{ \
		FiniteStateMachineMeta::RTTI::CRTTIBase::GetClassName = p_szNameFunc; \
		FiniteStateMachineMeta::RTTI::CRTTIBase::GetType = p_dwGetTypeFunc; \
	} \

#define INSTANCE_DECLARE_OPERATORS(ParentName, InstanceName, Type) \
public: \
	typedef ParentName Parent; \
	typedef Parent::Interface Interface; \
	enum { DEPTH = Parent::DEPTH + 1, }; \
	static const char* GetClassName() { return #InstanceName ; } \
	static int GetType() { return Type; } \

#define INTERFACE_FUNCTION_DECLEAR(ReturnType, FunctionName, ...) \
public: \
	class FunctionName##Interface \
	{ \
	public: \
		virtual ReturnType operator()(##__VA_ARGS__) = 0; \
	}; \
	FunctionName##Interface& FunctionName; \

#define INTERFACE_CONSTRUCT_BEGIN(Interface)\
	Interface(const char* (*p_szNameFunc)(), int(*p_dwGetTypeFunc)()

#define INTERFACE_CONSTRUCT_FUNCTION_BEGIN()\

#define INTERFACE_CONSTRUCT_FUNCTION(ReturnType, FunctionName, ...)\
	, FunctionName##Interface& ref_##FunctionName

#define INTERFACE_CONSTRUCT_FUNCTION_END()\
	)\
		: Parent(p_szNameFunc, p_dwGetTypeFunc)
	

#define INTERFACE_CONSTRUCT_FUNCTION_PARAM_BEGIN()\

#define INTERFACE_CONSTRUCT_FUNCTION_PARAM(ReturnType, FunctionName, ...)\
		, FunctionName(ref_##FunctionName)

#define INTERFACE_CONSTRUCT_FUNCTION_PARAM_END()\
		{}

#define INTERFACE_CONSTRUCT_END(Interface)\

#define INSTANCE_OPERATOR_FUNCTION_DECLEAR_BEGIN(Instance, ReturnType, FunctionName, ...) \
public: \
	friend class FunctionName; \
	class FunctionName : public Interface::FunctionName##Interface \
	{ \
	public: \
		FunctionName(Instance& ref) : refThis(ref) {} \
		virtual ReturnType operator()(##__VA_ARGS__); \
		Instance& refThis; \

#define INSTANCE_OPERATOR_FUNCTION_DECLEAR_END(Instance, ReturnType, FunctionName, ...) \
	}; \
	public: \
	FunctionName m_o##FunctionName; \

#define INSTANCE_OPERATOR_FUNCTION_DEFINE_BEGIN(Instance, ReturnType, FunctionName, ...) \
	ReturnType Instance::FunctionName::operator()(__VA_ARGS__) \

#define INSTANCE_OPERATOR_FUNCTION_DEFINE_END(Instance, ReturnType, FunctionName, ...) \

#define INSTANCE_CONSTRUCT_OPERATOR(Instance, ReturnType, FunctionName, ...) \
	new(&m_o##FunctionName) FunctionName(*this);

#define INSTANCE_CONSTRUCT_BEGIN() \
		new((Interface*)this) Interface(GetClassName, GetType

#define INSTANCE_CONSTRUCT_FUNCTION(Instance, ReturnType, FunctionName, ...) \
	, m_o##FunctionName

#define INSTANCE_CONSTRUCT_END() \
	);

class Test1 : public FiniteStateMachineMeta::RTTI::CRTTIInterface<Test1>
{
	INTERFACE_DECLARE_OPERATORS(Test1);

	INTERFACE_FUNCTION_DECLEAR(int, TestFun, int a);
	INTERFACE_FUNCTION_DECLEAR(int, TestFun2, float a);

	INTERFACE_CONSTRUCT_BEGIN(Test1)
	INTERFACE_CONSTRUCT_FUNCTION_BEGIN()
	INTERFACE_CONSTRUCT_FUNCTION(int, TestFun, int a)
	INTERFACE_CONSTRUCT_FUNCTION(int, TestFun2, float a)
	INTERFACE_CONSTRUCT_FUNCTION_END()
	INTERFACE_CONSTRUCT_FUNCTION_PARAM_BEGIN()
	INTERFACE_CONSTRUCT_FUNCTION_PARAM(int, TestFun, int a)
	INTERFACE_CONSTRUCT_FUNCTION_PARAM(int, TestFun2, float a)
	INTERFACE_CONSTRUCT_FUNCTION_PARAM_END()
	INTERFACE_CONSTRUCT_END(Test1)
};

class Test2 : public Test1
{
	INSTANCE_DECLARE_OPERATORS(Test1, Test2, 2);

	class TestFun : public Interface::TestFunInterface
	{
	public:
		virtual int operator()(int a) { return 0; }
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

	INSTANCE_OPERATOR_FUNCTION_DECLEAR_BEGIN(Test4, int, TestFun, int a);
	int b = 4;
	INSTANCE_OPERATOR_FUNCTION_DECLEAR_END(Test4, int, TestFun, int a);

	INSTANCE_OPERATOR_FUNCTION_DECLEAR_BEGIN(Test4, int, TestFun2, float a);
	int b = 4;
	INSTANCE_OPERATOR_FUNCTION_DECLEAR_END(Test4, int, TestFun2, float a);

	void Construct()
	{
		//处理继承的方法
		INSTANCE_CONSTRUCT_OPERATOR(Test4, int, TestFun, int a);
		INSTANCE_CONSTRUCT_OPERATOR(Test4, int, TestFun2, float a);

		INSTANCE_CONSTRUCT_BEGIN()
		INSTANCE_CONSTRUCT_FUNCTION(Test4, int, TestFun, int a)
		INSTANCE_CONSTRUCT_FUNCTION(Test4, int, TestFun2, float a)
		INSTANCE_CONSTRUCT_END();
	}

	int d;
};

INSTANCE_OPERATOR_FUNCTION_DEFINE_BEGIN(Test4, int, TestFun, int a)
{
	refThis.d = 30;
	return refThis.d;
}
INSTANCE_OPERATOR_FUNCTION_DEFINE_END(Test4, int, TestFun, int a);

INSTANCE_OPERATOR_FUNCTION_DEFINE_BEGIN(Test4, int, TestFun2, float a)
{
	refThis.d = 30;
	return refThis.d;
}
INSTANCE_OPERATOR_FUNCTION_DEFINE_END(Test4, int, TestFun, int a);

union Content
{
	Content() {}
	Test1 t1;
	Test2 t2;
	Test3 t3;
	Test4 t4;
};







#endif // !__CRTTI_BASE_H__
