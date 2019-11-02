#include "test.h"
#include "rtti_base.h"

const uint64_t& func1()
{
	static uint64_t a = 1;
	return a;
}

int main()
{
	bool b = func1() == 1;

	Content c;
	c.t4.Construct();
	c.t1.TestFun(1);
	return 0;
}