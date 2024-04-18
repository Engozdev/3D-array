#include "../include/Iterator2D.h"

Iterator2D::Iterator2D(uint8_t* a, int z, int pos, int sz) : arr_2d_(a), z_(z), cur_(pos), size_(sz) {}

Iterator Iterator2D::operator[](int j) { return {arr_2d_, cur_ + j * z_, size_}; }
