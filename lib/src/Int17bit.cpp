#include "../include/Int17bit.h"

#include <vector>
#include <algorithm>


uint17_t::uint17_t() : cur_byte_(nullptr), padding_(0), cur_(0) {};

uint17_t::uint17_t(uint8_t* a, int pos, uint8_t pad) : cur_(pos), padding_(pad), cur_byte_(a + pos) {}

[[nodiscard]]uint8_t uint17_t::GetPadding() const {
    return padding_;
}

[[nodiscard]]uint8_t* uint17_t::GetCurByte() const {
    return cur_byte_;
}

[[nodiscard]]uint8_t* uint17_t::GetNextByte() const {
    return cur_byte_ + 1;
}

uint17_t::operator int() {
    int mask = pow(2, 8 - padding_) - 1;
    int32_t res = *cur_byte_ & mask;
    res <<= 8;
    cur_byte_++;
    res |= *cur_byte_;
    cur_byte_++;
    res <<= (padding_ + 1);
    res |= *cur_byte_ >> (8 - padding_ - 1);
    return res;
}

uint17_t& uint17_t::operator=(uint32_t val) {
    val &= kUint17Max;
    *cur_byte_ = (*cur_byte_ >> (8 - padding_)) << (8 - padding_);
    *cur_byte_ |= (val >> (8 + padding_ + 1));
    cur_byte_++;
    *cur_byte_ = val >> (padding_ + 1);
    cur_byte_++;
    *cur_byte_ = (*cur_byte_ << (padding_ + 1));
    *cur_byte_ >>= (padding_ + 1);
    *cur_byte_ |= (val & ((uint32_t) pow(2, padding_ + 1) - 1)) << (8 - padding_ - 1);
    return *this;
}

std::istream& operator>>(std::istream& stream, uint17_t num) {
    uint32_t val;
    stream >> val;
    num = val;
    return stream;
}