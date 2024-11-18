#include <iostream>
#include <fstream>
#include "include/ldpc_matrix.h"
#include "include/awgn_channel.h"
#include "include/ldpc_decoder.h"
#include "src/awgn_channel.cpp"
#include "src/ldpc_decoder.cpp"
#include "src/ldpc_matrix.cpp"


int main() {
    int m = 100;
    int n = 200;
    int maxIterations = 16;
    int trials = 50;


    std::vector<std::vector<int>> H = generateParityCheckMatrix(m, n);

    std::vector<double> SNR_values = {-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28};

    std::ofstream outFile("SNR_vs_BER.csv");
    outFile << "SNR_dB,BER\n"; 

    for (double SNR_dB : SNR_values) {
        int totalErrors = 0;
        int totalBits = n * trials;

        for (int trial = 0; trial < trials; ++trial) {
            std::vector<double> all_zero_codeword(n, 1.0); // Transmit '0' as '+1' in BPSK


            std::vector<double> receivedSignal = transmitWithAWGN(all_zero_codeword, SNR_dB);


            int iterationsUsed;
            bool decodingSuccess = decodeLDPC_BP(receivedSignal, H, maxIterations, iterationsUsed);


            if (!decodingSuccess) {
                std::vector<int> decodedBits = decodeLDPC_BP(receivedSignal, H, maxIterations, iterationsUsed); // Modify decodeLDPC_BP to return decoded bits
                for (int i = 0; i < n; ++i) {
                        if (decodedBits[i] != originalBits[i]) {
                            totalErrors++;
                        }
                }
            } else {
                std::vector<int> decodedBits = decodeLDPC_BP(receivedSignal, H, maxIterations, iterationsUsed);
                for (int i = 0; i < n; ++i) {
                    if (decodedBits[i] != originalBits[i]) {
                        totalErrors++;
                        }
            }
        }


        double BER = static_cast<double>(totalErrors) / totalBits;
        

        outFile << SNR_dB << "," << BER << "\n";
        std::cout << "SNR (dB): " << SNR_dB << ", BER: " << BER << std::endl;
    }

    outFile.close(); 
    return 0;
}

