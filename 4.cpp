#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <array>

using namespace std;

typedef array<array<int, 5>, 5> card_t;

void print_card(card_t c) {
    cout << right << setw(3);
    for (auto row : c) {
        for (auto e : row) {
            cout << right << setw(3) << e;
        }
        cout << endl;
    }
}

bool bingo_turn(int draw, card_t& c) {
    for (auto& row : c) {
        for (auto& e : row) {
            if (e == draw) {
                e = 100;
            }
        }
    }

    bool is_bingo_row = true;
    bool is_bingo_col = true;
    for (int i = 0; i < c.size(); i++) {
        for (int j = 0; j < c.size(); j++) {
            is_bingo_row &= c[i][j] == 100;
            is_bingo_col &= c[j][i] == 100;
        }

        if (is_bingo_row || is_bingo_col) {
            return true;
        }

        is_bingo_row = true;
        is_bingo_col = true;
    }
    return false;
}

int main() {
    ifstream fin("4.in");
    string line;

    vector<int> draw;
    vector<card_t> cards;

    // Read draw numbers
    getline(fin, line);
    stringstream draw_ss(line);

    for (int i; draw_ss >> i;) {
        draw.push_back(i);
        if (draw_ss.peek() == ',') {
            draw_ss.ignore();
        }
    }

    // Remove empty line
    getline(fin, line);

    // Read card content
    card_t cur_card;
    int cur_row = 0;
    while (getline(fin, line)) {
        istringstream istream(line);

        if (line == "") {
            cards.push_back(cur_card);
            continue;
        }

        for (int i = 0; i < cur_card.size(); i++) {
            int val;
            istream >> val;
            cur_card[cur_row][i] = val;
        }

        cur_row = (cur_row + 1) % cur_card.size();
    }

    for (auto d : draw) {
        for (auto& c : cards) {
            if (bingo_turn(d, c)) {
                int card_sum = 0;

                for (auto& row : c) {
                    for (auto& e : row) {
                        card_sum += (e != 100) ? e : 0;
                    }
                }

                cout << card_sum * d << endl;

                for (int i = 0; i < c.size(); i++) {
                    c[i][i] = -1;
                }
            }
        }
    }

    return 0;
}