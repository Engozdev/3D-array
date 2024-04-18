#ifndef LABWORK5_ITERATOR2D_H
#define LABWORK5_ITERATOR2D_H
#pragma once

#include "../include/Iterator.h"

#include <iostream>

class Iterator2D {
private:
    int z_, cur_, size_;
    uint8_t* arr_2d_;
public:
    Iterator operator[](int j);

    Iterator2D(uint8_t* a, int z, int pos, int sz);
};

#endif //LABWORK5_ITERATOR2D_H
