#include <vector>
#include "matrix.hpp"
#include "H6.h"
#include <iostream>

using namespace std;

void convertirADispersa(const vector<vector<unsigned char>> &H, MatrizDispersa &H_rows, MatrizDispersa &H_cols) {
    int r = H.size();
    int n = H[0].size();
    
    H_rows.resize(r);
    H_cols.resize(n);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < n; j++) {
            if (H[i][j] == 1) {
                H_rows[i].push_back(j);
                H_cols[j].push_back(i);
            }
        }
    }
}

vector<vector<unsigned char>> leerMatriz(const unsigned char matriz[_NROWS][_NCOLS]){

    vector<vector<unsigned char>> vec(_NROWS, vector<unsigned char>(_NCOLS, 0));
    for (int i =0; i<_NROWS; i++){
        for (int j=0; j<_NCOLS; j++){
            vec[i][j] = matriz[i][j];
        }
    }
    return vec;
}

bool VectorIsNull(vector<unsigned char> &vector){
    for (unsigned char val : vector) {
        if (val != 0) return false;
    }
    return true;
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