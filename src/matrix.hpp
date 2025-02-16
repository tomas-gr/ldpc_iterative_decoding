#include <vector>
#include "H6.h"

using namespace std;


void initializeMatrix(vector<vector<unsigned char>> &matriz, size_t rows, size_t cols);

void initializeVector(vector<unsigned char> &vector, size_t cols);

vector<vector<unsigned char>> leerMatriz(const unsigned char matriz[_NROWS][_NCOLS]);

std::vector<std::vector<size_t>> MatrizDispersa(const std::vector<std::vector<unsigned char>> &H);

void productoMatrizDispersa(const std::vector<std::vector<size_t>> &sparseH, 
                         const std::vector<unsigned char> &x, 
                         std::vector<unsigned char> &y);

void productMatrix(const vector<vector<unsigned char>> &H, vector<unsigned char> &x, vector<unsigned char> &y);

void ANDMatrix(const vector<vector<unsigned char>> &H, vector<unsigned char> &x, vector<vector<unsigned char>> &y);

bool VectorIsNull(vector<unsigned char> &vector);

void syndromeMatrix(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> R, vector<unsigned char> &s) ;

void printMatrix(vector<vector<unsigned char>> &matriz);

void printVector(vector<unsigned char> &vector);