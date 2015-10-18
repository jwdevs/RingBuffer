//
//  Queue.h
//  CTest
//
//  Created by Jakub Wozniak on 28/10/14.
//  Copyright (c) 2014 Jakub Wozniak. All rights reserved.
//

#ifndef CTest_Queue_h
#define CTest_Queue_h
#include "stdlib.h"

template<typename T, typename R,  R CAPACITY>
class RingBuffer
{
    //+1 for empty empty/full condition
    T data[CAPACITY];
    
    R increment(R value) {
        return (value+1)%(capacity());
    }
    R nbOfElts{0};
    
public:
    //first free elemement
    R start{0};
    //element to pop
    R end{0};
    
    RingBuffer() {
    }

    T& peek() {
        return (*this)[0];
    }
    
    T& operator[](R idx) {
        R index = (end + idx)%(capacity());
        return data[index];
    }
    
    bool offer(T& obj) {
        if(!isFull()) {
            data[start] = obj;
            start = increment(start);
            ++nbOfElts;
            return true;
        } else {
            return false;
        }
    }
    
    bool poll(T& ret) {
        if(!isEmpty()) {
            R index = end;
            end = increment(end);
            ret = data[index];
            --nbOfElts;
            return true;
        } else {
            return false;
        }
    }
    
    
    R size() {
        return nbOfElts;
    }
    
    R capacity() {
        return CAPACITY;
    }
    
    bool isEmpty() {
        return nbOfElts==0;
    }
    
    bool isFull() {
        return nbOfElts == CAPACITY;
    }
};
#endif
