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

static const size_t ROWS = 500;
static const size_t COLS = 500;

typedef array<array<size_t, COLS>, ROWS> matrix_t;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

matrix_t find_min_path(matrix_t& m) {
    matrix_t e;
    queue<pair<size_t, size_t>> q;

    for (auto& r : e) {
        for (auto& c : r) {
            c = SIZE_MAX;
        }
    }
    e[0][0] = 0;

    q.push(make_pair(0, 0));

    while (!q.empty()) {
        pair<size_t, size_t> cur = q.front();
        q.pop();

        int dr, dc;
        size_t new_val;

        dr = cur.first - 1;
        dc = cur.second;
        new_val = e[cur.first][cur.second] + m[dr][dc];
        if (dr >= 0 && e[dr][dc] > new_val) {
            e[dr][dc] = new_val;
            q.push(make_pair(dr, dc));
        }

        dr = cur.first;
        dc = cur.second + 1;
        new_val = e[cur.first][cur.second] + m[dr][dc];
        if (dc < COLS && e[dr][dc] > new_val) {
            e[dr][dc] = new_val;
            q.push(make_pair(dr, dc));
        }

        dr = cur.first + 1;
        dc = cur.second;
        new_val = e[cur.first][cur.second] + m[dr][dc];
        if (dr < ROWS && e[dr][dc] > new_val) {
            e[dr][dc] = new_val;
            q.push(make_pair(dr, dc));
        }

        dr = cur.first;
        dc = cur.second - 1;
        new_val = e[cur.first][cur.second] + m[dr][dc];
        if (dc >= 0 && e[dr][dc] > new_val) {
            e[dr][dc] = new_val;
            q.push(make_pair(dr, dc));
        }
    }

    return e;
}

int main() {
    ifstream fin("15.in");
    string line;

    int total = 0;
    matrix_t m;
    matrix_t e;

    size_t row = 0;
    while (getline(fin, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            size_t val = line[i] - '0';
            for (size_t r = 0; r < 5; r++) {
                for (size_t c = 0; c < 5; c++) {
                    size_t new_val = val + r + c;
                    m[row + r * (ROWS / 5)][i + c * (COLS / 5)] = (new_val > 9) ? (new_val - 9) : new_val;
                }
            }
        }
        row++;
    }

    e = find_min_path(m);

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            cout << e[r][c] % 10;
        }
        cout << endl;
    }

    cout << e[ROWS - 1][COLS - 1] << endl;

    return 0;
}