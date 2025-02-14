#include <vector>
#include "matrix.hpp"


void inicializarMatriz(std::vector<std::vector<unsigned char>> &matriz, size_t rows, size_t cols) {
    matriz.resize(rows, std::vector<unsigned char>(cols, 0)); // Resize and initialize with 0
}

void inicializarVector(std::vector<unsigned char> &vector, size_t cols){
    vector.resize(cols, 0); // Resize and initialize with 0
}

void leerMatriz(unsigned char* H, size_t rows, size_t cols, std::vector<std::vector<unsigned char>> &vecH) {
    vecH.resize(rows, std::vector<unsigned char>(cols)); // Resize to match matrix dimensions

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            vecH[i][j] = H[i * cols + j]; // Accessing the flattened array
        }
    }
}

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