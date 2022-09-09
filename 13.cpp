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
#include <map>
#include <set>

using namespace std;

static const int SIZE = 2000;

typedef array<array<bool, SIZE>, SIZE> map_t;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

void fold(map_t& m, char dir, size_t val) {
    if (dir == 'x') {
        for (size_t i = 0; i < val; i++) {
            size_t fold_i = val + abs(static_cast<int>(val - i));
            for (size_t j = 0; j < SIZE; j++) {
                m[i][j] |= m[fold_i][j];
                m[fold_i][j] = false;
            }
        }
    } else if (dir == 'y') {
        for (size_t i = 0; i < val; i++) {
            size_t fold_i = val + abs(static_cast<int>(val - i));
            for (size_t j = 0; j < SIZE; j++) {
                m[j][i] |= m[j][fold_i];
                m[j][fold_i] = false;
            }
        }
    }
}

size_t count_holes(map_t& m) {
    size_t ans = 0;

    for (const auto& r : m) {
        for (const auto& c : r) {
            ans += c;
        }
    }

    return ans;
}

void print(map_t& m, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            cout << (m[i][j] ? '#' : '.');
        }
        cout << endl;
    }
}

int main() {
    ifstream fin("13.in");
    string line;

    bool is_fold_section = false;

    map_t m;
    for (auto& r : m) {
        for (auto& c : r) {
            c = false;
        }
    }

    while (getline(fin, line)) {
        if (is_fold_section) {
            istringstream istream(line);
            remove_substr(istream, "fold along ");

            char c;
            size_t val;

            istream >> c;
            remove_substr(istream, "=");
            istream >> val;

            fold(m, c, val);

            cout << c << " - " << val << "; " << count_holes(m) << endl;
        } else {
            if (line == "") {
                is_fold_section = true;
            } else {
                istringstream istream(line);

                size_t x, y;

                istream >> x;
                remove_substr(istream, ",");
                istream >> y;

                m[x][y] = true;
            }
        }
    }

    print(m, 70);

    return 0;
}