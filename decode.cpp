#include <iostream>
#include <vector>
#include <map>
#include "decode.hpp"

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

vector<int> ldpc_decode_unanimity(const vector<vector<int>> &H, vector<int> y, int max_iter){
    return vector<int>();

}

