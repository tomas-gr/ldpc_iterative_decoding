#include <vector>
#include "matrix.hpp"
#include "H6.h"
#include <iostream>

using namespace std;


void initializeMatrix(vector<vector<unsigned char>> &matriz, size_t rows, size_t cols) {
    matriz.resize(rows, vector<unsigned char>(cols, 0)); // Resize and initialize with 0
}

void initializeVector(vector<unsigned char> &vector, size_t cols){
    vector.resize(cols, 0); // Resize and initialize with 0
}

vector<vector<unsigned char>> leerMatriz(unsigned char matriz[_NROWS][_NCOLS]){

    vector<vector<unsigned char>> vec(1200, vector<unsigned char>(1600, 0));
    for (int i =0; i<1200; i++){
        for (int j=0; j<1600; j++){
            vec[i][j] = matriz[i][j];
        }
    }
    return vec;
}

void productMatrix(const vector<vector<unsigned char>> &H, vector<unsigned char> &x, vector<unsigned char> &y) {
    size_t N = H.size();     // Numero de filas
    size_t M = H[0].size();  // Numero de columnas

    vector<unsigned char> res(N, 0); // Inicializar vector resultado

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            res[i] ^= H[i][j] & x[j];
        }
        y[i] = res[i];
    }
}

void ANDMatrix(const vector<vector<unsigned char>> &H, vector<unsigned char> &x, vector<vector<unsigned char>> &y) {
    size_t N = H.size();     // Numero de filas
    size_t M = H[0].size();  // Numero de columnas

    vector<unsigned char> res(N, 0); // Inicializar vector resultado

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            y[i][j] = H[i][j] & x[j];
        }
    }
}

bool VectorIsNull(vector<unsigned char> &vector){
    bool is_null = true;
    int i=0;
    while (is_null && i < vector.size()){
        is_null = vector[i] == 0;
        i++;
    }
    return is_null;
}

void syndromeMatrix(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &R, vector<unsigned char> &s) {
    int N = H.size();     // Numero de filas
    int M = H[0].size();  // Numero de columnas

    /* Hacemos la multiplicación de H con R.t, pero nos quedamos solamente con la diagonal (como vector)*/
    for (int i=0; i<N; i++){
        s[i] = 0;

        for (int j = 0; j < M; ++j)
            s[i] ^= H[i][j] & R[i][j];
    }
}

void printMatrix(vector<vector<unsigned char>> &matriz){
    for (int i=0; i<matriz.size(); i++){
        for (int j=0; j<matriz[i].size(); j++){
            cout << (int)matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void printVector(vector<unsigned char> &vector){
    for (int i=0; i<vector.size(); i++){
        cout << (int)vector[i] << " ";
    }
    cout << endl;
}