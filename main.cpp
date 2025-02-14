#include <chrono>
#include <unistd.h>
#include "decode.hpp"
#include "gf256.h"
using namespace std;


int main(int argc, char* argv[]) {

    int n = -1;
    int r = -1;
    string file_in;
    string file_out;
    ifstream fin;

    int opt;
    while ((opt = getopt(argc, argv, "n:r:i:o:")) != -1) {
        switch (opt) {
        case 'n':
            n = stoi(optarg);
            if (n < 0 || n > 255){
                cerr << "Error: n debe ser un entero entre 0 y 255" << endl;
                return 1;
            }
            break;
        case 'r':
            r = stoi(optarg);
            if (r < 0 || r > 255){
                cerr << "Error: r debe ser un entero entre 0 y n" << endl;
                return 1;
            }
            break;
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
        default:
            cerr << "Uso correcto: rsdecode -n <n> -r <r> -i <file_in> -o <file_out>\n";
            return 1;
        }
    }

    if (optind < argc) {
        cerr << "Uso correcto: rsdecode -n <n> -r <r> -i <file_in> -o <file_out>\n";
        return 1;
    }

    if (n == -1 || r == -1 || file_in.empty() || file_out.empty()) {
        cerr << "Error: Faltan argumentos.\n";
        cerr << "Uso correcto: rsdecode -n <n> -r <r> -i <file_in> -o <file_out>\n";
        return 1;
    }



    std::cout << std::endl << "Comenzando decodificacion" << std::endl << std::endl;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    corregir_archivo(file_in,file_out,n,r);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms] (" << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " [s])" << std::endl;


    return 0;
}