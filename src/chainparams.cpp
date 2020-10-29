// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The Phore developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "bignum.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */
static bool regenerate = false;

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (     0, uint256("00000f62ca37e03539929b0fe54c61b46bb831b99e97df99194aae2fba346f45"))
    (  1000, uint256("39b4dfe99595f3a59fbd3cfaef5adb36a4f8b1e4168ae4586c0ac661b4f768bc"))
    ( 10000, uint256("9fb7cec5b3ef8297c51e5ace1af95bc2acc59c071a91ba2da42cc5becc391fa5"))
    ( 50000, uint256("246a5c558c887824af73f2388400f286eac7dc3da2095ca6b7f139ccaf5e84dc"))
    ( 75000, uint256("25e4b9f5fafa7df2a4f3ace2e23d3fab3120774e2aa1a4fbfe321f2ee8e57e73"))
    ( 100000, uint256("6a0f8abab031fec0fa0c97321b054d63640951798253aede93b07e0cc70d50a0"))
    ( 125000, uint256("53ad8076a93adc70ac7e898bb116f29274003a17a089dd91aa2cce7d64fff9c9"))
    ( 150000, uint256("1605fddb51984b3db5f3ab5bb0fa9a08b96a54eb654c32e0c325c12382d67eb8"))
    ( 175000, uint256("87ea07cb6db78cbd57b58e9005c06ff3590d1717b18ebe76234e3a48bc94d331"))
    ( 200000, uint256("d48c43dc84253e2edaf0d93fb2b9c6292626f20f10e348406dfc96dd7890a252"))
    ( 300000, uint256("76f6e5f92ec0a8b4716156a8192d8d37c0c6bf2ae47fb9ae98eb15b83f83dc87"))
    ( 350000, uint256("397b92a1551208c632afef5c20da983da3665e21c19af22ecdd7d7109961c5ac"))
    ( 400000, uint256("933d3dcd62741932de67b2cf419ff239d5c73975a66d559a9968d56f820aad88"))
    ( 450000, uint256("44f503a7f80832f775825bea5d606aef134397679e97e1c1fdca416c36c0dd47"))
    ( 500000, uint256("995982256e35c1cba890f2093368a8884df2e0174d7186b4bef2689ae796b619"))
    ( 550000, uint256("9af41a2d5a26f4745bf66a5dfb7fb70a2a3216a8bf0db7d992a945f60b3f87d2"))
    ( 570000, uint256("15615939e18f2408a5e2dfa17d98fd94ef55c5abbd442fa8febaef4b3070cdaa"))
    ( 600000, uint256("c8469964623b930e473c8852562a0e644f55c136386314233bdc13b6126aba6d"))
    ( 650000, uint256("e45b8a5166a4a189212c4eb4c66b535eb7e3b0dd9adda073366eef90d5bcd405"))
    ( 700000, uint256("37af59107608b938420f69876470498fcc1e14f1bf81ffabbd03aa2e92ff7747"));
    

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1564099465, // * UNIX timestamp of last checkpoint block
    100123,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("000007cb1c770414ded1b718165ad2484ebf905e343041ad03b7bc2022b6370d"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1561002031,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("000004b0de3c77b760d8849925be6bf68b667c1e09b6e238e16f847064d122c4"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1561001031,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x92;
        pchMessageStart[1] = 0xc5;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0xd4;
        vAlertPubKey = ParseHex("04659d53bd8f7ad9d34a17281febedac754e5a6eb136142d3a9c6c0ea21b6ed7498ceb3d872eed00ae755f7aeadaeb1d9ab5e1a8f1e7efcd0ddcb39d4623c12790");
        nDefaultPort = 18200;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Audax: 1 day
        nTargetSpacing = 1 * 60;  // Audax: 60 seconds
        nMaturity = 50;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 200000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 480;
        nModifierUpdateBlock = 1;        
		 
        const char* pszTimestamp = "Audaces Fortuna Juvat - June 20 2019";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1561003031;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 5407709;		
	
		hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";
            }
        } else {
            LogPrintf("Mainnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x00000f62ca37e03539929b0fe54c61b46bb831b99e97df99194aae2fba346f45"));
            assert(genesis.hashMerkleRoot == uint256("0xd5fa99ffeaf4a70e925a373485500de47eedff40dba142546ecf17826b7ebdb4"));
        }
		
		
        // Mainnet --- nonce: 5407709 time: 1561003031 hash: 0x00000f62ca37e03539929b0fe54c61b46bb831b99e97df99194aae2fba346f45 merklehash: 0xd5fa99ffeaf4a70e925a373485500de47eedff40dba142546ecf17826b7ebdb4

        vSeeds.push_back(CDNSSeedData("0", "audaxseed.audaxproject.io"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23); // AUDAX addresses start with 'A'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 8); // AUDAX script addresses start with '8'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 142); // AUDAX private keys start with 'z'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        nExtCoinType = 329;

        bech32_hrp = "bo";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "049b91c601a0cf8295fa665f5aa1ff4971b8fd0564c09102d7473a8251bfd1260cdd1ae14d535ecd76634afec9ad024f6f47a91e45924db9e5ce0330efcc40df45";
        strSporkKeyTemp = "046cc6f95590f050a08192e65f766c8fa7ff62dcfe42a3c3a7886bb8c5dd40d31ffc5057353365b9d44499ca981b7ccff7f53b40071de68d56d410347c62629d9c";
        strObfuscationPoolDummyAddress = "ALB4kES5ASrErPd7SKcTyw9nJ3xYkoXRAx";
        nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x48;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x35;
        pchMessageStart[3] = 0xc2;
        vAlertPubKey = ParseHex("04d7e13bc896eb07e2db2d7272f5ddfaedfb64b8ed4caa4d917d6e0781b59ca44f8b5d40995622008e40707b47687eebee11cbe3bbaf2348622cc271c7f0d0bd0a");
        nDefaultPort = 19200;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Audax: 1 day
        //nTargetSpacing = 1 * 10;  // Audax: 1 minute
		//nMaturity = 15;
        nTargetSpacing = 1 * 60;  // Audax: 1 minute
		nMaturity = 50;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1; 
        nMaxMoneyOut = 1000000000 * COIN;
        nLastPOWBlock = 480;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1561002031;
        genesis.nNonce = 1862643;
		
		hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Testnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x000007cb1c770414ded1b718165ad2484ebf905e343041ad03b7bc2022b6370d"));
            assert(genesis.hashMerkleRoot == uint256("0xd5fa99ffeaf4a70e925a373485500de47eedff40dba142546ecf17826b7ebdb4"));
        }
	
        // Testnet --- nonce: 1862643 time: 1561002031 hash: 0x000007cb1c770414ded1b718165ad2484ebf905e343041ad03b7bc2022b6370d merklehash: 0xd5fa99ffeaf4a70e925a373485500de47eedff40dba142546ecf17826b7ebdb4

        vFixedSeeds.clear();
        vSeeds.clear();


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 58); // Testnet audax addresses start with 'Q'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 66);  // Testnet audax script addresses start with 'T'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 56);     // Testnet private keys start with 'P'
        // Testnet audax BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet audax BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet audax BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        bech32_hrp = "tb";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKeyTemp = "04cb43fc5d2dd3750fa1e04ac37350dd740d8fe775e4e34d3acb7fd307b3c0005cb87d85b085bc2f42f4af4f928bf12e90bc99f0ff0787ee61bca2fb02d4a3e594";
        strSporkKey = "045b99b6c574b5ef03307352c9f8e854a90821c54cc3ca17c0cde061f4334f8a0c76643a329114956402552e69e55c33bed528fc4ba0ed4837c3273175ab7c2c1e";
        strObfuscationPoolDummyAddress = "QLB4kES5ASrErPd7SKcTyw9nJ3xYkoXRAx";
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                     // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x6e;
        pchMessageStart[3] = 0xc1;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Audax: 1 day
        nTargetSpacing = 1 * 60;        // Audax: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1561001031;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 832514;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nDefaultPort = 19205;
		
		hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtestnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Regtestnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x000004b0de3c77b760d8849925be6bf68b667c1e09b6e238e16f847064d122c4"));
            assert(genesis.hashMerkleRoot == uint256("0xd5fa99ffeaf4a70e925a373485500de47eedff40dba142546ecf17826b7ebdb4"));
        }
				
        // Regtestnet --- nonce: 12347 time: 1505224800 hash: 0x000004b0de3c77b760d8849925be6bf68b667c1e09b6e238e16f847064d122c4 merklehash: 0xd5fa99ffeaf4a70e925a373485500de47eedff40dba142546ecf17826b7ebdb4

        if (regenerate)
            exit(0);

        bech32_hrp = "brt";

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        strSporkKey = "04be8aa9cae2df33ffa2eb4b7285884320ad8b77ae079df0ae085d8d5027b9e93a7ece868bd10b6f0b75c895be34f582cf765e978133f022cd4a256e4a16af17de";
        strSporkKeyTemp = "04d3b43868dffd3ff123b3b5a3f558c23b35e3f26deb416c777f8cfa5bb84c03fd8ddff61eca4e80006a97211114713ef6441b37ddce67dfe86b5328f3cec0b4b3";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 19206;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        nExtCoinType = 1;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
