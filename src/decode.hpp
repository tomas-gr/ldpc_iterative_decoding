#include <vector>
#include <map>
#include "matrix.hpp"

using namespace std;


bool chequeoParidad(const MatrizDispersa &H, const vector<unsigned char> c_estimado);

tuple<vector<unsigned char>, bool, int> ldpc_decode_unanimity(const MatrizDispersa &H_rows,  // Nonzero indices per check node
                                                         const MatrizDispersa &H_cols,  // Nonzero indices per variable node
                                                         vector<unsigned char> y,
                                                         int max_iter);

int corregir_archivo(const std::string_view inputFileName,
                    const std::string_view outputFileName,
                    MatrizDispersa H_rows,
                    MatrizDispersa H_cols, 
                    int max_iter);
