#include <vector>
#include <cmath>
#include "../include/ldpc_decoder.h"

bool decodeLDPC_BP(const std::vector<double>& receivedSignal,
                   const std::vector<std::vector<int>>& parityCheckMatrix,
                   int maxIterations, int& iterationsUsed) {
    int numBits = receivedSignal.size();
    int numChecks = parityCheckMatrix.size();
    std::vector<std::vector<double>> messages(numChecks, std::vector<double>(numBits, 0));
    std::vector<double> likelihoodRatios(numBits);

    for (int i = 0; i < numBits; ++i) {
        likelihoodRatios[i] = log((1 + receivedSignal[i]) / (1 - receivedSignal[i]));
    }

    for (int iter = 0; iter < maxIterations; ++iter) {
        iterationsUsed = iter + 1;
        bool allChecksSatisfied = true;

  
        for (int i = 0; i < numChecks; ++i) {
            double product = 1.0;
            for (int j = 0; j < numBits; ++j) {
                if (parityCheckMatrix[i][j] == 1) {
                    product *= tanh(messages[i][j] / 2);
                }
            }
            double checkMessage = 2 * atanh(product);

            for (int j = 0; j < numBits; ++j) {
                if (parityCheckMatrix[i][j] == 1) {
                    double tempProduct = product / tanh(messages[i][j] / 2);
                    messages[i][j] = 2 * atanh(tempProduct);
                }
            }
        }

        std::vector<int> decodedBits(numBits, 0);
        for (int i = 0; i < numBits; ++i) {
            double totalLR = likelihoodRatios[i];
            for (int j = 0; j < numChecks; ++j) {
                if (parityCheckMatrix[j][i] == 1) {
                    totalLR += messages[j][i];
                }
            }
            decodedBits[i] = (totalLR < 0) ? 1 : 0;
        }

        for (int i = 0; i < numChecks; ++i) {
            int parity = 0;
            for (int j = 0; j < numBits; ++j) {
                if (parityCheckMatrix[i][j] == 1) {
                    parity ^= decodedBits[j];
                }
            }
            if (parity != 0) {
                allChecksSatisfied = false;
                break;
            }
        }

        if (allChecksSatisfied) {
            return true;
        }
    }
    return false;
}
