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

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

bool test_vector(int x, int y, int x_min, int x_max, int y_min, int y_max) {
    bool x_running = true;
    bool y_can_hit = true;

    int x_cur = 0;
    int y_cur = 0;

    while (x_running || y_can_hit) {
        x_cur += x;
        y_cur += y;

        if (x) x--;
        y--;

        x_running = x > 0;
        y_can_hit = y_cur >= y_min;

        if (((x_min <= x_cur) && (x_cur <= x_max))
        &&  ((y_min <= y_cur) && (y_cur <= y_max))) {
            return true;
        }
    }

    return false;
}

int main() {
    ifstream fin("17.in");
    string line;

    int x_min, x_max;
    int y_min, y_max;

    int total = 0;

    while (getline(fin, line)) {
        istringstream istream(line);

        remove_substr(istream, "target area: x=");
        istream >> x_min;
        remove_substr(istream, "..");
        istream >> x_max;
        remove_substr(istream, ", y=");
        istream >> y_min;
        remove_substr(istream, "..");
        istream >> y_max;
    }

    for (int x = 1; x <= x_max; x++) {
        for (int y = y_min; y < abs(y_min); y++) {
            total += test_vector(x, y, x_min, x_max, y_min, y_max);
        }
    }

    cout << total << endl;

    return 0;
}