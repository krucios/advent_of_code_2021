#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream fin("1.in");
    string line;

    vector<int> arr;

    while (getline(fin, line)) {
        istringstream istream(line);

        int val;

        istream >> val;
        arr.push_back(val);
    }

    int ans = 0;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i - 1] < arr[i]) {
            ans++;
        }
    }

    cout << ans << endl;

    ans = 0;
    for (int i = 3; i < arr.size() - 3; i++) {
        if ((arr[i - 3] + arr[i - 2] + arr[i -1])
        <   (arr[i - 2] + arr[i - 1] + arr[i])) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}