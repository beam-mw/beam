// Copyright 2018 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

// Common ord types (clang seems to miss them)
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed int int32_t;
typedef signed short int16_t;
typedef signed long long int64_t;

typedef uint64_t Amount;
typedef uint32_t AssetID;

#pragma pack (push, 1)

template <uint32_t nBytes>
struct Opaque {
    uint8_t m_p[nBytes];
};

#pragma pack (pop)

typedef Opaque<33> PubKey;
typedef Opaque<32> ContractID;

// environment functions
#include "../bvm2_opcodes.h"

namespace Env {

    extern "C" {

#define PAR_DECL(type, name) type name
#define COMMA ,
#define THE_MACRO(id, ret, name) \
        ret name(BVMOp_##name(PAR_DECL, COMMA));

        BVMOpsAll(THE_MACRO)

#undef THE_MACRO
#undef COMMA
#undef PAR_DECL
    } // extern "C"

    template <typename TKey, typename TVal>
    inline bool LoadVar_T(const TKey& key, TVal& val)
    {
        return LoadVar(&key, sizeof(key), &val, sizeof(val)) == sizeof(val);
    }

    template <typename TKey, typename TVal>
    inline void SaveVar_T(const TKey& key, const TVal& val)
    {
        SaveVar(&key, sizeof(key), &val, sizeof(val));
    }

    template <typename TKey>
    inline void DelVar_T(const TKey& key)
    {
        SaveVar(&key, sizeof(key), nullptr, 0);
    }

    inline void Halt_if(bool b)
    {
        if (b)
            Halt();
    }

} // namespace Env

#define export __attribute__( ( visibility( "default" ) ) ) extern "C"

// the following is useful for Amount manipulation, while ensuring no overflow
namespace Strict {

    template <typename T>
    inline void Add(T& a, const T& b)
    {
        a += b;
        Env::Halt_if(a < b); // overflow
    }

    template <typename T>
    inline void Sub(T& a, const T& b)
    {
        Env::Halt_if(a < b); // not enough
        a -= b;
    }

} // namespace Strict
