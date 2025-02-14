ldpc_decode: main.o decode.o matrix.o
	g++ main.o decode.o matrix.o -o ldpc_decode

main.o: main.cpp
	g++ -c main.cpp

decode.o: decode.cpp matrix.hpp
	g++ -c decode.cpp

matrix.o: matrix.cpp matrix.hpp
	g++ -c matrix.cpp

clean:
	rm -f *.o ldpc_decode
