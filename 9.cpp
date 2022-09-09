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

static const size_t ROWS = 100;
static const size_t COLS = 100;

typedef array<array<size_t, COLS>, ROWS> matrix_t;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

size_t basin_size(matrix_t& m, size_t r, size_t c) {
    queue<pair<size_t, size_t>> q;
    size_t size = 0;

    q.push(make_pair(r, c));

    while (!q.empty()) {
        pair<size_t, size_t> cur = q.front();
        q.pop();

        m[cur.first][cur.second] = 9;
        size++;

        int dr, dc;

        dr = cur.first - 1;
        dc = cur.second;
        if (dr >= 0 && m[dr][dc] != 9) {
            q.push(make_pair(dr, dc));
            m[dr][dc] = 9;
        }

        dr = cur.first;
        dc = cur.second + 1;
        if (dc < COLS && m[dr][dc] != 9) {
            q.push(make_pair(dr, dc));
            m[dr][dc] = 9;
        }

        dr = cur.first + 1;
        dc = cur.second;
        if (dr < ROWS && m[dr][dc] != 9) {
            q.push(make_pair(dr, dc));
            m[dr][dc] = 9;
        }

        dr = cur.first;
        dc = cur.second - 1;
        if (dc >= 0 && m[dr][dc] != 9) {
            q.push(make_pair(dr, dc));
            m[dr][dc] = 9;
        }
    }

    return size;
}

int main() {
    ifstream fin("9.in");
    string line;

    int total = 0;
    matrix_t m;

    vector<size_t> sizes;

    size_t row = 0;
    while (getline(fin, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            m[row][i] = line[i] - '0';
        }
        row++;
    }

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            cout << m[r][c];
        }
        cout << endl;
    }

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (r - 1 >=  0  && m[r - 1][c    ] <= m[r][c]) continue;
            if (c + 1 < COLS && m[r    ][c + 1] <= m[r][c]) continue;
            if (r + 1 < ROWS && m[r + 1][c    ] <= m[r][c]) continue;
            if (c - 1 >=  0  && m[r    ][c - 1] <= m[r][c]) continue;

            total += m[r][c] + 1;

            sizes.push_back(basin_size(m, r, c));
        }
    }

    sort(sizes.begin(), sizes.end());
    reverse(sizes.begin(), sizes.end());

    for (auto& e : sizes) {
        cout << e << " ";
    }
    cout << endl;

    uint64_t ans = sizes[0];
    ans *= sizes[1];
    ans *= sizes[2];

    cout << "Answer (1): " << total << endl;
    cout << "Answer (2): " << ans << endl;

    return 0;
}