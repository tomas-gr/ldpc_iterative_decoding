#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include "decode.hpp"
#include "matrix.hpp"

using namespace std;


void VCmessage(const vector<vector<unsigned char>> &VNCon, const vector<vector<unsigned char>> &CNCon, vector<vector<unsigned char>> &R, vector<unsigned char> &c, vector<unsigned char> &sindrome){
    int N = CNCon.size();
    int M = VNCon.size();
    int k = VNCon[0].size();
    int one_counter, first_one, first_zero;
    bool found_one, found_zero;
   
    /* Respuesta de los CN */

    /* Recorremos s y trabajamos con las filas con valor 1*/
    for (int i=0; i<sindrome.size(); i++){
         if (sindrome[i] == 1){ 

             /* Invertimos los valores de la fila de R*/
             /* (solamente cambiamos los valores de las posiciones en donde hay 1s en H) */
             for (int j=0; j<k; j++)
                 R[i][CNCon[i][j]] ^= 0x01;

         }
    }
    
    /* debug */
    std::cout << "R_syndrome" <<std::endl;
    printMatrix(R);
    std::cout << std::endl;

    /* Respuesta de los VN */

    /* Procesamos cada VN por separado */
    for (int j=0; j<M; j++){
        one_counter = 0;
        found_one = false;
        found_zero = false;

        /* debug */
        first_zero = N;
        first_one = N;

        /* Contamos la cantidad de 1s que recibió cada VN */
        for (int i=0; i<k; i++){
            if ((!found_zero) && (R[VNCon[j][i]][j]==0)){
                first_zero = i;
                found_zero = true;
            }
            else if ((!found_one) && (R[VNCon[j][i]][j]==1)){
                first_one = i;
                found_one = true;
            }
            
            one_counter += R[VNCon[j][i]][j];
        };

        /* debug */
        std::cout << "j = " << j << "   one_counter=" << one_counter << "   first_one=" << first_one << "   first_zero=" << first_zero <<std::endl <<std::endl;

        /* Accionamos según la cantidad de 1s contados */
        
        /* Si hay unanimidad cambiamos la palabra 'decodificada' */
        if (one_counter==0)
            c[j] = 0;
        else if (one_counter==k)
            c[j] = 1;

// Despues vi que estaba hecho más abajo esto.
        else if (one_counter==1){
            c[j] = (first_one == j) ? 0 : 1;
            }
        else if (one_counter==k-1){
            c[j] = (first_zero == j) ? 1 : 0; 
        }
///////////////////////////////////////////////

        /* Mandamos la palabra decodificada */                
        for (int i=0; i<k; i++)
            R[VNCon[j][i]][j] = c[j];
        
        /* Ajustamos cuando no hay unanimidad */
        if (one_counter==1)
            R[VNCon[j][first_one]][j] = 0;
            
        if (one_counter==k-1)
            R[VNCon[j][first_zero]][j] = 1;
    }

    /* debug */
    std::cout << "DECOD" <<std::endl;
    printVector(c);
    std::cout << std::endl;
}

void VNConnections(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &VNCon){
    int N = H.size();
    int M = H[0].size();
    int k = 0;

    for (int i=0; i<M; i++){
        k = 0;
        for (int j=0; j<N; j++){
            if (H[j][i] == 1){
                VNCon[i][k++] = j;
            }
        }
    }
}

void CNConnections(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &CNCon){
    int N = H.size();
    int M = H[0].size();
    int k = 0;

    for (int i=0; i<N; i++){
        k = 0;
        for (int j=0; j<M; j++){
            if (H[i][j] == 1){
                CNCon[i][k++] = j;
            }
        }
    }
}

tuple<vector<unsigned char>,bool> ldpc_decode_unanimity(const vector<vector<unsigned char>> &H, vector<unsigned char> y, int max_iter){
    std::vector<unsigned char> sindrome;

    initializeVector(sindrome, y.size());

    /* Calculamos el síndrome y vemos si es nulo */
    productMatrix(H, y, sindrome);

    if (VectorIsNull(sindrome)){
        return make_tuple(y,true);
    }
    else{
        int N, M, current_iter=0;

        N = H.size();
        M = H[0].size();
        
        vector<unsigned char> c(y);

        std::vector<std::vector<unsigned char>> VNCon;
        std::vector<std::vector<unsigned char>> CNCon;
        std::vector<std::vector<unsigned char>> R;
        initializeMatrix(R, N, M);

        /* Vemos dónde están los 1s de H */
        VNConnections(H, VNCon);
        CNConnections(H, CNCon);

        /* Calculamos el primer mensaje de los VN a CN */
        ANDMatrix(H, y, R);

        while ((!VectorIsNull(sindrome)) && (current_iter<max_iter)){
            /* Calculamos el mensaje de C->V y la respuesta de los VN */
            VCmessage(VNCon, CNCon, R, c, sindrome);

            /* Calculamos nuevamente el síndrome */
            syndromeMatrix(H, R, sindrome);

            current_iter++;
        };


        return make_tuple(c,VectorIsNull(sindrome));
    };
}

int corregir_archivo(const std::string_view inputFileName, const std::string_view outputFileName,vector<vector<unsigned char>> ParityCheck, int max_iter){
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

        tuple<vector<unsigned char>,bool> decod = ldpc_decode_unanimity(ParityCheck, bloque, max_iter);
        
        if (get<1>(decod)){
            corregidos++;
        }
        else{
            errores++;
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
