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
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xd1;
        vAlertPubKey = ParseHex("04b8d49de838594c2289037043e5330f12f4cb98f0a2f0cda90a2a957c3358c95480bb6db13fd5a50368c1f24096495eb473be801e5c919b0668a2f7acf74ed291");
        nDefaultPort = 48890;
        nRPCPort = 48891;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Ransomware is a “Rather Small” Phenomenon, AV-TEST Security Report Says | JP Buntinx | July 11, 2017";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1499806800, vin, vout, 0); 
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1499806800;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 2120726;

 /*
    Hashed MainNet Genesis Block Output
    block.hashMerkleRoot == 9e555106474965955abfa58b58b13ed9c84766e5171089de3de35c8850e34cab
    block.nTime = 1499806800
    block.nNonce = 2120726
    block.GetHash = 0000044761155635ed797d7652109dcf325c2ed9ae128430e24f3b3366fee290
        */       


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000044761155635ed797d7652109dcf325c2ed9ae128430e24f3b3366fee290"));
        assert(genesis.hashMerkleRoot == uint256("0x9e555106474965955abfa58b58b13ed9c84766e5171089de3de35c8850e34cab"));

        vSeeds.push_back(CDNSSeedData("ultraxcoin.thecryptochat.net", " "));
        vSeeds.push_back(CDNSSeedData("seed", "NULL"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 68);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 75);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 28);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 10000;
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
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0xc6;
        pchMessageStart[3] = 0xd7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 48892;
        nRPCPort = 48889;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 306946;

        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == f43214b95c7447197b3febdb1786f1bed5e130743abfc73beeed4f4c2c2fedfc
        block.nTime = 1503212400
        block.nNonce = 0
        block.GetHash = 50d32630ff04595e97bb278ac93a299f1c9887a7a04bad600f3542c692895422
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000b6fc7b14c6dae93bc702ed4bbfbb87d406cdd08e62768bee12d321f4854e"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 67);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 74);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 27);
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
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xb1;
        pchMessageStart[2] = 0xc2;
        pchMessageStart[3] = 0xd3;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1499806800;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 48893;
        strDataDir = "regtest";

       
        
        assert(hashGenesisBlock == uint256("0xbcdb2dd3235548e3a4dd157493cec574bd8eecfb5ef0894a0a9e51711353e056"));

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
