// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2017-2021 The c0ban Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <hash.h>
#include <tinyformat.h>

#include <crypto/Lyra2RE/Lyra2RE.h>

#define BEGIN(a)            ((char*)&(a))

uint256 CBlockHeader::GetHash() const
{
    return SerializeHash(*this);
}

uint256 CBlockHeader::GetPoWHash(bool bLyra2REv2, bool bLyra2REvc0ban) const
{
    if(bLyra2REv2){
        uint256 thash;
        if (bLyra2REvc0ban) {
            lyra2rec0ban_hash(BEGIN(nVersion), BEGIN(thash));
        }
        else {
            lyra2re2_hash(BEGIN(nVersion), BEGIN(thash));
        }
        return thash;
    }
    return GetHash();
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
