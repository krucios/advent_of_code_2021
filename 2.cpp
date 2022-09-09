#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream fin("2.in");
    string line;

    vector<int> arr;

    int pos = 0;
    int depth = 0;
    int aim = 0;

    while (getline(fin, line)) {
        istringstream istream(line);

        string direction;
        int val;

        istream >> direction >> val;

        if (direction == "forward") {
            pos += val;
            depth += aim * val;
        } else if (direction == "down") {
            aim += val;
        } else if (direction == "up") {
            aim -= val;
        } else {
            cout << "Error!" << endl;
        }
    }

    int ans = pos * depth;

    cout << ans << endl;
    return 0;
}