// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"

#include "arith_uint256.h"
#include "chain.h"
#include "chainparams.h"
#include "primitives/block.h"
#include "uint256.h"


unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock,
                                 const Consensus::Params& params)
{
    assert(pindexLast != nullptr);

    if(pindexLast->nHeight+1 < Params().SwitchLyra2REv2_LWMA())
    {
        // Original Bitcion PoW.
        return BitcoinGetNextWorkRequired(pindexLast, pblock, params);
    } else {
        // Zawy's LWMA.
        return LwmaGetNextWorkRequired(pindexLast, pblock, params);
    }
}

unsigned int LwmaGetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    // Special difficulty rule for testnet:
    // If the new block's timestamp is more than 2 * 10 minutes
    // then allow mining of a min-difficulty block.
    if (params.fPowAllowMinDifficultyBlocks &&
        pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing * 2) {
        return UintToArith256(params.powLimit).GetCompact();
    }
    return LinearWeightedMovingAverage(pindexLast, params);
}

// see. https://github.com/zawy12/difficulty-algorithms/issues/3#issuecomment-388386175
unsigned int static LinearWeightedMovingAverage(const CBlockIndex* pindexLast, const Consensus::Params& params) {
    if (params.fPowNoRetargeting) {  return pindexLast->nBits;   }
    // The FTL must be changed from 7200 to about NxT/10 or NxT/20 but I don't know where it
    // should be changed.  Maybe it is here:
    // static const int64_t MAX_FUTURE_BLOCK_TIME = 2 * 60 * 60;
    // but this affects a lot of things and BTG decided to create 2 variables where just 1 was lowered to 1/2
    // https://github.com/BTCGPU/BTCGPU/pull/296/commits/e803c163a680eeb49774f0bd9a24f6f3d7e5718b

    const int T = params.nPowTargetSpacing;
    const int N = Params().AveragingWindow();
    const int k = (N+1)/2*T*0.998;
    const int height = pindexLast->nHeight + 1;
    assert(height > N);

    arith_uint256 sum_target;
    int t = 0, j = 0;

    // Loop through N most recent blocks.
    for (int i = height - N; i < height; i++) {
         const CBlockIndex* block = pindexLast->GetAncestor(i);
         const CBlockIndex* block_Prev = block->GetAncestor(i - 1);
         int64_t solvetime = block->GetBlockTime() - block_Prev->GetBlockTime();
         // [zawy edit: bitcoin gold has implemented stricter limits on forward times and reverse times so
         // they do not need the limitation on solvetime as shown in the pseudocode ]
         j++;
         t += solvetime * j;  // Weighted solvetime sum.

         // Target sum divided by a factor, (k N^2).
         // The factor is a part of the final equation. However we divide sum_target
         // here to avoid potential overflow.
         arith_uint256 target;
         target.SetCompact(block->nBits);
         sum_target += target / (k * N * N);
    }
    // Keep t reasonable in case strange solvetimes occurred.
    // [zawy edit: change N * k/3 to "1" in both places. This caused new coins to get stuck ]
    if (t < N * k / 3) { t = N * k / 3; }
    arith_uint256 next_target = t * sum_target;

    return next_target.GetCompact();
}


unsigned int BitcoinGetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    assert(pindexLast != nullptr);
    unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

    // Only change once per difficulty adjustment interval
    if ((pindexLast->nHeight+1) % params.DifficultyAdjustmentInterval() != 0)
    {
        if (params.fPowAllowMinDifficultyBlocks)
        {
            // Special difficulty rule for testnet:
            // If the new block's timestamp is more than 2* 10 minutes
            // then allow mining of a min-difficulty block.
            if (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing*2)
                return nProofOfWorkLimit;
            else
            {
                // Return the last non-special-min-difficulty-rules-block
                const CBlockIndex* pindex = pindexLast;
                while (pindex->pprev && pindex->nHeight % params.DifficultyAdjustmentInterval() != 0 && pindex->nBits == nProofOfWorkLimit)
                    pindex = pindex->pprev;
                return pindex->nBits;
            }
        }
        return pindexLast->nBits;
    }

    // Go back by what we want to be 14 days worth of blocks
    int nHeightFirst = pindexLast->nHeight - (params.DifficultyAdjustmentInterval()-1);
    assert(nHeightFirst >= 0);
    const CBlockIndex* pindexFirst = pindexLast->GetAncestor(nHeightFirst);
    assert(pindexFirst);

    if(pindexLast->nHeight+1 >= Params().SwitchLyra2REv2_LWMA())
    {
        return LinearWeightedMovingAverage(pindexLast, params);
    }
    return CalculateNextWorkRequired(pindexLast, pindexFirst->GetBlockTime(), params);
}

unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
{
    if (params.fPowNoRetargeting)
        return pindexLast->nBits;

    // Limit adjustment step
    int64_t nActualTimespan = pindexLast->GetBlockTime() - nFirstBlockTime;
    if (nActualTimespan < params.nPowTargetTimespan/4)
        nActualTimespan = params.nPowTargetTimespan/4;
    if (nActualTimespan > params.nPowTargetTimespan*4)
        nActualTimespan = params.nPowTargetTimespan*4;

    // Retarget
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= params.nPowTargetTimespan;

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    return bnNew.GetCompact();
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params)
{
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}
