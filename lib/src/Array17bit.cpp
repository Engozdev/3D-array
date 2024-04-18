#include "../include/Array17bit.h"

#include <cmath>
#include <iostream>

Array17bit::Array17bit(int x, int y, int z) : x_(x), y_(y), z_(z), size_((x * y * z * 17 + 7) / 8) {
    arr_3d_ = new uint8_t[size_];
    std::fill(arr_3d_, arr_3d_ + size_, 0);
}

[[nodiscard]] int Array17bit::getX() const {
    return x_;
}

[[nodiscard]] int Array17bit::getY() const {
    return y_;
}

[[nodiscard]] int Array17bit::getZ() const {
    return z_;
}

[[nodiscard]] int Array17bit::getSize() const {
    return size_;
}

Iterator2D Array17bit::operator[](int i) { return {arr_3d_, z_, i * y_ * z_, size_}; }

Array17bit operator+(Array17bit& lhs, Array17bit& rhs) {
    if (lhs.getX() != rhs.getX() || lhs.getY() != rhs.getY() || lhs.getZ() != rhs.getZ()) {
        std::cerr << "Different size of input arrays" << std::endl;
        exit(EXIT_FAILURE);
    }
    Array17bit res(lhs.getX(), lhs.getY(), lhs.getZ());
    for (int i = 0; i < lhs.getX(); ++i) {
        for (int j = 0; j < lhs.getY(); ++j) {
            for (int k = 0; k < lhs.getZ(); ++k) {
                uint32_t a = lhs[i][j][k], b = rhs[i][j][k];
                res[i][j][k] = a + b;
            }
        }
    }
    return res;
}

Array17bit operator-(Array17bit& lhs, Array17bit& rhs) {
    if (lhs.getX() != rhs.getX() || lhs.getY() != rhs.getY() || lhs.getZ() != rhs.getZ()) {
        std::cerr << "Different size of input arrays" << std::endl;
        exit(EXIT_FAILURE);
    }
    Array17bit res = Array17bit::make_array(lhs.getX(), lhs.getY(), lhs.getZ());
    for (int i = 0; i < lhs.getX(); ++i) {
        for (int j = 0; j < lhs.getY(); ++j) {
            for (int k = 0; k < lhs.getZ(); ++k) {
                uint32_t a = lhs[i][j][k], b = rhs[i][j][k];
                int32_t c = a - b;
                if (c < 0)
                    res[i][j][k] = kUint17Max + 1 + c;
                else
                    res[i][j][k] = c;
            }
        }
    }
    return res;
}

Array17bit operator*(Array17bit& lhs, int32_t n) {
    if (n < 0) {
        std::cerr << "Negative multiplier is unacceptable" << std::endl;
        exit(EXIT_FAILURE);
    }
    Array17bit res = Array17bit::make_array(lhs.getX(), lhs.getY(), lhs.getZ());
    for (int i = 0; i < lhs.getX(); ++i) {
        for (int j = 0; j < lhs.getY(); ++j) {
            for (int k = 0; k < lhs.getZ(); ++k) {
                res[i][j][k] = lhs[i][j][k] * n;
            }
        }
    }
    return res;
}

std::ostream& operator<<(std::ostream& stream, Array17bit& value) {
    for (int i = 0; i < value.getY(); ++i) {
        for (int j = 0; j < value.getX(); ++j) {
            for (int k = 0; k < value.getZ(); ++k) {
                std::cout << value[j][i][k] << '\t';
            }
            std::cout << '\t';
        }
        std::cout << '\n';
    }
    return stream;
}

Array17bit Array17bit::make_array(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0) {
        std::cerr << "Invalid size of array" << std::endl;
        exit(EXIT_FAILURE);
    }
    return Array17bit(x, y, z);
}

Array17bit::~Array17bit() {
    delete[] arr_3d_;
}

Array17bit::Array17bit(const Array17bit& other) : arr_3d_(other.arr_3d_ != nullptr ? new uint8_t[other.size_] : nullptr),
                                                  x_(other.x_), y_(other.y_), z_(other.z_), size_(other.size_) {
    for (int i = 0; i < other.size_; ++i) {
        arr_3d_[i] = other.arr_3d_[i];
    }
}

Array17bit& Array17bit::operator=(const Array17bit& other) {
    Array17bit temp(other);
    x_ = temp.x_;
    y_ = temp.y_;
    z_ = temp.z_;
    size_ = temp.size_;
    std::swap(arr_3d_, temp.arr_3d_);

    return *this;
}
