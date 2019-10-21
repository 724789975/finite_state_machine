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

#ifndef __META_ISENUM_H__
#define __META_ISENUM_H__

#include "meta/metabase.h"
#include "meta/isfundamental.h"
#include "meta/isfunction.h"

namespace FiniteStateMachineMeta {
	template< typename Type >
	struct IsEnum {
		enum {
			Result = !IsFundamental< Type >::Result &&
			!IsClass< Type >::Result &&
			!IsFunction< Type >::Result &&
			!IsCompound< Type >::Result
		};
	};
}

#endif
