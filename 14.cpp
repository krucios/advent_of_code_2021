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

typedef map<string, string> rules_t;

int main() {
    ifstream fin("14.in");
    string line;
    string polymer;

    rules_t rules;

    bool is_polymer_section = true;


    while (getline(fin, line)) {
        if (is_polymer_section) {
            polymer = line;
            is_polymer_section = false;
        } else {
            if (line == "") {
                continue;
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