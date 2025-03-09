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
    size_t r = H.size();     // Numero de nodos check
    size_t n = H[0].size();  // Numero de nodos variable conectados a check
    int paridad;
    for (size_t i = 0; i < r; i++) {
        paridad = 0;
        for (size_t j = 0; j < n; j++) {
            paridad ^= c_estimado[H[i][j]];
        }
        if (paridad != 0) return false;
    }
    return true;
}

tuple<vector<unsigned char>, bool> ldpc_decode_unanimity(const MatrizDispersa &H_rows,
                                                         const MatrizDispersa &H_cols,
                                                         vector<unsigned char> y,
                                                         int max_iter) {
    // static bool first_success = true;
    // static bool first_fail = true;
    
    int r = H_rows.size();  // Cantidad de nodos de check
    int n = H_cols.size();  // Cantidad de nodos de variable

    /* Chequeo de paridad inicial */        
    if (chequeoParidad(H_rows, y)) {
        return make_tuple(y, true);
    }


    /* Paso 0: Mensaje inicial de variable a check */
    vector<unsigned char> c_estimado = y;
    vector<unordered_map<int,unsigned char>> mensaje_vc(n);
    vector<unordered_map<int, unsigned char>> mensaje_cv(r);

    for (int j = 0; j < n; j++) {
        for (int i : H_cols[j]) {
            // Para cada nodo de variable j, se envía el valor de y[j] a los nodos de check conectados a j
            mensaje_vc[j].insert({i, c_estimado[j]});
        }
    }

    for (int iter = 0; iter < max_iter; iter++) {
        /* Paso 1: Mensajes de check a variable */    


        // Para cada nodo de check
        for (int i = 0; i < r; i++) {
            // Para cada nodo de variable conectado a i
            for (int j : H_rows[i]) {
                unsigned char message = 0;
                for (auto m : mensaje_vc[i]) {
                    // Suma modulo dos (xor) de los mensajes recibidos por i, excepto el mensaje enviado por j
                    if (m.first != j) {
                        message ^= m.second;
                    }
                    // Se almacena el mensaje recibido por i
                    mensaje_vc[j].insert({i, message});
                }
                mensaje_cv[i].clear();
            }
        }


        // Para cada nodo de variable    
        for (int j = 0; j < n; j++) {
            unsigned char message = 0;
            for (int i : H_cols[j]) {
                // Para cada nodo de check conectado a j
                for (auto m : mensaje_vc[i]) {
                    // Suma modulo dos (xor) de los mensajes recibidos por i, excepto el mensaje enviado por j
                    if (m.first != j) {
                        message ^= m.second;
                    }
                    // Se almacena el mensaje recibido por j
                    mensaje_cv[i].insert({j, message});
                }
                mensaje_vc[i].clear();
            }
        }



        /* Paso 2: Mensajes de variable a check */

        // Para cada nodo de check
        for (int i = 0; i < r; i++) {
            // Si todos los mensajes recibidos por i son iguales, se envía ese mensaje a los nodos de variable conectados a i
            if (all_of(mensaje_cv[i].begin(), mensaje_cv[i].end(), [](const auto &m) { return m.second == 1; })) {
                for (int j : H_rows[i]) {
                    mensaje_vc[j].insert({i, 1});
                }
                c_estimado[i] = 1;

            } else if (all_of(mensaje_cv[i].begin(), mensaje_cv[i].end(), [](const auto &m) { return m.second == 0;})) {
                for (int j : H_rows[i]) {
                    mensaje_vc[j].insert({i, 0});
                }
                c_estimado[i] = 0;
            }
            mensaje_cv[i].clear();
        }

        /* Paso 3: Parity Check */    
        if (chequeoParidad(H_rows, c_estimado)) {
            return make_tuple(vector<unsigned char>(c_estimado.begin(), c_estimado.begin() + n), true);
        }
    }
    return make_tuple(y, false);
}

int corregir_archivo(const std::string_view inputFileName,
                    const std::string_view outputFileName,
                    MatrizDispersa H_rows,
                    MatrizDispersa H_cols, 
                    int max_iter) {
    
    int n = H_cols.size(); 

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
    std::vector<unsigned char> bloque_deco(n);

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
        if (++total % 10 == 0) {
            std::cout << "Palabras procesadas: " << total << std::endl;
            std::cout << "Cantidad de errores: " << errores << std::endl;
            std::cout << "Cantidad de correctas: " << corregidos << std::endl;
            // std::cout << "Tasa de error: " << (float)errores/(float)total << std::endl << std::endl;
        }
        /*-------------------------------------------------------------------------*/
    
        // Escribir la palabra decodificada en archivo de salida
        bloque_deco = get<0>(decod);
        outputFile.write(reinterpret_cast<const char*>(bloque_deco.data()),n);


    }
    std::cout << "Decodificación finalizada" << std::endl;
    std::cout << "Palabras procesadas: " << total << std::endl;
    std::cout << "Cantidad de errores: " << errores << std::endl;
    std::cout << "Cantidad de correcciones: " << corregidos << std::endl;
    // std::cout << "Tasa de corrección: " << (float)corregidos/(float)total << std::endl;

    outputFile.close();
    inputFile.close();

    return (1);
}



