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

#define USE_BASIC_CONFIG

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wunused-function"
#else
#	pragma warning (push, 0) // suppress warnings from secp256k1
#	pragma warning (disable: 4706) // assignment within conditional expression
#endif

#include "secp256k1-zkp/src/basic-config.h"
#include "secp256k1-zkp/include/secp256k1.h"
#include "secp256k1-zkp/src/scalar.h"
#include "secp256k1-zkp/src/group.h"
#include "secp256k1-zkp/src/hash.h"

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#	pragma GCC diagnostic pop
#else
#	pragma warning (default: 4706)
#	pragma warning (pop)
#endif

#define BeamCrypto_nBytes sizeof(secp256k1_scalar)
#define BeamCrypto_nBits (BeamCrypto_nBytes * 8)

typedef struct
{
	uint8_t m_pVal[BeamCrypto_nBytes];
} BeamCrypto_UintBig;

typedef struct
{
	// platform-independent EC point representation
	BeamCrypto_UintBig m_X;
	uint8_t m_Y;
} BeamCrypto_CompactPoint;

// Converting point representations is expensive.
// The following is a "flexible" point representation, which is converted on-demand according to the needs
typedef struct
{
	BeamCrypto_CompactPoint m_Compact; // platform-independent way. Suitable for serialization, hashing and etc.
	secp256k1_gej m_Gej; // Jacobian form (x,y,z)
	secp256k1_ge m_Ge; // Affine form (x,y)

	uint8_t m_Flags; // zero indicates 'invalid' point. Auto-set on a failed attempt to convert from m_Compact

} BeamCrypto_FlexPoint;

#define BeamCrypto_FlexPoint_Compact 1
#define BeamCrypto_FlexPoint_Gej 2
#define BeamCrypto_FlexPoint_Ge 4

void BeamCrypto_FlexPoint_MakeCompact(BeamCrypto_FlexPoint*);
void BeamCrypto_FlexPoint_MakeGej(BeamCrypto_FlexPoint*);
void BeamCrypto_FlexPoint_MakeGe(BeamCrypto_FlexPoint*);
