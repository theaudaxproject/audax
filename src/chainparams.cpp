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
    (     0, uint256("00000e5ce2c60eb83f8e2984931c17bd467763a1e7ec6d8a5bf00c5776db7025"));
    

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1554367099, // * UNIX timestamp of last checkpoint block
    0,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0000050a6607f14c0f30aa738604cedd8608152e3be729477cd509d9c1d5f772"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1554366099,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("000004993c18ca5c7555bd9edbc7a693c39792618d616a5f84301a8b8b8ac91b"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1554365099,
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

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
		 
        const char* pszTimestamp = "Bitcoin Block #3940: 0000000033d217c1a40ef8f42c06205bc9059e2a43756ebb1a3a4f364fc78810";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1554367099;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 4417337;
		
	//=================================================
	/*
	hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("0x"))
        {
        printf("MSearching for genesis block...\n");
        uint256 hashTarget;
        hashTarget.SetCompact(genesis.nBits);
        while(uint256(genesis.GetHash()) > uint256(hashTarget))
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("Mainnet NONCE WRAPPED, incrementing time");
                std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
               printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }
        printf("Mainnet block.nTime = %u \n", genesis.nTime);
        printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
        printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
		
	*/	

//============================================================

	
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
            assert(hashGenesisBlock == uint256("0x00000e5ce2c60eb83f8e2984931c17bd467763a1e7ec6d8a5bf00c5776db7025"));
            assert(genesis.hashMerkleRoot == uint256("0xb34f5b46eb99e9bd8d68cd759e29e774d5af1757dc23a5b404aeb2a4603c4c27"));
        }
		
		
		//=================================================
		
        // Mainnet --- nonce: 1 time: 1536266133 hash: 0x0b58ed450b3819ca54ab0054c4d220ca4f887d21c9e55d2a333173adf76d987f merklehash: 0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e

        vSeeds.push_back(CDNSSeedData("0", "dns1.cryptotron.xyz"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23); // AUDAX addresses start with 'A'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 8); // AUDAX script addresses start with '8'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 142); // AUDAX private keys start with 'z'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x01)(0x22).convert_to_container<std::vector<unsigned char> >();

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
        strSporkKey = "04615040cee8445d8cdd48e41b72e487e3a1c0065c4727c1700a27a74e16285997b33a6f2b0ee9343442409d67e78f78f48bf925b3b4e21d4a7cf9776787337d3c";
        strSporkKeyTemp = "04ecf30a20336ec7ff165159a91b16468d92a74571b7e80400f1a661fdeec7322c2de30523360eb55f08f1a6709d20aa5815b802a8b48224318d6de6e2b7ce1a1d";
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
        genesis.nTime = 1554366099;
        genesis.nNonce = 1167308;
		
		//==========================

	/*
	hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("0x"))
        {
        printf("MSearching for genesis block...\n");
        uint256 hashTarget;
        hashTarget.SetCompact(genesis.nBits);
        while(uint256(genesis.GetHash()) > uint256(hashTarget))
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("Mainnet NONCE WRAPPED, incrementing time");
                std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
               printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }
        printf("Testnet block.nTime = %u \n", genesis.nTime);
        printf("Testnet block.nNonce = %u \n", genesis.nNonce);
        printf("Testnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("Testnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
	
	*/
		//===================
		
	
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
            assert(hashGenesisBlock == uint256("0x0000050a6607f14c0f30aa738604cedd8608152e3be729477cd509d9c1d5f772"));
            assert(genesis.hashMerkleRoot == uint256("0xb34f5b46eb99e9bd8d68cd759e29e774d5af1757dc23a5b404aeb2a4603c4c27"));
        }
	
	
		//========================
		
        // Testnet --- nonce: 1 time: 1505224800 hash: 0x7fbf5849b7a8602fecd2d5e4465b3d4f0bfb482b02c87388b925009d14ba7e42 merklehash: 0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e

        //vFixedSeeds.clear();
        //vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("1", "dns1.cryptotron.xyz"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 58); // Testnet audax addresses start with 'Q'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 66);  // Testnet audax script addresses start with 'T'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 56);     // Testnet private keys start with 'P'
        // Testnet audax BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet audax BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet audax BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

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
        genesis.nTime = 1554365099;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 796871;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nDefaultPort = 19205;
		
		//=========================

	/*
	hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("0x"))
        {
        printf("MSearching for genesis block...\n");
        uint256 hashTarget;
        hashTarget.SetCompact(genesis.nBits);
        while(uint256(genesis.GetHash()) > uint256(hashTarget))
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("Mainnet NONCE WRAPPED, incrementing time");
                std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
               printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }
        printf("Regnet block.nTime = %u \n", genesis.nTime);
        printf("Regnet block.nNonce = %u \n", genesis.nNonce);
        printf("Regnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("Regnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
	
	*/

		//===============
		
		
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
            assert(hashGenesisBlock == uint256("0x000004993c18ca5c7555bd9edbc7a693c39792618d616a5f84301a8b8b8ac91b"));
            assert(genesis.hashMerkleRoot == uint256("0xb34f5b46eb99e9bd8d68cd759e29e774d5af1757dc23a5b404aeb2a4603c4c27"));
        }
	
		//===============================
		
        // Regtestnet --- nonce: 12347 time: 1505224800 hash: 0x613e35c5b607586d3f5b8b109d162eac5fca0be0b0fa282277092e8dea8af138 merklehash: 0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e

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
