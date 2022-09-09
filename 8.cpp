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

int main() {
    ifstream fin("8.in");
    string line;

    int total = 0;
    while (getline(fin, line)) {
        vector<string> terms;
        vector<string> puzzle;

        istringstream istream(line);

        bool is_puzzle_string = false;

        while (!istream.eof()) {
            string term;

            istream >> term;

            if (term == "|") {
                is_puzzle_string = true;
            } else {
                if (is_puzzle_string) {
                    puzzle.push_back(term);
                } else {
                    terms.push_back(term);
                }
            }
        }

        // cout << "Terms: ";
        // for (auto& t : terms) cout << t << " ";
        // cout << endl;

        // cout << "Puzzle: ";
        // for (auto& p : puzzle) cout << p << " ";
        // cout << endl;

        array<array<bool, 7>, 7> m;
        for (auto& r : m) {
            for (auto& c : r) {
                c = true;
            }
        }

        for (auto& t : terms) {
            switch (t.length()) {
            case 2: {
                size_t pos_1 = t[0] - 'a';
                size_t pos_2 = t[1] - 'a';

                for (size_t i = 0; i < 7; i++) {
                    if (i != pos_1 && i != pos_2) {
                        m[2][i] = false;
                        m[5][i] = false;
                    }
                }
                break;
            }
            case 3: {
                size_t pos_1 = t[0] - 'a';
                size_t pos_2 = t[1] - 'a';
                size_t pos_3 = t[2] - 'a';

                for (size_t i = 0; i < 7; i++) {
                    if (i != pos_1 && i != pos_2 && i != pos_3) {
                        m[0][i] = false;
                        m[2][i] = false;
                        m[5][i] = false;
                    }
                }
                break;
            }
            case 4: {
                size_t pos_1 = t[0] - 'a';
                size_t pos_2 = t[1] - 'a';
                size_t pos_3 = t[2] - 'a';
                size_t pos_4 = t[3] - 'a';

                for (size_t i = 0; i < 7; i++) {
                    if (i != pos_1 && i != pos_2 && i != pos_3 && i != pos_4) {
                        m[1][i] = false;
                        m[2][i] = false;
                        m[3][i] = false;
                        m[5][i] = false;
                    }
                }
                break;
            }
            case 5: {
                size_t pos_1 = t[0] - 'a';
                size_t pos_2 = t[1] - 'a';
                size_t pos_3 = t[2] - 'a';
                size_t pos_4 = t[3] - 'a';
                size_t pos_5 = t[4] - 'a';

                for (size_t i = 0; i < 7; i++) {
                    if (i != pos_1 && i != pos_2 && i != pos_3 && i != pos_4 && i != pos_5) {
                        m[0][i] = false;
                        m[3][i] = false;
                        m[6][i] = false;
                    }
                }
                break;
            }
            case 6: {
                size_t pos_1 = t[0] - 'a';
                size_t pos_2 = t[1] - 'a';
                size_t pos_3 = t[2] - 'a';
                size_t pos_4 = t[3] - 'a';
                size_t pos_5 = t[4] - 'a';
                size_t pos_6 = t[5] - 'a';

                for (size_t i = 0; i < 7; i++) {
                    if (i != pos_1 && i != pos_2 && i != pos_3 && i != pos_4 && i != pos_5 && i != pos_6) {
                        m[0][i] = false;
                        m[1][i] = false;
                        m[5][i] = false;
                        m[6][i] = false;
                    }
                }
                break;
            }
            default:
                break;
            }
        }

        for (size_t repeat = 0; repeat < 7; repeat++) {
            for (size_t i = 0; i < 7; i++) {
                if (std::count(m[i].cbegin(), m[i].cend(), true) == 1) {
                    size_t pos = 0;
                    for (size_t j = 0; j < 7; j++) {
                        if (m[i][j] == true) {
                            pos = j;
                            break;
                        }
                    }

                    for (size_t j = 0; j < 7; j++) {
                        if (i != j) {
                            m[j][pos] = false;
                        }
                    }
                }
            }
        }

        cout << "Matrix:" << endl;
        for (size_t i = 0; i < 7; i++) {
            cout << "[" << (char)('a' + i) << "]";
        }
        cout << endl;
        cout << "---------------------" << endl;

        for (size_t i = 0; i < 7; i++) {
            for (size_t j = 0; j < 7; j++) {
                cout << " " << m[j][i] << " ";
            }
            cout << endl;
        }

        size_t number = 0;
        for (size_t i = 0; i < 4; i++) {
            size_t mask = 0;

            for (auto& c : puzzle[i]) {
                size_t pos = c - 'a';

                for (size_t j = 0; j < 7; j++) {
                    if (m[j][pos] == true) {
                        mask |= 1 << j;
                        break;
                    }
                }
            }

            size_t digit;
            switch (mask) {
                case 0b1110111:
                    digit = 0;
                    break;
                case 0b0100100:
                    digit = 1;
                    break;
                case 0b1011101:
                    digit = 2;
                    break;
                case 0b1101101:
                    digit = 3;
                    break;
                case 0b0101110:
                    digit = 4;
                    break;
                case 0b1101011:
                    digit = 5;
                    break;
                case 0b1111011:
                    digit = 6;
                    break;
                case 0b0100101:
                    digit = 7;
                    break;
                case 0b1111111:
                    digit = 8;
                    break;
                case 0b1101111:
                    digit = 9;
                    break;
            }

            number += digit * (int)(pow(10, 3 - i));
        }

        cout << number << endl;
        total += number;
    }

    cout << "Answer: " << total << endl;

    return 0;
}