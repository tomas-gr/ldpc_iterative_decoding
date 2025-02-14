#include <vector>



void initializeMatrix(std::vector<std::vector<unsigned char>> &matriz, size_t rows, size_t cols);

void initializeVector(std::vector<unsigned char> &vector, size_t cols);

// std::vector<std::vector<unsigned char>> leerMatriz();

void productMatrix(std::vector<std::vector<unsigned char>> &H, std::vector<unsigned char> &x, std::vector<unsigned char> &y);

void ANDMatrix(std::vector<std::vector<unsigned char>> &H, std::vector<unsigned char> &x, std::vector<std::vector<unsigned char>> &y);

bool VectorIsNull(std::vector<unsigned char> &vector);

void printMatrix(std::vector<std::vector<unsigned char>> &matriz);

void printVector(std::vector<unsigned char> &vector);