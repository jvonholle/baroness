all: main
nettest: nntestop

#Tests
nntestunop: tests/nnetTime.cpp
	g++ -std=c++11 tests/nnetTime.cpp src/nnet.cpp src/nnet.h -o baroness
nntestop: tests/nnetTime.cpp
	g++ -O3 -Ofast -std=c++11 tests/nnetTime.cpp src/nnet.cpp src/nnet.h -o baroness
testmove: tests/moveTest.cpp
	g++ -std=c++11 tests/moveTest.cpp src/movement.cpp src/movecheck.h src/movement.h -o baroness
catch: tests/valueCheck.cpp
	g++ -std=c++11 tests/catch.hpp tests/valueCheck.cpp src/nnet.h src/nnet.cpp -o baroness
#Play checkers
main: src/play.cpp
	g++ -std=c++11 src/nnet.cpp src/nnet.h src/movement.cpp src/movecheck.h src/movement.h src/play.cpp -o baroness
train: src/train.cpp
	g++ -std=c++11 src/nnet.cpp src/nnet.h src/movement.cpp src/movecheck.h src/movement.h src/train.cpp -o baroness

clean:
	rm baroness */*.gch output
