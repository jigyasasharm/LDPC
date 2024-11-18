#ifndef AWGN_CHANNEL_H
#define AWGN_CHANNEL_H

#include <vector>


double addAWGNNoise(double transmittedBit, double SNR_dB);
std::vector<double> transmitWithAWGN(const std::vector<double>& codeword, double SNR_dB);

#endif
