#include "test.h"
#include "rtti_base.h"
#include "t_bit_set.h"
#include "state_data.h"

#include <iostream>

const uint64_t& func1()
{
	static uint64_t a = 1;
	return a;
}

BeginEnumBitSet(ESecond)
{
	EndEnumBitSetWithCount(ESecond, 512)
};

EnumBitSet(ESecond);

class a
{
public:
	a() {};
	~a() {}
private:

};
int main()
{
	BitSet::ESecondBitSet es;
	BitSet::ESecondBitSet es2;
	//es.m_unionData.llData[0] = 0;

	std::cout << (es == es2) << "\n";
	es.SetBit(9, true);
	es2.SetBit(1, true);
	//es.SetBit(73, true);
	//es2.SetBit(65, true);
	std::cout << (es < es2) << "\n";
	std::cout << (es == es2) << "\n";

	FiniteStateMachine::StateData<BitSet::ESecondBitSet, a> fsm;
	

	return 0;
}