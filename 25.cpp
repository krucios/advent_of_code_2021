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

using namespace std;

static const size_t ROWS = 137;
static const size_t COLS = 139;

typedef array<array<char, COLS>, ROWS> matrix_t;

void print(const matrix_t& m) {
    for (auto& r : m) {
        for (auto& e : r) {
            cout << e;
        }
        cout << endl;
    }
}

bool is_equal(const matrix_t& m1, const matrix_t& m2) {
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            if (m1[i][j] != m2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

matrix_t step(const matrix_t& m) {
    matrix_t east_m = m;

    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            if (m[i][j] == '>') {
                size_t new_j = (j + 1) % COLS;

                if (m[i][new_j] == '.') {
                    east_m[i][j]     = '.';
                    east_m[i][new_j] = '>';
                }
            }
        }
    }

    matrix_t south_m = east_m;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            if (east_m[i][j] == 'v') {
                size_t new_i = (i + 1) % ROWS;

                if (east_m[new_i][j] == '.') {
                    south_m[i][j]     = '.';
                    south_m[new_i][j] = 'v';
                }
            }
        }
    }

    /*
    cout << "East (>) ";
    for (int i = 0; i < COLS - 9; i++) cout << " ";

    for (int i = 0; i < 5; i++) cout << " ";

    cout << "South (V) ";
    for (int i = 0; i < COLS - 10; i++) cout << " ";
    cout << endl;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << east_m[i][j];
        }

        for (int i = 0; i < 5; i++) cout << " ";

        for (int j = 0; j < COLS; j++) {
            cout << south_m[i][j];
        }

        cout << endl;
    }
    */

    return south_m;
}

int main() {
    ifstream fin("25.in");
    string line;

    matrix_t m;

    size_t row = 0;
    while (getline(fin, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            m[row][i] = line[i];
        }
        row++;
    }

    size_t turn = 0;
    matrix_t old_m;

    do {
        old_m = m;
        m = step(m);
        turn++;
    } while (!is_equal(old_m, m));

    cout << turn << endl;

    return 0;
}