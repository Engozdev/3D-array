#include "lib/include/Array17bit.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> binary(uint32_t y) {
    vector<bool> temp;
    while (y) {
        temp.push_back(y % 2);
        y /= 2;
    }
    reverse(temp.begin(), temp.end());
    if (temp.empty())
        temp.push_back(false);
    return temp;
}

int main() {
    int x = 6, y = 85, z = 257;
    Array17bit a = Array17bit::make_array(x, y, z);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                a[i][j][k] = i * y * z + j * z + k;
                cout << a[i][j][k] << "\n";
            }
        }
    }
    return 0;
}
