// Copyright 2019 The Beam Team
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

#include "litecoin_electrum.h"

#include "bitcoin/bitcoin.hpp"

namespace {
    constexpr uint8_t kLitecoinMainnetP2KH = 48;
}

namespace beam
{
    LitecoinElectrum::LitecoinElectrum(io::Reactor& reactor, const LitecoinOptions& options)
        : BitcoinElectrum(reactor, options)
    {
    }

    uint8_t LitecoinElectrum::getAddressVersion() const
    {
        if (isMainnet())
        {
            return kLitecoinMainnetP2KH;
        }

        return libbitcoin::wallet::ec_private::testnet_p2kh;
    }

    std::string LitecoinElectrum::getCoinName() const
    {
        return "litecoin";
    }
}