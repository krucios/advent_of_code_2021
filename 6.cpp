#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>
#include <array>

using namespace std;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

int main() {
    ifstream fin("6.in");
    string line;

    array<uint64_t, 9> fishes;

    for (auto& e : fishes) e = 0;

    while (getline(fin, line)) {
        int val;

        istringstream istream(line);

        while (!istream.eof()) {
            istream >> val;
            fishes[val]++;
            remove_substr(istream, ",");
        }
    }

    for (int gen = 1; gen <= 256; gen++) {
        array<uint64_t, 9> new_fishes;
        
        new_fishes[8] = fishes[0];
        new_fishes[7] = fishes[8];
        new_fishes[6] = fishes[7];
        new_fishes[5] = fishes[6];
        new_fishes[4] = fishes[5];
        new_fishes[3] = fishes[4];
        new_fishes[2] = fishes[3];
        new_fishes[1] = fishes[2];
        new_fishes[0] = fishes[1];

        new_fishes[6] += fishes[0];

        fishes = new_fishes;

        cout << "Completed gen: " << gen << endl;
    }

    uint64_t ans = 0;
    for (auto f : fishes) ans += f;

    cout << ans << endl;

    return 0;
}