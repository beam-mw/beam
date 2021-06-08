#pragma once
//#include "../Eth.h"

namespace Bridge
{
    // Hash of the compiled shader bytecode
    static const ShaderID s_SID = { 0x54,0xe9,0x7c,0x19,0x3e,0x37,0x45,0xbb,0xde,0x87,0x64,0x96,0x31,0xc1,0x2c,0x53,0xec,0x2b,0x6f,0xaa,0xa6,0xf1,0xf9,0xe4,0x60,0xad,0xa2,0xc9,0x96,0x37,0xee,0x32 };

#pragma pack (push, 1) // the following structures will be stored in the node in binary form
    struct Header
    {
        Opaque<32> m_ParentHash;
        Opaque<32> m_UncleHash;
        Opaque<20> m_Coinbase;
        Opaque<32> m_Root;
        Opaque<32> m_TxHash;
        Opaque<32> m_ReceiptHash;
        Opaque<256> m_Bloom;
        Opaque<32> m_Extra;
        uint32_t m_nExtra; // can be less than maximum size

        uint64_t m_Difficulty;
        uint64_t m_Number; // height
        uint64_t m_GasLimit;
        uint64_t m_GasUsed;
        uint64_t m_Time;
        uint64_t m_Nonce;
    };

    struct Unlock
    {
        static const uint32_t s_iMethod = 2;
        /*uint32_t m_Amount;
        PubKey m_Pk;*/
    };

    struct Lock
    {
        static const uint32_t s_iMethod = 3;
        uint32_t m_Amount;
    };

    struct InMsg
    {
        uint32_t m_Amount;
        uint8_t m_Finalized;
        PubKey m_Pk;
    };

    struct ImportMessage
    {
        static const uint32_t s_iMethod = 4;
        InMsg m_Msg;
        Header m_Header;
        uint32_t m_ProofSize;
    };

    struct Finalized
    {
        static const uint32_t s_iMethod = 5;
    };
#pragma pack (pop)
}