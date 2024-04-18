#include "lib/include/Array17bit.h"

#include <gtest/gtest.h>
#include <sstream>


TEST(Array17bitTestSuite, SizeTest) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    ASSERT_EQ(a.getSize(), (x * y * z * 17 + 7) / 8);
}

TEST(Array17bitTestSuite, CreatingNegativeSizeArray) {
    int x = -1, y = 2, z = 3;
    ASSERT_DEATH(Array17bit::make_array(x, y, z), "Invalid size of array");
}

TEST(Array17bitTestSuite, GettingOutOfRangeElement) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    ASSERT_DEATH(a[5][5][5], "Array index out of range");
}

TEST(Array17bitTestSuite, GettingPositiveElement) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    a[0][0][0] = 23;
    int val = a[0][0][0];
    ASSERT_EQ(val, 23);
}

TEST(Array17bitTestSuite, GettingNegativeElement) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    a[0][0][0] = -23;
    int val = a[0][0][0];
    ASSERT_EQ(val, kUint17Max + 1 - 23);
}

TEST(Array17bitTestSuite, RewritingElement) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    a[0][0][0] = 23;
    ASSERT_EQ(static_cast<int>(a[0][0][0]), 23);
    a[0][0][0] = 17;
    ASSERT_EQ(static_cast<int>(a[0][0][0]), 17);
}

TEST(Array17bitTestSuite, GettingMultipleExistingElement) {
    int x = 6, y = 85, z = 257; // 6 * 85 * 257 = 131070
    Array17bit a = Array17bit::make_array(x, y, z);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                a[i][j][k] = i * y * z + j * z + k;
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                int val = a[i][j][k];
                ASSERT_EQ(val, cnt++);
            }
        }
    }
}

TEST(Array17bitTestSuite, OutputElement) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    a[0][0][0] = 23;
    std::stringstream out;
    out << a[0][0][0];
    std::string expected = std::to_string(a[0][0][0]);
    ASSERT_EQ(out.str(), expected);
}

TEST(Array17bitTestSuite, InputElement) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    std::istringstream in("23");
    in >> a[0][0][0];
    int expected = 23;
    ASSERT_EQ(static_cast<int>(a[0][0][0]), expected);
}

TEST(Array17bitTestSuite, MultiplicationByPositiveNumber) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                a[i][j][k] = 1;
            }
        }
    }
    Array17bit b = a * 7;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                int val = b[i][j][k];
                ASSERT_EQ(val, 7);
            }
        }
    }
}

TEST(Array17bitTestSuite, MultiplicationByZero) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                a[i][j][k] = 1;
            }
        }
    }
    Array17bit b = a * 0;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                int val = b[i][j][k];
                ASSERT_EQ(val, 0);
            }
        }
    }
}

TEST(Array17bitTestSuite, MultiplicationByNegativeNumber) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                a[i][j][k] = 1;
            }
        }
    }
    ASSERT_DEATH(a * -1, "Negative multiplier is unacceptable");
}

TEST(Array17bitTestSuite, AddingDiffrentSizesArrays) {
    int x1 = 1, y1 = 2, z1 = 3;
    Array17bit a = Array17bit::make_array(x1, y1, z1);
    int x2 = 3, y2 = 2, z2 = 1;
    Array17bit b = Array17bit::make_array(x2, y2, z2);
    for (int i = 0; i < x1; ++i) {
        for (int j = 0; j < y1; ++j) {
            for (int k = 0; k < z1; ++k) {
                a[i][j][k] = 1;
            }
        }
    }
    for (int i = 0; i < x2; ++i) {
        for (int j = 0; j < y2; ++j) {
            for (int k = 0; k < z2; ++k) {
                b[i][j][k] = 1;
            }
        }
    }
    ASSERT_DEATH(a + b, "Different size of input arrays");
}

TEST(Array17bitTestSuite, AddingArrays) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    Array17bit b = Array17bit::make_array(x, y, z);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                a[i][j][k] = 1;
                b[i][j][k] = 2;
            }
        }
    }
    Array17bit c = a + b;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                int val = c[i][j][k];
                ASSERT_EQ(val, 3);
            }
        }
    }
}

TEST(Array17bitTestSuite, SubstractingDiffrentSizesArrays) {
    int x1 = 1, y1 = 2, z1 = 3;
    Array17bit a = Array17bit::make_array(x1, y1, z1);
    int x2 = 3, y2 = 2, z2 = 1;
    Array17bit b = Array17bit::make_array(x2, y2, z2);
    for (int i = 0; i < x1; ++i) {
        for (int j = 0; j < y1; ++j) {
            for (int k = 0; k < z1; ++k) {
                a[i][j][k] = 1;
            }
        }
    }
    for (int i = 0; i < x2; ++i) {
        for (int j = 0; j < y2; ++j) {
            for (int k = 0; k < z2; ++k) {
                b[i][j][k] = 1;
            }
        }
    }
    ASSERT_DEATH(a - b, "Different size of input arrays");
}

TEST(Array17bitTestSuite, SubstractingArrays) {
    int x = 1, y = 2, z = 3;
    Array17bit a = Array17bit::make_array(x, y, z);
    Array17bit b = Array17bit::make_array(x, y, z);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                a[i][j][k] = 2;
                b[i][j][k] = 1;
            }
        }
    }
    Array17bit c = a - b;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                int val = c[i][j][k];
                ASSERT_EQ(val, 1);
            }
        }
    }
}

TEST(Array17bitTestSuite, CopyTest) {
    Array17bit original = Array17bit::make_array(2, 2, 2);
    Array17bit copy = Array17bit::make_array(2, 2, 2);
    original[1][1][1] = 28;
    copy = original;
    ASSERT_EQ(static_cast<int>(copy[1][1][1]), 28);
    ASSERT_EQ(static_cast<int>(original[1][1][1]), 28);
    copy[1][1][1] = 5;
    ASSERT_EQ(static_cast<int>(original[1][1][1]), 28);
    ASSERT_EQ(static_cast<int>(copy[1][1][1]), 5);
}