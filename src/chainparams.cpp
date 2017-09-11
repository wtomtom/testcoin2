// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
 
#include "assert.h"
 
#include "chainparams.h"
#include "main.h"
#include "util.h"
 
#include <boost/assign/list_of.hpp>
 
using namespace boost::assign;
 
struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};
 
#include "chainparamsseeds.h"
 
//
// Main network
//
 
// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
 
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x76;
        pchMessageStart[1] = 0x38;
        pchMessageStart[2] = 0x26;
        pchMessageStart[3] = 0x18;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 18154;
        nRPCPort = 18155;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Testcoin tomtomcoinv2";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1505148039, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1505148039;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 563596;
 
 //printf("MainNet GenesisBlockHash %s\n", genesis.GetHash().ToString().c_str());
   //     printf("MainNet GenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
     //   printf("MainNet Hashmerkleroot %s\n", genesis.hashMerkleRoot.ToString().c_str());
      
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x9e2c556f5bd32ae4a935993f94db3167d4acab58e9a1ede7b86fe37e8b82763f"));
        assert(genesis.hashMerkleRoot == uint256("0x784e2a604572d39f690343b299b382a6ff79ee69b01f36a21e348332185b1e6d"));
		
		  
       // printf("Mainnet genesis.nTime = %u \n", genesis.nTime);
       // printf("Mainnet genesis.nNonce = %u \n", genesis.nNonce);
 // printf("Mainnet genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
     
	vSeeds.push_back(CDNSSeedData("testcoinnode.servep2p.com", "testcoinnode1.servep2p.com"));
 
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); //T
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 127); //t
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
 
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
 
        nLastPOWBlock = 200; //aprox 6 months, then its PURE POS.
    }
 
    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }
 
    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;
 
 
//
// Testnet
//
 
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 25714;
        nRPCPort = 25715;
        strDataDir = "testnet";
 
        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000724595fb3b9609d441cbfb9577615c292abf07d996d3edabc48de843642d"));
 
        vFixedSeeds.clear();
        vSeeds.clear();
 
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
 
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
 
        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;
 
 
//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1504888659;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x523dda6d336047722cbaf1c5dce622298af791bac21b33bf6e2d5048b2a13e3d"));
 
        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }
 
    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;
 
static CChainParams *pCurrentParams = &mainParams;
 
const CChainParams &Params() {
    return *pCurrentParams;
}
 
void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}
 
bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);
 
    if (fTestNet && fRegTest) {
        return false;
    }
 
    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
