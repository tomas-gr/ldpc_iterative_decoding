#include <iostream>
#include <vector>
#include "decode.hpp"

using namespace std;

// Function to perform LDPC decoding using unanimous vote message passing
vector<int> ldpc_decode_unanimity(const vector<vector<int>> &H, vector<int> y, int max_iter) {
    int M = H.size();     // Number of check nodes
    int N = H[0].size();  // Number of variable nodes
    vector<int> x = y;    // Initialize decoded codeword

    for (int iter = 0; iter < max_iter; ++iter) {
        vector<vector<int>> messages(M, vector<int>(N, 0));
        vector<int> syndrome(M, 0);

        // Step 1: Compute Syndrome and Check Node Messages
        for (int i = 0; i < M; ++i) {
            int parity = 0;
            for (int j = 0; j < N; ++j) {
                if (H[i][j] == 1) parity ^= x[j];
            }
            syndrome[i] = parity;

            // Send messages to connected variable nodes
            for (int j = 0; j < N; ++j) {
                if (H[i][j] == 1) {
                    messages[i][j] = (syndrome[i] == 1) ? (1 - x[j]) : x[j];
                }
            }
        }

        // Step 2: Variable Node Updates (Unanimous Voting)
        bool updated = false;
        for (int j = 0; j < N; ++j) {
            vector<int> connected_cns;
            for (int i = 0; i < M; ++i) {
                if (H[i][j] == 1) connected_cns.push_back(i);
            }

            if (!connected_cns.empty()) {
                int suggested_value = messages[connected_cns[0]][j];
                bool unanimous = true;
                for (int i : connected_cns) {
                    if (messages[i][j] != suggested_value) {
                        unanimous = false;
                        break;
                    }
                }
                
                if (unanimous && suggested_value != x[j]) {
                    x[j] = suggested_value;
                    updated = true;
                }
            }
        }

        // Step 3: Stopping Condition
        bool all_satisfied = true;
        for (int i = 0; i < M; ++i) {
            int parity = 0;
            for (int j = 0; j < N; ++j) {
                if (H[i][j] == 1) parity ^= x[j];
            }
            if (parity != 0) {
                all_satisfied = false;
                break;
            }
        }
        if (all_satisfied || !updated) break;
    }
    
    return x;
}







// Example usage
// int main() {
//     vector<vector<int>> H = {
//         {1, 1, 0, 1, 0, 0}, 
//         {0, 1, 1, 0, 1, 0}, 
//         {1, 0, 1, 0, 0, 1}
//     };

//     vector<int> y = {1, 0, 1, 1, 0, 1};  // Received noisy codeword

//     vector<int> decoded = ldpc_decode_unanimity(H, y);
    
//     cout << "Decoded Codeword: ";
//     for (int bit : decoded) cout << bit << " ";
//     cout << endl;

//     return 0;
// }
