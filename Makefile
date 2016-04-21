all: trainop
nettest: nntestop

#Tests
nntestunop: tests/nnetTime.cpp
	g++ -std=c++11 tests/nnetTime.cpp src/nnet.cpp src/nnet.h -o baroness_test
nntestop: tests/nnetTime.cpp
	g++ -O3 -Ofast -std=c++11 tests/nnetTime.cpp src/nnet.cpp src/nnet.h src/minimax.h src/minimax.cpp src/movement.cpp src/movement.h -o baroness_test
testmove: tests/moveTest.cpp
	g++ -std=c++11 tests/moveTest.cpp src/movement.cpp src/movecheck.h src/movement.h -o baroness_test
catch: tests/valueCheck.cpp
	g++ -std=c++11 tests/catch.hpp tests/valueCheck.cpp src/nnet.h src/nnet.cpp -o baroness_test
catch_ab: tests/ab_vs_mm_test.cpp
	g++ -std=c++11 tests/catch.hpp tests/ab_vs_mm_test.cpp src/nnet.h src/nnet.cpp src/minimax.cpp src/minimax.h src/movement.cpp src/movement.h -o baroness_test
noc_ab: tests/ab_vs_mm_test_no_catch.cpp
	g++ -O3 -Ofast -std=c++11 tests/ab_vs_mm_test_no_catch.cpp src/nnet.h src/nnet.cpp src/minimax.cpp src/minimax.h src/movement.cpp src/movement.h -o baroness_test
testmini: tests/minimax_test.cpp
	g++ -std=c++11 tests/minimax_test.cpp src/minimax.cpp src/minimax.h src/nnet.h src/nnet.cpp src/movement.h src/movement.cpp -o baroness_test
kaiju: tests/kaiju_test.cpp
	g++ -O3 -Ofast -std=c++11 src/kaiju.cpp src/kaiju.h tests/kaiju_test.cpp src/nnet.h src/nnet.cpp src/minimax.cpp src/minimax.h src/movement.cpp src/movement.h -o baroness_test


#Play checkers

trainop: src/train.cpp
	g++ -pthread -O3 -Ofast -std=c++11 src/movement.cpp src/movement.h src/nnet.cpp src/nnet.h src/player.cpp src/player.h src/tourney.cpp src/tourney.h src/train.cpp src/minimax.cpp src/minimax.h src/kaiju.cpp src/kaiju.h -o baroness_train
pick: src/pick_best.cpp
	g++ -pthread -O3 -Ofast -std=c++11 src/movement.cpp src/movement.h src/nnet.cpp src/nnet.h src/player.cpp src/player.h src/tourney.cpp src/tourney.h src/pick_best.cpp src/minimax.cpp src/minimax.h src/kaiju.cpp src/kaiju.h -o baroness_pick
best: src/best_of_best.cpp
	g++ -pthread -O3 -Ofast -std=c++11 src/movement.cpp src/movement.h src/nnet.cpp src/nnet.h src/player.cpp src/player.h src/tourney.cpp src/tourney.h src/best_of_best.cpp src/minimax.cpp src/minimax.h src/kaiju.cpp src/kaiju.h -o baroness_best

.PHONY: clean
clean:
	rm baroness_* */*.gch out*
