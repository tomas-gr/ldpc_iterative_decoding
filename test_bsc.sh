# Generating file
bbchannel -s 314 -p 0.05 -Z 32000000 testdata.dat

# Decoding file
./ldpc_decode -i testdata.dat -o testdata_corr.dat -n 10

# Checking results
ldpc_Utils/diffblock -m 8 -z -n 1600 testdata_corr.dat 