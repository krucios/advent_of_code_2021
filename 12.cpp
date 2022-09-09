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

typedef map<string, set<string>> map_t;
typedef map<string, bool> visited_t;

bool is_multivisit(string s) {
    bool ans = true;

    ans &= s != "start";
    ans &= s != "end";

    for (const auto& c : s) {
        ans &= !islower(c);
    }

    return ans;
}

size_t find_paths(string v, map_t& E, visited_t visited, bool second_visit) {
    size_t ans = 0;

    if (v == "end") {
        return 1;
    }

    if (!is_multivisit(v)) {
        visited[v] = true;
    }

    for (const auto& adj : E[v]) {
        if (!visited[adj]) {
            ans += find_paths(adj, E, visited, second_visit);
        } else if (second_visit && adj != "start") {
            ans += find_paths(adj, E, visited, false);
        }
    }

    return ans;
}

int main() {
    ifstream fin("12.in");
    string line;

    map_t E;
    visited_t visited;

    while (getline(fin, line)) {
        string a;
        string b;

        size_t pos = line.find("-");
        a = line.substr(0, pos);
        line.erase(0, pos + 1);
        b = line;

        E[a].insert(b);
        E[b].insert(a);

        visited[a] = false;
        visited[b] = false;
    }

    for (auto& [key, value] : E) {
        cout << key << " : ";
        for (auto& v : value) {
            cout << v << " ";
        }
        cout << endl;
    }

    cout << find_paths("start", E, visited, true) << endl;

    return 0;
}