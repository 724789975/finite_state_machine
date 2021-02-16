#include "test.h"
#include "rtti_base.h"
#include "t_bit_set.h"

const uint64_t& func1()
{
	static uint64_t a = 1;
	return a;
}

BeginEnumBitSet(ESecond)
{
	EndEnumBitSetWithCount(ESecond, 60)
};

EnumBitSet(ESecond);

int main()
{
	BitSet::ESecondBitSet es;
	

	return 0;
}