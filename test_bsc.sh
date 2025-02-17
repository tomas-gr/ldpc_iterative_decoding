#!/bin/bash

# Verificar si se pasaron los parámetros p (probabilidad de error) y l (largo del archivo)
if [ "$#" -ne 3 ]; then
  echo "Uso: $0 <probabilidad de error> <largo del archivo> <numero de iteraciones>"
  exit 1
fi

# Asignar los parámetros a variables
p=$1
l=$2
n=$3

# Nombre del archivo de resultados
logfile="result.log"

# Generar archivo
ldpc_Utils/bbchannel -s 314 -p "$p" -Z "$l" testdata.dat >> /dev/null 2>&1

# Decodificación
./ldpc_decode -i testdata.dat -o testdata_corr.dat -n "$n" >> /dev/null 2>&1

# Diferencia
ldpc_Utils/diffblock -m 8 -z -n 1600 testdata_corr.dat >> "$logfile" 2>&1

echo "Proceso completado. Resultados guardados en $logfile."
