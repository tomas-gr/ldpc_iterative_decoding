#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include <tuple>
#include <chrono>
#include <thread>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "decode.hpp"
#include "matrix.hpp"

using namespace std;
using namespace std::chrono;



bool chequeoParidad(const MatrizDispersa &H_rows, const vector<unsigned char> c_estimado){
    // Para cada nodo de check
    for (const auto& c : H_rows) {
        int paridad = 0;
        // Para cada nodo de variable conectado a c
        for (int v : c) {
            paridad ^= c_estimado[v];
        }
        if (paridad != 0) return false;
    }
    return true;
}


#include <future>

tuple<vector<unsigned char>, bool, int> ldpc_decode_unanimity(const MatrizDispersa &H_rows,
                                                         const MatrizDispersa &H_cols,
                                                         const vector<unsigned char> &y,
                                                         int max_iter) {
    
    int r = H_rows.size();  // Cantidad de nodos de check
    int n = H_cols.size();  // Cantidad de nodos de variable

    /* Chequeo de paridad inicial */        
    if (chequeoParidad(H_rows, y)) {
        return make_tuple(y, true, -1);
    }

    vector<unsigned char> c_estimado = y;
    vector<vector<unsigned char>> mensaje_vc(r, vector<unsigned char>(n, 0));

    vector<unordered_map<int, unsigned char>> mensaje_cv(n);

    /* Paso 0: Mensaje inicial de variable a check */
    // Para cada nodo de variable
    for (int j = 0; j < n; j++) {
        // Para cada nodo de check conectado a j
        for (int i : H_cols[j]) {
            // Se envía el valor de y[j] a los nodos de check i conectados a j
            mensaje_vc[i][j] = c_estimado[j];
        }
    }

    for (int iter = 0; iter < max_iter; ++iter) {
        /* Paso 1: Mensajes de check a variable */    

        // Para cada nodo de variable  
        for (int j = 0; j < n; j++) {
            // Para cada nodo de check conectado a j
            for (int i : H_cols[j]) {
                // Recorro mensajes recibidos por check i
                unsigned char mensaje = 0;
                for (int k : H_rows[i]) {
                    // Suma modulo dos (xor) de los mensajes recibidos por i, excepto el mensaje enviado por j
                    if (k != j) {
                        mensaje ^= mensaje_vc[i][k];
                    }
                }
                // Cada nodo de check envía el mensaje a j
                mensaje_cv[j][i] = mensaje;
            }
        }

        // Para cada nodo de check
        for (int i = 0; i < r; i++) {
            // Para cada nodo de variable conectado a i
            for (int j : H_rows[i]) {
                // Si todos los mensajes recibidos por j son iguales, excepto por el mensaje enviado por i
                if (count_if(mensaje_cv[j].begin(), mensaje_cv[j].end(), [i](const auto &m) { return m.first != i && m.second == 1; }) == mensaje_cv[j].size() - 1) {
                    // Se envía un mensaje de 1 a i
                    mensaje_vc[i][j] = 1;
                    c_estimado[j] = 1;
                } else if (count_if(mensaje_cv[j].begin(), mensaje_cv[j].end(), [i](const auto &m) { return m.first != i && m.second == 0; }) == mensaje_cv[j].size() - 1) {
                    // Se envía un mensaje de 0 a i
                    mensaje_vc[i][j] = 0;
                    c_estimado[j] = 0;
                }
            }
        }

        /* Paso 3: Parity Check */
        if (chequeoParidad(H_rows, c_estimado)) {
            return make_tuple(vector<unsigned char>(c_estimado.begin(), c_estimado.begin() + n), true, iter);
        }
    }
    return make_tuple(y, false, max_iter);
}

int corregir_archivo(const std::string_view inputFileName,
                    const std::string_view outputFileName,
                    MatrizDispersa H_rows,
                    MatrizDispersa H_cols, 
                    int max_iter,
                    bool use_multiple_cpus) {
    
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
    int sin_error = 0;
    int iters_totales = 0;
    int iters_decodificacion = 0;

    std::vector<std::future<tuple<vector<unsigned char>, bool, int>>> futures;

    while(inputFile.read(buffer.data(),n)){
        std::streamsize bytes_read = inputFile.gcount();
        for (int i = 0; i < bytes_read; ++i){
            bloque[i] = static_cast<unsigned char>(buffer[i]);
        }

        if (use_multiple_cpus) {
            futures.push_back(std::async(std::launch::async, ldpc_decode_unanimity, H_rows, H_cols, bloque, max_iter));
        } else {
            futures.push_back(std::async(std::launch::deferred, ldpc_decode_unanimity, H_rows, H_cols, bloque, max_iter));
        }
        total++;
    }

    for (int i = 0; i < total; ++i) {
        auto decod = futures[i].get();
        if (get<1>(decod)){
            if (get<2>(decod) == -1){
                sin_error++;
            } else {
                corregidos++;
            }
        }
        else{
            errores++;
        }

        int tmp = get<2>(decod);
        iters_totales += tmp;
        if (tmp != max_iter && tmp != -1){
            iters_decodificacion += tmp;
        }

        // Escribir la palabra decodificada en archivo de salida
        bloque_deco = get<0>(decod);
        outputFile.write(reinterpret_cast<const char*>(bloque_deco.data()),n);
    }

    std::cout << "Decodificación finalizada" << std::endl;
    std::cout << "Palabras procesadas: " << total << std::endl;
    std::cout << "Palabras que no se pudieron corregir: " << errores << std::endl;
    std::cout << "Palabras corregidas: " << corregidos << std::endl;
    std::cout << "Palabras sin error: " << sin_error << std::endl;
    std::cout << "Tasa de error: " << (float)errores/(float)total << std::endl;
    std::cout << "Iters promedio: " << (float)iters_totales/(float)total << std::endl;
    std::cout << "Iters promedio de decodificación: " << (float)iters_decodificacion/(float)corregidos << std::endl;

    outputFile.close();
    inputFile.close();

    return (1);
}



