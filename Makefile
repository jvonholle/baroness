all: trainop
nettest: nntestop

#Tests
nntestunop: tests/nnetTime.cpp
	g++ -std=c++14 tests/nnetTime.cpp src/nnet.cpp src/nnet.h -o baroness
nntestop: tests/nnetTime.cpp
	g++ -O3 -Ofast -std=c++14 tests/nnetTime.cpp src/nnet.cpp src/nnet.h -o baroness
testmove: tests/moveTest.cpp
	g++ -std=c++14 tests/moveTest.cpp src/movement.cpp src/movecheck.h src/movement.h -o baroness
catch: tests/valueCheck.cpp
	g++ -std=c++14 tests/catch.hpp tests/valueCheck.cpp src/nnet.h src/nnet.cpp -o baroness
testmini: tests/minimax_test.cpp
	g++ -std=c++14 tests/minimax_test.cpp src/minimax.cpp src/minimax.h src/nnet.h src/nnet.cpp src/movement.h src/movement.cpp -o baroness
#Play checkers
train: src/train.cpp
	g++ -std=c++14 src/movement.cpp src/movement.h src/nnet.cpp src/nnet.h src/player.cpp src/player.h src/tourney.cpp src/tourney.h src/train.cpp -o baroness
trainop: src/train.cpp
	g++ -O3 -Ofast -std=c++14 src/movement.cpp src/movement.h src/nnet.cpp src/nnet.h src/player.cpp src/player.h src/tourney.cpp src/tourney.h src/train.cpp src/minimax.cpp src/minimax.h -o baroness

.PHONY: clean
clean:
	rm baroness */*.gch out*
