#include <vector>



void inicializarMatriz(std::vector<std::vector<unsigned char>> &matriz, size_t rows, size_t cols);

void inicializarVector(std::vector<unsigned char> &vector, size_t cols);

void leerMatriz(unsigned char* H, size_t rows, size_t cols, std::vector<std::vector<unsigned char>> &vecH);

void productoMatriz(std::vector<std::vector<unsigned char>> &H, std::vector<unsigned char> &x, std::vector<unsigned char> &y);

void ANDMatriz(std::vector<std::vector<unsigned char>> &H, std::vector<unsigned char> &x, std::vector<std::vector<unsigned char>> &y);