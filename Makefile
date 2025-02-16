ldpc_decode: main.o decode.o matrix.o
	g++ main.o decode.o matrix.o -o ldpc_decode

main.o: main.cpp
	g++ -c main.cpp

decode.o: src/decode.cpp src/matrix.hpp
	g++ -c src/decode.cpp

matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -c src/matrix.cpp

clean:
	rm -f *.o ldpc_decode
