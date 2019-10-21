/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tencent is pleased to support the open source community by making behaviac available.
//
// Copyright (C) 2015-2017 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at http://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __META_METATYPES_H__
#define __META_METATYPES_H__

#include "meta/metabase.h"
#include "meta/removeconst.h"
#include "meta/removeref.h"
#include "meta/removeptr.h"
#include "meta/removeall.h"

#include "meta/pointertype.h"
#include "meta/reftype.h"

#include "meta/isenum.h"
#include "meta/isvector.h"
#include "meta/ismap.h"
#include "meta/isstruct.h"

#include "meta/ifthenelse.h"
#include "meta/hasfunction.h"

#include <string>

#define _BASETYPE_(T) typename FiniteStateMachineMeta::RemovePtr<typename FiniteStateMachineMeta::RemoveRef<T>::Result>::Result

#define REAL_BASETYPE(T) typename FiniteStateMachineMeta::RemoveConst<_BASETYPE_(T)>::Result

#define VALUE_TYPE(T) typename FiniteStateMachineMeta::RemoveConst<typename FiniteStateMachineMeta::RemoveRef<T>::Result>::Result
#define POINTER_TYPE(T) typename FiniteStateMachineMeta::PointerType<T>::Result

//class Agent;

namespace FiniteStateMachineMeta {
	template <typename T, bool bPtr>
	class ParamTypeConverter {
	public:
		typedef REAL_BASETYPE(T)		BaseType;
		typedef POINTER_TYPE(T)			PointerType;
	};

	template <>
	class ParamTypeConverter<const char*, true> {
	public:
		typedef std::string		BaseType;
		typedef const char** PointerType;
	};

	template<typename T>
	struct ParamCalledType {
	private:
		//can't remove const
		typedef typename FiniteStateMachineMeta::RefType<T>::Result										RefType_t;
	public:
		typedef typename FiniteStateMachineMeta::IfThenElse<FiniteStateMachineMeta::IsPtr<T>::Result, RefType_t, T>::Result Result;
	};

	//template <typename T>
	//struct IsAgent {
	//	typedef REAL_BASETYPE(T)		TBaseType;

	//	enum {
	//		Result = Meta::IsSame<Agent, TBaseType>::Result || Meta::IsDerived<Agent, TBaseType>::Result
	//	};
	//};

	template <typename T>
	struct TypeMapperTo {
		typedef T Type;
	};

	template <typename T>
	struct TIsRefType {
		enum {
			Result = false
		};
	};

	template <typename T, bool bHasFromString>
	struct IsRefTypeStruct {
		enum {
			Result = FiniteStateMachineMeta::TIsRefType<T>::Result
		};
	};

	//template <typename T>
	//class IsRefTypeStruct<T, true> {
	//public:
	//    enum {
	//        Result = T::ms_bIsRefType
	//    };
	//};

	//template <typename T>
	//struct IsRefType {
	//	typedef REAL_BASETYPE(T)						TBaseType;
	//	typedef typename TypeMapperTo<TBaseType>::Type	MappedType;
	//	enum {
	//		Result = behaviac::Meta::IsAgent<TBaseType>::Result || behaviac::Meta::IsRefTypeStruct<MappedType, behaviac::Meta::HasFromString<MappedType>::Result>::Result
	//	};
	//};
}//namespace Meta

#define PARAM_BASETYPE(T)		typename FiniteStateMachineMeta::ParamTypeConverter<T, FiniteStateMachineMeta::IsPtr<T>::Result>::BaseType
#define PARAM_POINTERTYPE(T)	typename FiniteStateMachineMeta::ParamTypeConverter<T, FiniteStateMachineMeta::IsPtr<T>::Result>::PointerType

#define PARAM_CALLEDTYPE(T)	typename FiniteStateMachineMeta::ParamCalledType<T>::Result
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


#endif//__META_METATYPES_H__
