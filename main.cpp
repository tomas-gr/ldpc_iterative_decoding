#include <chrono>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "decode.hpp"
#include "matrix.hpp"
#include "H6.h"
using namespace std;


int main(int argc, char* argv[]) {

    int j = 3;
    int k = 4;
    int m = 400;
    int n = 1600;
    int r = 1200;
    int max_iter;

    string file_in;
    string file_out;
    ifstream fin;

    unsigned char H[_NROWS][_NCOLS];

    vector<vector<unsigned char>> parityCheck = leerMatriz(H);

    int opt;
    while ((opt = getopt(argc, argv, "i:o:n")) != -1) {
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
            max_iter = atoi(optarg);
            break;
        default:
            cerr << "Uso correcto: ldpc_decode -i <file_in> -o <file_out> -n <max_iter>\n";
            return 1;
        }
    }

    if (optind < argc) {
        cerr << "Uso correcto: ldpc_decode -i <file_in> -o <file_out> -n <max_iter>\n";
        return 1;
    }

    if (file_in.empty() || file_out.empty()) {
        cerr << "Error: Faltan argumentos.\n";
        cerr << "Uso correcto: ldpc_decode -i <file_in> -o <file_out> -n <max_iter>\n";
        return 1;
    }



    std::cout << std::endl << "Comenzando decodificacion" << std::endl << std::endl;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    corregir_archivo(file_in,file_out,parityCheck, max_iter);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Tiempo de correción del archivo = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms] (" << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " [s])" << std::endl;


///////////////////////////////// PRUEBAS //////////////////////////////////////////////////////

    // std::vector<std::vector<unsigned char>> H_test;
    // std::vector<std::vector<unsigned char>> VNCon;
    // std::vector<std::vector<unsigned char>> CNCon;

    // std::vector<std::vector<unsigned char>> R_test;
    // std::vector<unsigned char> message;
    // std::vector<unsigned char> decod;
    // std::vector<unsigned char> syn;

    // initializeMatrix(VNCon,6,2);
    // initializeMatrix(CNCon,6,2);
    // initializeMatrix(H_test,6,6);

    // H_test[0] = {1,1,0,0,0,0};
    // H_test[1] = {0,0,1,1,0,0};
    // H_test[2] = {0,0,0,0,1,1};
    // H_test[3] = {1,0,0,0,1,0};
    // H_test[4] = {0,1,0,0,0,1};
    // H_test[5] = {0,0,1,1,0,0};
    
    // VNConnections(H_test,VNCon);
    // CNConnections(H_test,CNCon);

    // std::cout << "VN" <<std::endl;
    // printMatrix(VNCon);
    // std::cout << std::endl;
    // std::cout << "CN" <<std::endl;
    // printMatrix(CNCon);
    // std::cout << std::endl;

    // initializeMatrix(R_test, 6,6);
    // initializeVector(message, 6);
    // initializeVector(decod, 6);
    // initializeVector(syn, 6);

    // message[1] = 1;
    // message[2] = 1;
    // message[3] = 1;

    // decod = message;

    // std::cout << "MSG" <<std::endl;
    // printVector(message);
    // std::cout << std::endl;

    // /* Le puse unos const a la definición en matrix.cpp y se rompió esto :( */
    // ANDMatrix(H_test, message, R_test);
    // productMatrix(H_test, decod, syn);

    // std::cout << "R" <<std::endl;
    // printMatrix(R_test);
    // std::cout << std::endl;

    // std::cout << "SYN" <<std::endl;
    // printVector(syn);
    // std::cout << std::endl;

    // VCmessage(VNCon, CNCon, R_test, decod, syn);

    // std::cout << "R_response" <<std::endl;
    // printMatrix(R_test);
    // std::cout << std::endl;

    return 0;
}