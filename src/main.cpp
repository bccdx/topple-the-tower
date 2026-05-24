// src/main.cpp
#include "Counter.h"
#include <iostream>
 
int main() {
    Counter c;
    c.increment();
    c.increment();
    c.increment();
    std::cout << "Counter value: " << c.getValue() << std::endl;
    return 0;
}