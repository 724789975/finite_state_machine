#pragma once
#include "meta/meta.h"

class A
{
public:
	virtual void fun() = 0;
protected:
private:
};

class B : public A
{
public:
	B()
	{
	}

	~B()
	{
	}
	virtual void fun(){}
private:

};



