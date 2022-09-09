#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>
#include <limits>
#include <array>

using namespace std;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

int count_steps(vector<int> v, int pos) {
    int ans = 0;
    for (auto& e : v) {
        ans += ((1 + abs(e - pos)) * (abs(e - pos))) / 2;
    }
    return ans;
}

int main() {
    ifstream fin("7.in");
    string line;

    vector<int> crabs;

    int total = 0;
    while (getline(fin, line)) {
        int val;

        istringstream istream(line);

        while (!istream.eof()) {
            istream >> val;
            crabs.push_back(val);
            total += val;
            cout << "Add: " << val << endl;
            remove_substr(istream, ",");
        }
    }

    int min = INT32_MAX;
    int pos = 0;

    for (int i = *(min_element(crabs.begin(), crabs.end())), stop = *(max_element(crabs.begin(), crabs.end())); i <= stop; i++) {
        int cur_count = count_steps(crabs, i);
        if (cur_count < min) {
            min = cur_count;
            pos = i;
        }
    }

    cout << pos << " - " << min << endl;

    return 0;
}