#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include <tuple>
#include <chrono>
#include <algorithm>
#include <unordered_map>
#include "decode.hpp"
#include "matrix.hpp"

using namespace std;
using namespace std::chrono;


bool chequeoParidad(const MatrizDispersa &H, const vector<unsigned char> c_estimado){
    size_t r = H.size();     // Numero de filas
    size_t n = H[0].size();  // Numero de columnas
    int paridad;

    for (size_t i = 0; i < r; ++i) {
        paridad = 0;
        for (size_t j = 0; j < n; ++j) {
            paridad ^= H[i][j] & c_estimado[j];
        }
        if (paridad != 0) return false;
    }
    return true;
}

tuple<vector<unsigned char>, bool> ldpc_decode_unanimity(const MatrizDispersa &H_rows,  // Nonzero indices per check node
                                                         const MatrizDispersa &H_cols,  // Nonzero indices per variable node
                                                         vector<unsigned char> y,
                                                         int max_iter) {
    static bool first_success = true;
    static bool first_fail = true;
    
    int r = H_rows.size();  // Number of check nodes
    int n = H_cols.size();  // Number of variable nodes
    vector<unsigned char> c_estimado = y;

    for (int iter = 0; iter < max_iter; iter++) {

        /* Step 1: Check-to-Variable Messages */        
        vector<unordered_map<int, unsigned char>> check_a_var(r);

        for (int i = 0; i < r; i++) {
            int parity = 0;
            for (int v : H_rows[i]) {
                parity ^= c_estimado[v];
            }
            for (int v : H_rows[i]) {
                check_a_var[i][v] = parity ^ c_estimado[v];  // Exclude self
            }
        }


        /* Step 2: Variable-to-Check Messages */
        vector<unsigned char> c_estimado_new = c_estimado;

        for (int j = 0; j < n; j++) {
            vector<unsigned char> messages;
            for (int i : H_cols[j]) {
                messages.push_back(check_a_var[i][j]);
            }

            // Apply Unanimity Rule
            if (all_of(messages.begin(), messages.end(), [](int x) { return x == 1; })) {
                c_estimado_new[j] = 1;
            } else if (all_of(messages.begin(), messages.end(), [](int x) { return x == 0; })) {
                c_estimado_new[j] = 0;
            }
        }

        /* Step 3: Parity Check */        
        if (chequeoParidad(H_rows, c_estimado_new)) {
            return make_tuple(c_estimado_new, true);
        }

        c_estimado = c_estimado_new;
    }

    return make_tuple(y, false);
}

int corregir_archivo(const std::string_view inputFileName,
                    const std::string_view outputFileName,
                    MatrizDispersa H_rows,
                    MatrizDispersa H_cols, 
                    int max_iter) {

    int j = 3,k=4,n=1600,m=400,r=1200;
    
    // Abrir archivos binarios
    std::ifstream inputFile(inputFileName.data(), std::ios::binary);
    std::ofstream outputFile(outputFileName.data(), std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 0;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return 0;
    }

    // Cargar n bytes en buffer de caracteres y pasar a vector de enteros
    std::vector<char> buffer(n);
    std::vector<unsigned char> bloque(n);
    std::vector<char> bloque_deco(n-r,0);

    int total = 0;
    int errores = 0;
    int corregidos = 0;

    while(inputFile.read(buffer.data(),n)){
        std::streamsize bytes_read = inputFile.gcount();
        for (int i = 0; i < bytes_read; ++i){
            bloque[i] = static_cast<unsigned char>(buffer[i]);
        }

        /*------------------------------------------------------------------------*/
            // DECODIFICACION
        tuple<vector<unsigned char>,bool> decod = ldpc_decode_unanimity(H_rows,H_cols,bloque,max_iter);
        if (get<1>(decod)){
            corregidos++;
        }
        else{
            errores++;
        }

        // Imprimir cada 1000 palabras procesadas
        if (++total % 1000 == 0) {
            std::cout << "Palabras procesadas: " << total << std::endl;
            std::cout << "Cantidad de errores: " << errores << std::endl;
            std::cout << "Cantidad de correctas: " << corregidos << std::endl << std::endl;
            std::cout << "Tasa de error: " << (float)errores/(float)total << std::endl;
        }
        /*-------------------------------------------------------------------------*/
    
        // Escribir la palabra decodificada en archivo de salida
        outputFile.write(bloque_deco.data(), bytes_read);

    }
    std::cout << "Total de palabras procesadas: " << total << std::endl;
    std::cout << "Cantidad de errores: " << errores << std::endl << std::endl;
    std::cout << "Cantidad de correcciones: " << corregidos << std::endl;
    std::cout << "Tasa de corrección: " << (float)corregidos/(float)total << std::endl;

    outputFile.close();
    inputFile.close();

    return (1);
}



