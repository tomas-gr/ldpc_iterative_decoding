#include <vector>
#include "H6.h"

using namespace std;
using MatrizDispersa = vector<vector<unsigned int>>;

void convertirADispersa(const vector<vector<unsigned char>> &H, MatrizDispersa &H_rows, MatrizDispersa &H_cols);

vector<vector<unsigned char>> leerMatriz(const unsigned char matriz[_NROWS][_NCOLS]);

bool VectorIsNull(vector<unsigned char> &vector);

void printMatrix(vector<vector<unsigned char>> &matriz);

void printVector(vector<unsigned char> &vector);