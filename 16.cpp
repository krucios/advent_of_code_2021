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

size_t read_bits(vector<bool>& v, size_t& pos, size_t cnt) {
    size_t val = 0;

    for (size_t i = 0; i < cnt; i++) {
        val <<= 1;
        val |= v[pos++];
    }

    return val;
}

uint64_t process_packet(vector<bool>& v, size_t& pos) {
    size_t ver = 0;
    size_t tid = 0;
    uint64_t val = 0;

    vector<uint64_t> args;

    ver = read_bits(v, pos, 3);
    tid = read_bits(v, pos, 3);

    cout << "New packet. Ver: " << ver << ", TID: " << tid << endl;

    if (tid == 4) {
        bool is_continue;

        do {
            is_continue = v[pos++];

            uint64_t part = read_bits(v, pos, 4);
            val <<= 4;
            val |= part;
        } while (is_continue);

        cout << "Literal value: " << val << endl;
    } else {
        size_t len = 0;
        bool L = v[pos++];

        cout << "Length type: " << L <<", ";
        if (L) {
            len = read_bits(v, pos, 11);

            cout << "sub-packet amount: " << len << endl;
            for (size_t i = 0; i < len; i++) {
                args.push_back(process_packet(v, pos));
            }
        } else {
            size_t old_pos;

            len = read_bits(v, pos, 15);
            old_pos = pos;

            cout << "sub-packet bit length: " << len << endl;
            while (pos < old_pos + len) {
                args.push_back(process_packet(v, pos));
            }
        }

        switch (tid) {
        case 0:
            for (auto& e : args) {
                val += e;
            }
            break;
        case 1:
            val = 1;
            for (auto& e : args) {
                val *= e;
            }
            break;
        case 2:
            val = args[0];
            for (auto& e : args) {
                if (e < val) {
                    val = e;
                }
            }
            break;
        case 3:
            val = args[0];
            for (auto& e : args) {
                if (e > val) {
                    val = e;
                }
            }
            break;
        case 5:
            val = args[0] > args[1];
            break;
        case 6:
            val = args[0] < args[1];
            break;
        case 7:
            val = args[0] == args[1];
            break;
        }
    }

    return val;
}

int main() {
    ifstream fin("16.in");
    string line;
    vector<bool> v;

    int total = 0;

    while (getline(fin, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            size_t val = (line[i] >= 'A') ? (line[i] - 'A' + 10) : (line[i] - '0');

            v.push_back(static_cast<bool>(val & 0x8));
            v.push_back(static_cast<bool>(val & 0x4));
            v.push_back(static_cast<bool>(val & 0x2));
            v.push_back(static_cast<bool>(val & 0x1));
        }
    }

    for (auto b : v) {
        cout << b;
    }
    cout << endl;

    size_t pos = 0;
    cout << process_packet(v, pos) << endl;

    return 0;
}