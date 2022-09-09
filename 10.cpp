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
#include <stack>
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

int get_score(char c) {
    if (c == ')') return 3;
    if (c == ']') return 57;
    if (c == '}') return 1197;
    if (c == '>') return 25137;
}

bool is_match(char c1, char c2) {
    if ((c1 == '(' && c2 == ')')
    ||  (c1 == '[' && c2 == ']')
    ||  (c1 == '{' && c2 == '}')
    ||  (c1 == '<' && c2 == '>')
    ||  (c2 == '(' && c1 == ')')
    ||  (c2 == '[' && c1 == ']')
    ||  (c2 == '{' && c1 == '}')
    ||  (c2 == '<' && c1 == '>')) {
        return true;
    }
    return false;
}

uint64_t get_score(stack<char>& s) {
    uint64_t ans = 0;

    while (!s.empty()) {
        ans *= 5ULL;
        if (s.top() == '(') { ans += 1ULL; }
        if (s.top() == '[') { ans += 2ULL; }
        if (s.top() == '{') { ans += 3ULL; }
        if (s.top() == '<') { ans += 4ULL; }
        s.pop();
    }

    return ans;
}

int main() {
    ifstream fin("10.in");
    string l;

    int total = 0;
    int ans = 0;

    vector<uint64_t> scores;

    while (getline(fin, l)) {
        bool is_corrupted = false;
        stack<char> s;

        for (size_t i = 0; i < l.length(); i++) {
            if (l[i] == ')' || l[i] == ']' || l[i] == '}' || l[i] == '>') {
                if (s.size()) {
                    char p = s.top();

                    if (!is_match(l[i], p)) {
                        total += get_score(l[i]);
                        is_corrupted = true;
                        break;
                    }

                    s.pop();
                } else {
                    total += get_score(l[i]);
                    is_corrupted = true;
                }
            } else {
                s.push(l[i]);
            }
        }

        if (!is_corrupted && s.size()) {
            scores.push_back(get_score(s));
        }
    }

    cout << scores.size() << endl;

    for (auto& e : scores) {
        cout << e << " ";
    }
    cout << endl;

    sort(scores.begin(), scores.end());

    cout << "Answer (1): " << total << endl;
    cout << "Answer (2): " << scores[(scores.size() - 1) >> 1] << endl;

    return 0;
}