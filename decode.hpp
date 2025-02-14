#include <vector>
#include <map>

using namespace std;


/**
 * @brief Modifica los valores de R y c de acuerdo al mensaje enviado por los nodos de check 
 * 
 * @param H Matriz de chequeo de paridad
 * @param R Matriz que almacena los mensajes entre nodos de variable y de check
 * @param c Estimacion de la palabra de codigo
 * @param s Vector que contiene el calculo del sindrome
 * 
 */
void VCmessage(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &R, vector<unsigned char> &c, vector<unsigned char> &sindrome);

/**
 * @brief Calcula las posiciones de la matriz de chequeo de paridad que contienen un 1
 * 
 * @param H Matriz de chequeo de paridad
 * @param Hpos diccionario que almacena las posiciones de los 1s en la matriz de chequeo de paridad
 * 
 */
void VNConnections(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &VNCon);


void CNConnections(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &CNCon);

vector<int> ldpc_decode_unanimity(const vector<vector<int>> &H, vector<int> y, int max_iter = 10);
