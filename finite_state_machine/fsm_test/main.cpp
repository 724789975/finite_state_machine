#include "test.h"
#include "rtti_base.h"
#include "t_bit_set.h"
#include "state_data.h"

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

	FiniteStateMachine::StateData<BitSet::ESecondBitSet, a> fsm;
	

	return 0;
}