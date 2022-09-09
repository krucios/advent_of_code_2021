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

static const size_t ROWS = 10;
static const size_t COLS = 10;

typedef array<array<size_t, COLS>, ROWS> matrix_t;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

size_t simulate(matrix_t& m, size_t generations = 1) {
    queue<pair<size_t, size_t>> q;
    size_t flashes = 0;

    for (int gen = 0; gen < generations; gen++) {
        bool all_flashed = true;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                m[i][j]++;
                if (m[i][j] > 9) {
                    m[i][j] = 1000;
                    q.push(make_pair(i, j));
                }
            }
        }

        while (!q.empty()) {
            pair<size_t, size_t> cur = q.front();
            q.pop();

            flashes++;

            int di, dj;

            di = cur.first - 1;
            dj = cur.second;
            if (di >= 0) {
                m[di][dj]++;
                if (m[di][dj] > 9 && m[di][dj] < 1000) {
                    m[di][dj] = 1000;
                    q.push(make_pair(di, dj));
                }
            }

            di = cur.first - 1;
            dj = cur.second + 1;
            if (di >= 0 && dj < COLS) {
                m[di][dj]++;
                if (m[di][dj] > 9 && m[di][dj] < 1000) {
                    m[di][dj] = 1000;
                    q.push(make_pair(di, dj));
                }
            }

            di = cur.first;
            dj = cur.second + 1;
            if (dj < COLS) {
                m[di][dj]++;
                if (m[di][dj] > 9 && m[di][dj] < 1000) {
                    m[di][dj] = 1000;
                    q.push(make_pair(di, dj));
                }
            }

            di = cur.first + 1;
            dj = cur.second + 1;
            if (di < ROWS && dj < COLS) {
                m[di][dj]++;
                if (m[di][dj] > 9 && m[di][dj] < 1000) {
                    m[di][dj] = 1000;
                    q.push(make_pair(di, dj));
                }
            }

            di = cur.first + 1;
            dj = cur.second;
            if (di < ROWS) {
                m[di][dj]++;
                if (m[di][dj] > 9 && m[di][dj] < 1000) {
                    m[di][dj] = 1000;
                    q.push(make_pair(di, dj));
                }
            }

            di = cur.first + 1;
            dj = cur.second - 1;
            if (di < COLS && dj >= 0) {
                m[di][dj]++;
                if (m[di][dj] > 9 && m[di][dj] < 1000) {
                    m[di][dj] = 1000;
                    q.push(make_pair(di, dj));
                }
            }

            di = cur.first;
            dj = cur.second - 1;
            if (dj >= 0) {
                m[di][dj]++;
                if (m[di][dj] > 9 && m[di][dj] < 1000) {
                    m[di][dj] = 1000;
                    q.push(make_pair(di, dj));
                }
            }

            di = cur.first - 1;
            dj = cur.second - 1;
            if (di >= 0 && dj >= 0) {
                m[di][dj]++;
                if (m[di][dj] > 9 && m[di][dj] < 1000) {
                    m[di][dj] = 1000;
                    q.push(make_pair(di, dj));
                }
            }
        }

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                all_flashed &= m[i][j] > 9;
                if (m[i][j] > 9) {
                    m[i][j] = 0;
                }
            }
        }

        if (all_flashed) {
            cout << "Flash generation: " << gen << endl;
        }
    }

    return flashes;
}

int main() {
    ifstream fin("11.in");
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

    cout << simulate(m, 1000) << endl;

    return 0;
}