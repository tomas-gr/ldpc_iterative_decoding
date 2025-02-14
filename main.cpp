#include <chrono>
#include <unistd.h>
#include <iostream>
#include "decode.hpp"
#include "matrix.hpp"
using namespace std;


int main(int argc, char* argv[]) {

    // int n = -1;
    // int r = -1;
    // string file_in;
    // string file_out;
    // ifstream fin;

    // int opt;
    // while ((opt = getopt(argc, argv, "n:r:i:o:")) != -1) {
    //     switch (opt) {
    //     case 'n':
    //         n = stoi(optarg);
    //         if (n < 0 || n > 255){
    //             cerr << "Error: n debe ser un entero entre 0 y 255" << endl;
    //             return 1;
    //         }
    //         break;
    //     case 'r':
    //         r = stoi(optarg);
    //         if (r < 0 || r > 255){
    //             cerr << "Error: r debe ser un entero entre 0 y n" << endl;
    //             return 1;
    //         }
    //         break;
    //     case 'i':
    //         file_in = optarg;
    //         fin.open(file_in);
    //         if (!fin) {
    //             cerr << "Error: El archivo de entrada no existe.\n";
    //             return 1;
    //         }
    //         fin.close();
    //         break;
    //     case 'o':
    //         file_out = optarg;
    //         break;
    //     default:
    //         cerr << "Uso correcto: rsdecode -n <n> -r <r> -i <file_in> -o <file_out>\n";
    //         return 1;
    //     }
    // }

    // if (optind < argc) {
    //     cerr << "Uso correcto: rsdecode -n <n> -r <r> -i <file_in> -o <file_out>\n";
    //     return 1;
    // }

    // if (n == -1 || r == -1 || file_in.empty() || file_out.empty()) {
    //     cerr << "Error: Faltan argumentos.\n";
    //     cerr << "Uso correcto: rsdecode -n <n> -r <r> -i <file_in> -o <file_out>\n";
    //     return 1;
    // }



    // std::cout << std::endl << "Comenzando decodificacion" << std::endl << std::endl;

    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // corregir_archivo(file_in,file_out,n,r);
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms] (" << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " [s])" << std::endl;

    // Probar un ejemplo de producto de matrices
    std::vector<std::vector<unsigned char>> H;
    std::vector<std::vector<unsigned char>> y2;
    std::vector<unsigned char> x;
    std::vector<unsigned char> y;

    inicializarMatriz(H, 2, 6);
    inicializarVector(x, 6);
    inicializarVector(y, 2);
    inicializarMatriz(y2, 2, 6);

    H[0] = {1, 1, 0, 1, 0, 0};
    H[1] = {0, 1, 1, 0, 1, 0};

    x = {1, 0, 1, 1, 0, 1};

    productoMatriz(H, x, y);
    ANDMatriz(H, x, y2);

    cout << "Resultado del producto de matrices: ";
    for (unsigned char bit : y) cout << (int)bit << " ";
    cout << endl;


    cout << "Resultado del AND de matrices: " << endl;
    for (size_t i = 0; i < y2.size(); ++i) {
        for (size_t j = 0; j < y2[0].size(); ++j) {
            cout << (int)y2[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}