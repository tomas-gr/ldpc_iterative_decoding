#include <vector>
#include "matrix.hpp"
#include "H6.h"
#include <iostream>


void inicializarMatriz(std::vector<std::vector<unsigned char>> &matriz, size_t rows, size_t cols) {
    matriz.resize(rows, std::vector<unsigned char>(cols, 0)); // Resize and initialize with 0
}

void inicializarVector(std::vector<unsigned char> &vector, size_t cols){
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

void productoMatriz(std::vector<std::vector<unsigned char>> &H, std::vector<unsigned char> &x, std::vector<unsigned char> &y) {
    size_t M = H.size();     // Numero de filas
    size_t N = H[0].size();  // Numero de columnas

    std::vector<unsigned char> res(M, 0); // Inicializar vector resultado

    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            res[i] ^= H[i][j] & x[j];
        }
        y[i] = res[i];
    }
}

void ANDMatriz(std::vector<std::vector<unsigned char>> &H, std::vector<unsigned char> &x, std::vector<std::vector<unsigned char>> &y) {
    size_t M = H.size();     // Numero de filas
    size_t N = H[0].size();  // Numero de columnas

    std::vector<unsigned char> res(M, 0); // Inicializar vector resultado

    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            y[i][j] = H[i][j] & x[j];
        }
    }
}

bool VectorEsNulo(std::vector<unsigned char> &vector){
    bool is_null = true;
    int i=0;
    while (is_null && i < vector.size()){
        is_null = vector[i] == 0;
        i++;
    }
    return is_null;
}

void imprimirMatriz(std::vector<std::vector<unsigned char>> &matriz){
    for (int i=0; i<matriz.size(); ++i){
        for (int j=0; j<matriz[i].size(); ++j){
            std::cout << (int)matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}