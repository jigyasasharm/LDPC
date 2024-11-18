#ifndef LDPC_DECODER_H
#define LDPC_DECODER_H

#include <vector>


bool decodeLDPC_BP(const std::vector<double>& receivedSignal,
                   const std::vector<std::vector<int>>& parityCheckMatrix,
                   int maxIterations, int& iterationsUsed);

#endif
