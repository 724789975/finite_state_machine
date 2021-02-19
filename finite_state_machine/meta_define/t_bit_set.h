#ifndef __TBitSet_h__
#define __TBitSet_h__

#include <string.h>
#include <iostream>

namespace BitSet
{
	class BitSetInterface
	{
	public:
		virtual bool					SetBit(unsigned int e, bool bValue) = 0;
		virtual bool					GetBit(unsigned int e) const = 0;
		virtual unsigned int			GetCount() const = 0;
		virtual void					Reset() = 0;
		virtual void					DumpInfo(std::ostream& refStream) const = 0;
		virtual void					DumpInfoKV(std::ostream& refStream) const = 0;
	};
};

//这个类型的对象根本不会被创建成功
#define EnumBitSet(EnumName) \
namespace BitSet\
{\
	template<EnumName>\
	class T##EnumName##BitSet\
	{\
	private:\
		T##EnumName##BitSet(){class _error; _error err;}\
	};\
	template<>\
	class T##EnumName##BitSet<EnumName##Count> : public BitSet::BitSetInterface \
	{\
	public:\
		union Data\
		{\
			char szData[EnumName##Count / 8 + 1]; \
			long long llData[EnumName##Count / 64 + 1];\
		};\
		T##EnumName##BitSet(){memset(&m_unionData, 0, sizeof(m_unionData));}\
		virtual ~T##EnumName##BitSet(){}\
		bool SetBit(unsigned int e, bool bValue)\
		{\
			if (e >= EnumName##Count)\
			{\
				return false;\
			}\
			if (bValue)\
			{\
				m_unionData.szData[e / 8] |= (1 << (e % 8));\
			}\
			else\
			{\
				m_unionData.szData[e / 8] &= ~(1 << (e % 8));\
			}\
			return true;\
		}\
		bool GetBit(unsigned int e)const \
		{\
			if (e >= EnumName##Count)\
			{\
				return false;\
			}\
			return (m_unionData.szData[e / 8] & (1 << (e % 8))) != 0;\
		}\
		unsigned int GetCount() const \
		{\
			return (unsigned int)EnumName##Count;\
		}\
		bool operator < (const T##EnumName##BitSet<EnumName##Count> & ref) const\
		{\
			for(unsigned int i = 0; i < sizeof(m_unionData.llData) / sizeof(m_unionData.llData[0]); ++i)\
			{\
				if (this->m_unionData.llData[i] < ref.m_unionData.llData[i]) return true;\
			}\
			return false;\
		}\
		bool operator == (const T##EnumName##BitSet<EnumName##Count> & ref) const\
		{\
			return !(*this < ref) && !(ref < *this);\
		}\
		void Reset()\
		{\
			memset(&m_unionData, 0, sizeof(m_unionData));\
		}\
		void DumpInfo(std::ostream& refStream) const\
		{\
			for (unsigned int i = 0; i < EnumName##Count; ++i)\
			{\
				refStream << GetBit(i) ? 1 : 0;\
			}\
		}\
		void DumpInfoKV(std::ostream& refStream) const\
		{\
			for (unsigned int i = 0; i < EnumName##Count; ++i)\
			{\
				refStream << i << " : " << GetBit(i) << ", ";\
			}\
		}\
	private:\
		Data m_unionData;\
	};\
	typedef T##EnumName##BitSet<EnumName##Count> EnumName##BitSet;\
};

#define BeginEnumBitSet(EnumName) \
enum EnumName

#define EndEnumBitSetWithCount(EnumName, NUM) \
EnumName##Count = NUM,




#endif // !__TBitSet_h__
