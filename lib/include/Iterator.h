#ifndef LABWORK5_ITERATOR_H
#define LABWORK5_ITERATOR_H
#pragma once

#include "../include/Int17bit.h"

#include <iostream>

class Iterator {
private:
    uint8_t* arr_;
    int cur_, size_;
public:
    Iterator(uint8_t* a, int pos, int sz);

    uint17_t operator[](int k);
};

#endif //LABWORK5_ITERATOR_H
