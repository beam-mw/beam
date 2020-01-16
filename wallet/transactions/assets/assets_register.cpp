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
#include "assets_register.h"
#include "aissue_transaction.h"
#include "wallet/core/base_transaction.h"

namespace beam::wallet
{
    void RegisterAssetCreators(Wallet& wallet)
    {
        auto crIssue = std::make_shared<AssetIssueTransaction::Creator>(true);
        wallet.RegisterTransactionType(TxType::AssetIssue, std::static_pointer_cast<BaseTransaction::Creator>(crIssue));

        auto crConsume = std::make_shared<AssetIssueTransaction::Creator>(false);
        wallet.RegisterTransactionType(TxType::AssetConsume, std::static_pointer_cast<BaseTransaction::Creator>(crConsume));
    }
}