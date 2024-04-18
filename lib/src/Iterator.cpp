#include "../include/Iterator.h"

Iterator::Iterator(uint8_t* a, int pos, int sz) : arr_(a), cur_(pos), size_(sz) {}

uint17_t Iterator::operator[](int k) {
    uint8_t padding_ = (cur_ + k) % 8;
    int pos = 2 * (cur_ + k);
    pos += pos / 16;
    if (pos > size_) {
        std::cerr << "Array index out of range" << std::endl;
        exit(EXIT_FAILURE);
    }
    return {arr_, pos, padding_};
}