#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/nnet.h"


TEST_CASE("Testing Small Nets"){
    SECTION("Testing 2,3,1"){
            neuralNet test ({2,3,1},{1,1,1,1,1,1,1,1,1});
            test.evolve("out", [&](double a){return a;});
            neuralNet test1("out");
            REQUIRE(test.evaluate({1,1}) == test1.evaluate({1,1}));
    }
    SECTION("Testing 3,2,1"){
            neuralNet test ({3,2,1},{1,1,1,1,1,1,1,1});
            test.evolve("out", [&](double a){return a;});
            neuralNet test1("out");
            for(double i = 0; i < 100; ++i)
                REQUIRE(test.evaluate({i,i,i}) == test1.evaluate({i,i,i}));
    }
}
TEST_CASE("Testing Medium Nets"){
    SECTION("Testing 32/40/10/1"){
        vector<double> weights;
        vector<double> inputs;
        weights.resize(1690, 1);
        neuralNet test ({32,40,10,1}, weights);
        test.evolve("out", [&](double a){return a;});
        neuralNet test1("out");
        for(double i = 0; i < 100; ++i){
            inputs.clear();
            inputs.resize(32,i);
            REQUIRE(test.evaluate(inputs) == test1.evaluate(inputs));
        }
    }
    SECTION("Testing 32/40/40/10/1"){
        vector<double> weights;
        vector<double> inputs;
        weights.resize(3290, 1);
        neuralNet test ({32,40,40,10,1}, weights);
        test.evolve("out", [&](double a){return a;});
        neuralNet test1("out");
        for(double i = 0; i < 100; ++i){
            inputs.clear();
            inputs.resize(32,i);
            REQUIRE(test.evaluate(inputs) == test1.evaluate(inputs));
        }
    }
}
