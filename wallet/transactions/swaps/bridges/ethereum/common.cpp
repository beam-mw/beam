// Copyright 2020 The Beam Team
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

#include "common.h"

#include <boost/multiprecision/cpp_int.hpp>
#include "utility/hex.h"

namespace beam::ethereum
{
std::string ConvertEthAddressToStr(const libbitcoin::short_hash& addr)
{
    return "0x" + libbitcoin::encode_base16(addr);
}

libbitcoin::short_hash ConvertStrToEthAddress(const std::string& addressStr)
{
    libbitcoin::short_hash address;
    libbitcoin::decode_base16(address, std::string(addressStr.begin() + 2, addressStr.end()));
    return address;
}

ECC::uintBig ConvertStrToUintBig(const std::string& number, bool hex)
{
    // TODO roman.strilets process prefix 0x
    libbitcoin::data_chunk dc;

    if (hex)
    {
        //libbitcoin::decode_base16(dc, number);
        dc = beam::from_hex(number);
    }
    else
    {
        boost::multiprecision::uint256_t value(number);
        std::stringstream stream;

        stream << std::hex << value;
        dc = beam::from_hex(stream.str());
    }

    ECC::uintBig result = ECC::Zero;
    std::copy(dc.crbegin(), dc.crend(), std::rbegin(result.m_pData));
    return result;
}
} // namespace beam::ethereum