all: op

unop: test.cpp
	g++ -std=c++11 test.cpp nnet.cpp nnet.h
op: test.cpp
	g++ -O3 -std=c++11 test.cpp nnet.cpp nnet.h
clean:
	rm *o testNet
