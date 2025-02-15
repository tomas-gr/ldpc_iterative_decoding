#include <vector>
#include "matrix.hpp"
#include "H6.h"
#include <iostream>


void initializeMatrix(std::vector<std::vector<unsigned char>> &matriz, size_t rows, size_t cols) {
    matriz.resize(rows, std::vector<unsigned char>(cols, 0)); // Resize and initialize with 0
}

void initializeVector(std::vector<unsigned char> &vector, size_t cols){
    vector.resize(cols, 0); // Resize and initialize with 0
}

// std::vector<std::vector<unsigned char>> leerMatriz() {
//     std::vector<std::vector<unsigned char>> vecH(_NROWS, std::vector<unsigned char>(_NCOLS));

//     for (size_t i = 0; i < _NROWS; ++i) {
//         for (size_t j = 0; j < _NCOLS; ++j) {
//             vecH[i][j] = H[i][j];  // Copy each element
//         }
//     }

//     return vecH;
// }

void productMatrix(const std::vector<std::vector<unsigned char>> &H, std::vector<unsigned char> &x, std::vector<unsigned char> &y) {
    size_t N = H.size();     // Numero de filas
    size_t M = H[0].size();  // Numero de columnas

    std::vector<unsigned char> res(N, 0); // Inicializar vector resultado

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            res[i] ^= H[i][j] & x[j];
        }
        y[i] = res[i];
    }
}

void ANDMatrix(const std::vector<std::vector<unsigned char>> &H, std::vector<unsigned char> &x, std::vector<std::vector<unsigned char>> &y) {
    size_t N = H.size();     // Numero de filas
    size_t M = H[0].size();  // Numero de columnas

    std::vector<unsigned char> res(N, 0); // Inicializar vector resultado

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            y[i][j] = H[i][j] & x[j];
        }
    }
}

bool VectorIsNull(std::vector<unsigned char> &vector){
    bool is_null = true;
    int i=0;
    while (is_null && i < vector.size()){
        is_null = vector[i] == 0;
        i++;
    }
    return is_null;
}

void syndromeMatrix(const std::vector<std::vector<unsigned char>> &H, std::vector<std::vector<unsigned char>> &R, std::vector<unsigned char> &s) {
    int N = H.size();     // Numero de filas
    int M = H[0].size();  // Numero de columnas

    /* Hacemos la multiplicación de H con R.t, pero nos quedamos solamente con la diagonal (como vector)*/
    for (int i=0; i<N; i++){
        s[i] = 0;

        for (int j = 0; j < M; ++j)
            s[i] ^= H[i][j] & R[i][j];
    }
}

void printMatrix(std::vector<std::vector<unsigned char>> &matriz){
    for (int i=0; i<matriz.size(); i++){
        for (int j=0; j<matriz[i].size(); j++){
            std::cout << (int)matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printVector(std::vector<unsigned char> &vector){
    for (int i=0; i<vector.size(); i++){
        std::cout << (int)vector[i] << " ";
    }
    std::cout << std::endl;
}