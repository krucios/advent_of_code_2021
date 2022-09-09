#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>
#include <array>

using namespace std;

typedef array<array<int, 1000>, 1000> field_t;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

void add_cloud(field_t& f, int x1, int x2, int y1, int y2) {
    bool is_x1_greater = x1 > x2;
    bool is_y1_greater = y1 > y2;

    if (x1 == x2) {
        for (int i = y1; is_y1_greater ? i >= y2 : i <= y2; i += is_y1_greater ? -1 : 1) {
            f[i][x1]++;
        }
    } else if (y1 == y2) {
        for (int i = x1; is_x1_greater ? i >= x2 : i <= x2; i += is_x1_greater ? -1 : 1) {
            f[y1][i]++;
        }
    } else {
        for (int i = x1, j = y1;
             is_y1_greater ? j >= y2 : j <= y2;
             i += is_x1_greater ? -1 : 1, j += is_y1_greater ? -1 : 1) {
            f[j][i]++;
        }
    }
}

int main() {
    ifstream fin("5.in");
    string line;

    field_t f;
    for (auto& row : f) {
        for (auto& e : row) {
            e = 0;
        }
    }

    while (getline(fin, line)) {
        int x1;
        int y1;
        int x2;
        int y2;

        istringstream istream(line);

        istream >> x1;
        remove_substr(istream, ",");
        istream >> y1;

        remove_substr(istream, " -> ");

        istream >> x2;
        remove_substr(istream, ",");
        istream >> y2;

        add_cloud(f, x1, x2, y1, y2);
    }

    int ans = 0;
    for (int i = 0; i < f.size(); i++) {
        for (int j = 0; j < f.size(); j++) {
            cout << f[i][j];
            if (f[i][j] > 1) {
                ans++;
            }
        }
        cout << endl;
    }

    cout << ans << endl;

    return 0;
}