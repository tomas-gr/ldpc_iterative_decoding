#include <vector>
#include <map>

#include "matrix.hpp"

using namespace std;


/**
 * @brief Modifica los valores de R y c de acuerdo al mensaje enviado por los nodos de check.
 * 
 * @param H Matriz de chequeo de paridad.
 * @param R Matriz que almacena los mensajes entre nodos de variable y de check.
 * @param c Estimacion de la palabra de codigo.
 * @param s Vector que contiene el calculo del sindrome.
 * 
 */
void VCmessage(const vector<vector<unsigned char>> &VNCon, const vector<vector<unsigned char>> &CNCon, vector<vector<unsigned char>> &R, vector<unsigned char> &c, vector<unsigned char> &sindrome);

/**
 * @brief Calcula las posiciones de la matriz de chequeo de paridad que contienen un 1, según sus columnas.
 * 
 * @param H Matriz de chequeo de paridad de tamaño N*M con k 1s por fila/columna.
 * @param VNCon Matriz de tamaño M*k que almacena las posiciones de los 1s de las columnas de la matriz de chequeo de paridad.
 * 
 */
void VNConnections(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &VNCon);

/**
 * @brief Calcula las posiciones de la matriz de chequeo de paridad que contienen un 1, según sus filas.
 * 
 * @param H Matriz de chequeo de paridad de tamaño N*M con k 1s por fila/columna.
 * @param CNCon Matriz de tamaño N*k que almacena las posiciones de los 1s de las filas de la matriz de chequeo de paridad.
 * 
 */
void CNConnections(const vector<vector<unsigned char>> &H, vector<vector<unsigned char>> &CNCon);

vector<int> ldpc_decode_unanimity(const vector<vector<int>> &H, vector<int> y, int max_iter = 10);
