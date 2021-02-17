#ifndef __StateData_H__
#define __StateData_H__

#include "t_bit_set.h"

//²âÊÔÊı¾İ?

namespace FiniteStateMachine
{
	template<typename BT, typename Data>
	class StateData : public BT, public Data
	{
	public:
		StateData()
		{}
		virtual ~StateData() {}

		bool						SetState(int eState);


	private:
		bool						CheckMutex(int eState);
	};

	template<typename BT, typename Data>
	bool StateData<BT, Data>::SetState(int eState)
	{
		if (!this->CheckMutex(eState))
		{
			return;
		}

		this->BT::SetState(eState);
	}

	template<typename BT, typename Data>
	bool StateData<BT, Data>::CheckMutex(int eState)
	{
		return false;
	}

};

#endif // !__StateData_H__
