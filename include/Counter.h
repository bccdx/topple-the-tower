// include/Counter.h
#ifndef COUNTER_H
#define COUNTER_H
 
class Counter {
private:
    int value;
 
public:
    Counter();
 
    int getValue() const;
 
    void increment();
    void decrement();
    void reset();
};
 
#endif