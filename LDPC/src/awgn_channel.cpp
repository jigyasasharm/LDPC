#include <vector>
#include <random>
#include <cmath>
#include "../include/awgn_channel.h"

std::default_random_engine generator(std::random_device{}());
std::normal_distribution<double> distribution(0.0, 1.0);

double addAWGNNoise(double transmittedBit, double SNR_dB) {
    double SNR_linear = pow(10, SNR_dB / 10.0);    
    double sigma = sqrt(1 / (2 * SNR_linear));
    distribution.param(std::normal_distribution<double>::param_type(0.0, sigma));
    double noise = distribution(generator);
    return transmittedBit + noise;
}

std::vector<double> transmitWithAWGN(const std::vector<double>& codeword, double SNR_dB) {
    std::vector<double> receivedSignal(codeword.size());
    for (size_t i = 0; i < codeword.size(); ++i) {
        receivedSignal[i] = addAWGNNoise(codeword[i], SNR_dB);
    }
    return receivedSignal;
}
