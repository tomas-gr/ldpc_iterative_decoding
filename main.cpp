#include <chrono>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "src/decode.hpp"
#include "src/matrix.hpp"
#include "src/H6.c"
using namespace std;

int main(int argc, char* argv[]) {

    int j = 3;
    int k = 4;
    int m = 400;
    int n = 1600;
    int r = 1200;
    int max_iter = 1;
    bool use_multiple_cpus = false;

    string file_in;
    string file_out;
    ifstream fin;

    vector<vector<unsigned char>> parityCheck = leerMatriz(H);
    MatrizDispersa H_rows, H_cols;
    convertirADispersa(parityCheck,H_rows,H_cols);

    int opt;
    while ((opt = getopt(argc, argv, "i:o:n:c")) != -1) {
        switch (opt) {
        case 'i':
            file_in = optarg;
            fin.open(file_in);
            if (!fin) {
                cerr << "Error: El archivo de entrada no existe.\n";
                return 1;
            }
            fin.close();
            break;
        case 'o':
            file_out = optarg;
            break;
        case 'n':
            max_iter = stoi(optarg);
            if (max_iter <= 0 || max_iter > 500) {
                cerr << "Error: max_iter debe ser un entero positivo menor a 500.\n";
                return 1;
            }
            break;
        case 'c':
            use_multiple_cpus = true;
            break;
        default:
            cerr << "Uso correcto: ldpc_decode -i <file_in> -o <file_out> -n <max_iter> [-c]\n";
            return 1;
        }
    }

    if (optind < argc) {
        cerr << "Uso correcto: ldpc_decode -i <file_in> -o <file_out> -n <max_iter> [-c]\n";
        return 1;
    }

    if (file_in.empty() || file_out.empty()) {
        cerr << "Error: Faltan argumentos.\n";
        cerr << "Uso correcto: ldpc_decode -i <file_in> -o <file_out> -n <max_iter> [-c]\n";
        return 1;
    }

    std::cout << std::endl << "Comenzando decodificacion" << std::endl << std::endl;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    corregir_archivo(file_in,file_out,H_rows,H_cols,max_iter,use_multiple_cpus);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Tiempo = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " [s] " << std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() << " [m]" << std::endl;

    return 0;
}