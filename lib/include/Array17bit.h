#ifndef LABWORK5_ARRAY17BIT_H
#define LABWORK5_ARRAY17BIT_H
#pragma once

#include "Array17bit.h"
#include "Int17bit.h"
#include "Iterator2D.h"

#include <cmath>
#include <iostream>

class Array17bit {
public:
    Array17bit(int x, int y, int z);
    ~Array17bit();
    Array17bit(Array17bit const& other);
    Array17bit& operator=(Array17bit const& other);

    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getZ() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] Iterator2D operator[](int i);
    static Array17bit make_array(int x, int y, int z);

    friend Array17bit operator+(Array17bit& lhs, Array17bit& rhs);
    friend Array17bit operator-(Array17bit& lhs, Array17bit& rhs);
    friend Array17bit operator*(Array17bit& lhs, int32_t n);
    friend std::ostream& operator<<(std::ostream& stream, Array17bit& value);
private:
    uint8_t* arr_3d_;
    int x_, y_, z_, size_;
};

#endif //LABWORK5_ARRAY17BIT_H
