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

static const size_t PADDING = 60;

static const size_t ROWS = 100 + 2 * PADDING;
static const size_t COLS = 100 + 2 * PADDING;

typedef array<array<bool, COLS>, ROWS> matrix_t;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

void print(matrix_t& m) {
  for (size_t i = 0; i < ROWS; i++) {
      for (size_t j = 0; j < COLS; j++) {
          cout << (m[i][j] ? '#' : '.');
      }
      cout << endl;
  }
}

int main() {
    ifstream fin("20.in");
    string line;

    int total = 0;
    matrix_t m, new_m;

    for (auto& r : m) {
        for (auto& e : r) {
            e = false;
        }
    }

    array<bool, 512> v;

    getline(fin, line);
    for (size_t i = 0; i < line.length(); i++) {
        v[i] = line[i] == '#';
    }
    getline(fin, line);

    size_t row = 0;
    while (getline(fin, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            m[row + PADDING][i + PADDING] = line[i] == '#';
        }
        row++;
    }

    cout << "--== Before ==--" << endl;
    print(m);

    for (size_t step = 0; step < 50; step++) {
        for (size_t i = 1; i < ROWS - 1; i++) {
            for (size_t j = 1; j < COLS - 1; j++) {
                size_t index = 0;

                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        index <<= 1;
                        index |= m[i + di][j + dj];
                    }
                }

                new_m[i][j] = v[index];
            }
        }

        for (size_t i = 0; i < ROWS; i++) {
            new_m[i][0] = new_m[1][1];
            new_m[i][COLS - 1] = new_m[1][1];
        }


        for (size_t i = 0; i < COLS; i++) {
            new_m[0][i] = new_m[1][1];
            new_m[ROWS - 1][i] = new_m[1][1];
        }

        m = new_m;

        cout << "--== Step " << step << " ==--" << endl;
        // print(m);
    }

    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            if (m[i][j]) {
            total++;
            }
        }
    }

    cout << total << endl;

    return 0;
}