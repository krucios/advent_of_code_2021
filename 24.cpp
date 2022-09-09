#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include <utility>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <cmath>
#include <array>
#include <list>

using namespace std;

typedef array<uint8_t, 14> model_t;

bool monad(model_t id) {
    int w = 0;
    int x = 0;
    int y = 0;
    int z = 0;

    w = id[0];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 10;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 5;
    y *= x;
    z += y;
    w = id[1];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 13;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 9;
    y *= x;
    z += y;
    w = id[2];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 12;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 4;
    y *= x;
    z += y;
    w = id[3];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -12;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 4;
    y *= x;
    z += y;
    w = id[4];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 11;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 10;
    y *= x;
    z += y;
    w = id[5];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -13;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 14;
    y *= x;
    z += y;
    w = id[6];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -9;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 14;
    y *= x;
    z += y;
    w = id[7];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -12;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 12;
    y *= x;
    z += y;
    w = id[8];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 14;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 14;
    y *= x;
    z += y;
    w = id[9];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -9;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 14;
    y *= x;
    z += y;
    w = id[10];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 15;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 5;
    y *= x;
    z += y;
    w = id[11];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 11;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 10;
    y *= x;
    z += y;
    w = id[12];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -16;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 8;
    y *= x;
    z += y;
    w = id[13];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -2;
    x = x == w;
    x = x == 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 15;
    y *= x;
    z += y;

    return z == 0;
}

bool monad2(model_t id) {
    int w = 0;
    int x = 0;
    int y = 0;
    int z = 0;

    w = id[0];
    x = 1;
    z = w + 5;

    w = id[1];
    z *= 26;
    z += w + 9;

    w = id[2];
    y = w + 4;

    w = id[3];
    x = y - 12;
    x = x != w;
    y = 25 * x + 1;
    z *= y;
    y = w + 4;
    y *= x;
    z += y;

    w = id[4];
    x = 1;
    y = w + 10;

    w = id[5];
    x = y - 13;
    x = x != w;
    y = 25 * x + 1;
    z *= y;
    y = w + 14;
    y *= x;
    z += y;

    w = id[6];
    x = z % 26 - 9;
    z /= 26;
    x = x != w;
    y = 25 * x + 1;
    z *= y;
    y = w + 14;
    y *= x;
    z += y;

    w = id[7];
    x = z % 26 - 12;
    z /= 26;
    x = x != w;
    y = 25 * x + 1;
    z *= y;
    y = w + 12;
    y *= x;
    z += y;

    w = id[8];
    x = 1;
    y = w + 14;

    w = id[9];
    x = y - 9;
    x = x != w;
    y = 25 * x + 1;
    z *= y;
    y = w + 14;
    y *= x;
    z += y;

    w = id[10];
    x = 1;
    z *= 26;
    y = w + 5;
    z += y;

    w = id[11];
    x = 1;
    y = w + 10;

    w = id[12];
    x = y - 16;
    x = x != w;
    y = 25 * x + 1;
    z *= y;
    y = w + 8;
    y *= x;
    z += y;

    w = id[13];
    x = z % 26 - 2;
    z /= 26;
    x = x != w; // x == w
    y = 25 * x + 1;
    z *= y;
    y = w + 15;
    y *= x; // x should be 0
    z += y; // z should be 0

    return z == 0;
}

#define loop(var) for (uint8_t var = 1; var <= 9; var++)

int main() {
    loop(a1 ) {
    loop(a2 ) {
    loop(a3 ) {
    // for (uint8_t a3 = 9; a3 <= 9; a3++) {
    loop(a4 ) {
    loop(a5 ) {
    loop(a6 ) {
    loop(a7 ) {
    loop(a8 ) {
    for (uint8_t a9 = 1; a9 <= 4; a9++) {
    for (uint8_t a11 = 1; a11 <= 6; a11++) {
    for (uint8_t a12 = 7; a12 <= 9; a12++) {
        uint8_t a10 = a9 + 5;
        uint8_t a13 = a12 - 6;
        uint8_t a14 = a11 + 3;
        if (monad2((model_t){a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14})) {
            cout << (int)a1 << (int)a2 << (int)a3 << (int)a4 << (int)a5 << (int)a6 << (int)a7 << (int)a8 << (int)a9 << (int)a10 << (int)a11 << (int)a12 << (int)a13 << (int)a14 << endl;
            return 0;
        }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    cout << "a2 = " << (int)a2 << endl;
    }
    }

    return 0;
}
