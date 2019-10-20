#include <iostream>
#include "receiver.h"


void receiver::run() {
    this -> output -> run();
    // this -> demod -> run();
    this -> input -> run();

    std::cerr << "Running..." << std::endl;
}

void receiver::stop() {
    this -> input -> stop();
    // this -> demod -> stop();
    this -> output -> stop();

    std::cerr << "Stopped." << std::endl;
}