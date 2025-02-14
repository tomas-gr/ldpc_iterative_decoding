#include <iostream>
#include <vector>
#include <map>
#include "decode.hpp"

using namespace std;


void VCmessage(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &R, vector<unsigned char> &c, vector<unsigned char> &sindrome){
//    for (int i=0; i<sindrome.size(); i++){
//         if (sindrome[i] == 1){
//             for (int j=0; j)
//             R[i] = sindrome[i] ^ c[j];
//         }
//    }
}

void VNConnections(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &VNCon){
    int N = H.size();
    int M = H[0].size();
    int k = 0;

    for (int i=0; i<M; i++){
        k = 0;
        for (int j=0; j<N; j++){
            if (H[j][i] == 1){
                VNCon[i][k++] = j;
            }
        }
    }
}

void CNConnections(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &CNCon){
    int N = H.size();
    int M = H[0].size();
    int k = 0;

    for (int i=0; i<N; i++){
        k = 0;
        for (int j=0; j<M; j++){
            if (H[i][j] == 1){
                CNCon[i][k++] = j;
            }
        }
    }
}

vector<int> ldpc_decode_unanimity(const vector<vector<int>> &H, vector<int> y, int max_iter){
    return vector<int>();

}

