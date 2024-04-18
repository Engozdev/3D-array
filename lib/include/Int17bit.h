#ifndef LABWORK5_INT17BIT_H
#define LABWORK5_INT17BIT_H
#pragma once

#include <cmath>
#include <iostream>

const uint32_t kUint17Max = 0x0001FFFF;

class uint17_t {
private:
    uint8_t* cur_byte_;
    uint8_t padding_;
    int cur_;
public:
    uint17_t();
    uint17_t(uint8_t* a, int pos, uint8_t pad);

    [[nodiscard]]uint8_t GetPadding() const;
    [[nodiscard]]uint8_t* GetCurByte() const;
    [[nodiscard]]uint8_t* GetNextByte() const;

    operator int();
    uint17_t& operator=(uint32_t val);
    friend std::istream& operator>>(std::istream& stream, uint17_t num);
};

#endif //LABWORK5_INT17BIT_H
