#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

std::vector<std::vector<int>> generateParityCheckMatrix(int m, int n) {
    std::vector<std::vector<int>> H(m, std::vector<int>(n, 0));

    std::vector<int> rowCounts(m, 0); 
    std::vector<int> colCounts(n, 0); 

    for (int col = 0; col < n; ++col) {
        int placedOnes = 0;
        while (placedOnes < 3) {
            int row = std::rand() % m; 
            if (H[row][col] == 0 && rowCounts[row] < 6) {
                H[row][col] = 1;
                rowCounts[row]++;
                colCounts[col]++;
                placedOnes++;
            }
        }
    }


    for (int row = 0; row < m; ++row) {
        while (rowCounts[row] < 6) {
            int col = std::rand() % n;
            if (H[row][col] == 0 && colCounts[col] < 3) {
                H[row][col] = 1;
                rowCounts[row]++;
                colCounts[col]++;
            }
        }
    }

    return H;
}


