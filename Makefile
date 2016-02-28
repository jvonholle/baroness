all: main
nettest: nntestop

#Tests
nntestunop: tests/nnetTime.cpp
	g++ -std=c++11 tests/nnetTime.cpp src/nnet.cpp src/nnet.h
nntestop: tests/nnetTime.cpp
	g++ -O3 -Ofast -std=c++11 tests/nnetTime.cpp src/nnet.cpp src/nnet.h
testmove: moveTest.cpp
	g++ -std=c++11 tests/moveTest.cpp src/movement.cpp src/movecheck.h src/movement.h
catch: valueCheck.cpp
	g++ -std=c++11 tests/catch.hpp tests/valueCheck.cpp src/nnet.h nnet.cpp
#Play checkers
main:
	g++ -std=c++11 src/nnet.cpp src/nnet.h src/movement.cpp src/movecheck.h src/movement.h src/play.cpp -o baroness
train:
	g++ -std=c++11 src/nnet.cpp src/nnet.h src/movement.cpp src/movecheck.h src/movement.h src/train.cpp -o baroness

clean:
	rm a.out */*.gch output
