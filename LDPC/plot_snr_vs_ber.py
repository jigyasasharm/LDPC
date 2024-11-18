import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv("SNR_vs_BER.csv")


snr_dB = data["SNR_dB"]
ber = data["BER"]


plt.figure(figsize=(10, 6))
plt.plot(snr_dB, ber, marker='o', linestyle='-', color='b', label="BER vs SNR")

plt.title("SNR vs BER for LDPC Code over AWGN Channel")
plt.xlabel("SNR (dB)")
plt.ylabel("BER (Bit Error Rate)")
plt.yscale("log") 
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.legend()


plt.show()


