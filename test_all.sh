#!/bin/bash

# Nombre del archivo de resultados
logfile="result.log"

# Limpiar archivo de log previo (si existe)
> "$logfile"

echo "Script started" >> result.log
echo "Starting script execution" >> "$logfile" 2>&1

# echo -e "Corriendo test_bsc para 50 iteraciones maximo\n\n" >> "$logfile" 2>&1
# echo -e "Probabilidad de error 0.05 y 50 max_iter \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.05 32000000 50
# echo -e "Probabilidad de error 0.06 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.06 32000000 50
# echo -e "Probabilidad de error 0.07 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.07 32000000 50
# echo -e "Probabilidad de error 0.08 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.08 32000000 50
# echo -e "Probabilidad de error 0.09 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.09 32000000 50
# echo -e "Probabilidad de error 0.10 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.10 32000000 50
# echo -e "Probabilidad de error 0.11 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.11 32000000 50
# echo -e "Probabilidad de error 0.12 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.12 32000000 50

# echo -e "Corriendo test_bsc para 20 iteraciones maximo\n\n" >> "$logfile" 2>&1
# echo -e "Probabilidad de error 0.05 y 20 max_iter \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.05 32000000 20
# echo -e "Probabilidad de error 0.06 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.06 32000000 20
# echo -e "Probabilidad de error 0.07 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.07 32000000 20
# echo -e "Probabilidad de error 0.08 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.08 32000000 20
# echo -e "Probabilidad de error 0.09 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.09 32000000 20
# echo -e "Probabilidad de error 0.10 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.10 32000000 20
# echo -e "Probabilidad de error 0.11 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.11 32000000 20
# echo -e "Probabilidad de error 0.12 \n" >> "$logfile" 2>&1
# ./test_bsc.sh 0.12 32000000 20

echo -e "Corriendo test_bsc para 10 iteraciones maximo\n\n" >> "$logfile" 2>&1
echo -e "Probabilidad de error 0.05 y 10 max_iter \n" >> "$logfile" 2>&1
./test_bsc.sh 0.05 32000000 10
echo -e "Probabilidad de error 0.06 \n" >> "$logfile" 2>&1
./test_bsc.sh 0.06 32000000 10
echo -e "Probabilidad de error 0.07 \n" >> "$logfile" 2>&1
./test_bsc.sh 0.07 32000000 10
echo -e "Probabilidad de error 0.08 \n" >> "$logfile" 2>&1
./test_bsc.sh 0.08 32000000 10
echo -e "Probabilidad de error 0.09 \n" >> "$logfile" 2>&1
./test_bsc.sh 0.09 32000000 10
echo -e "Probabilidad de error 0.10 \n" >> "$logfile" 2>&1
./test_bsc.sh 0.10 32000000 10
echo -e "Probabilidad de error 0.11 \n" >> "$logfile" 2>&1
./test_bsc.sh 0.11 32000000 10
echo -e "Probabilidad de error 0.12 \n" >> "$logfile" 2>&1
./test_bsc.sh 0.12 32000000 10