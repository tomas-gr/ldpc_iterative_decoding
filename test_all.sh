#!/bin/bash

# Define parameters
PROBABILITIES=(0.05 0.06 0.07 0.08 0.09 0.1 0.11 0.12)
MAX_ITERS=(10 20 30 50)
FILE_LENGTH=32000000
SEED=42 
OUTPUT_CSV="test_results.csv"

# Initialize CSV file
echo "Probability,Max Iterations,Block Error Rate,Decoding time, Average Iters, Average Iters decod" > $OUTPUT_CSV

# Create temporary directory for test files
mkdir -p test_files

for P in "${PROBABILITIES[@]}"; do
    INPUT_FILE="test_files/input_p${P}.dat"

    # Generate input file
    ldpc_Utils/bbchannel -s $SEED -p $P -Z $FILE_LENGTH $INPUT_FILE

    for ITER in "${MAX_ITERS[@]}"; do
        OUTPUT_FILE="test_files/output_p${P}_iter${ITER}.dat"

        # Run decoder and extract both values
        OUTPUT=$(./ldpc_decode -i $INPUT_FILE -o $OUTPUT_FILE -n $ITER)
        TIME=$(echo "$OUTPUT" | grep "Tiempo" | awk '{print $3}')
        AVG_ITERS=$(echo "$OUTPUT" | grep "Iters promedio:" | awk '{print $3}')
        AVG_ITERS_DECOD=$(echo "$OUTPUT" | grep "decodificación:" | awk '{print $5}')
                
        # Run diffblock and extract block error rate
        ERROR_RATE=$(ldpc_Utils/diffblock -z -n 1600 -m 8 $OUTPUT_FILE | grep "Error rates" | awk '{print $8}')

        # Store results in CSV
        echo "$P,$ITER,$ERROR_RATE,$TIME,$AVG_ITERS,$AVG_ITERS_DECOD" >> $OUTPUT_CSV

        echo "Tested P=$P, Iter=$ITER -> Block Error Rate: $ERROR_RATE"
    done
done

echo "Testing complete. Results saved in $OUTPUT_CSV."
