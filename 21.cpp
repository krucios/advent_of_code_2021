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

size_t roll(size_t& dice) {
    size_t ans = dice;

    dice++;
    if (dice > 100) {
        dice = 1;
    }

    return ans;
}

static const int SIZE = 50;
static const int WIN_SCORE = 21;

typedef array<array<uint64_t, 10>, 10> state_t;
typedef array<array<state_t, SIZE>, SIZE> matrix_t;

static const array<uint64_t, 7> split = {1, 3, 6, 7, 6, 3, 1};

void solve_part_1();

pair<uint64_t, uint64_t> play(uint64_t p1_score, uint64_t p2_score, uint64_t p1_pos, uint64_t p2_pos, bool p1_turn) {
    if (p1_score >= WIN_SCORE) { return make_pair(1, 0); }
    if (p2_score >= WIN_SCORE) { return make_pair(0, 1); }

    uint64_t p1_total_wins = 0;
    uint64_t p2_total_wins = 0;

    for (size_t i = 0; i < split.size(); i++) {
        if (p1_turn) {
            uint64_t p1_new_pos = ((p1_pos - 1 + i + 3) % 10) + 1;
            uint64_t p1_new_score = p1_score + p1_new_pos;
            auto p = play(p1_new_score, p2_score, p1_new_pos, p2_pos, false);
            p1_total_wins += p.first  * split[i];
            p2_total_wins += p.second * split[i];
        } else {
            uint64_t p2_new_pos = ((p2_pos - 1 + i + 3) % 10) + 1;
            uint64_t p2_new_score = p2_score + p2_new_pos;
            auto p = play(p1_score, p2_new_score, p1_pos, p2_new_pos, true);
            p1_total_wins += p.first  * split[i];
            p2_total_wins += p.second * split[i];
        }
    }

    return make_pair(p1_total_wins, p2_total_wins);
}

uint64_t game_sum(matrix_t& g, size_t r_min, size_t r_max, size_t c_min, size_t c_max) {
    uint64_t total = 0;

    for (size_t i = r_min; i < r_max; i++) {
        for (size_t j = c_min; j < c_max; j++) {
            for (size_t k = 0; k < 10; k++) {
                for (size_t l = 0; l < 10; l++) {
                    total += g[i][j][k][l];
                }
            }
        }
    }

    return total;
}

uint64_t state_sum(state_t& s) {
    uint64_t total = 0;

    for (size_t k = 0; k < 10; k++) {
        for (size_t l = 0; l < 10; l++) {
            total += s[k][l];
        }
    }

    return total;
}

int main() {
    ifstream fin("21.in");
    string line;

    // solve_part_1();

    matrix_t g;
    for (auto& r : g) for (auto& e : r) for (auto& k : e) for (auto& l : k) l = 0;

    g[0][0][8][9] = 1;

    bool p1_turn = true;
    while (game_sum(g, 0, WIN_SCORE, 0, WIN_SCORE)) {
        matrix_t new_g;
        for (auto& r : new_g) for (auto& e : r) for (auto& k : e) for (auto& l : k) l = 0;

        for (size_t i = 0; i < WIN_SCORE; i++) {
            for (size_t j = 0; j < WIN_SCORE; j++) {
                if (state_sum(g[i][j])) {
                    for (size_t s = 0; s < split.size(); s++) {
                        for (size_t k = 0; k < 10; k++) {
                            for (size_t l = 0; l < 10; l++) {
                                if (g[i][j][k][l]) {
                                    if (p1_turn) {
                                        uint64_t new_pos = ((k + s + 3) % 10) + 1;

                                        new_g[i + new_pos][j][new_pos - 1][l] += g[i][j][k][l] * split[s];
                                    } else {
                                        uint64_t new_pos = ((l + s + 3) % 10) + 1;

                                        new_g[i][j + new_pos][k][new_pos - 1] += g[i][j][k][l] * split[s];
                                    }
                                }
                            }
                        }
                    }

                    for (size_t k = 0; k < 10; k++) {
                        for (size_t l = 0; l < 10; l++) {
                            g[i][j][k][l] = 0;
                        }
                    }
                }
            }
        }

        p1_turn = !p1_turn;
        for (size_t i = 0; i < SIZE; i++) {
            for (size_t j = 0; j < SIZE; j++) {
                for (size_t k = 0; k < 10; k++) {
                    for (size_t l = 0; l < 10; l++) {
                        g[i][j][k][l] += new_g[i][j][k][l];
                    }
                }
            }
        }

        uint64_t p1_score = game_sum(g, WIN_SCORE, SIZE, 0, WIN_SCORE);
        uint64_t p2_score = game_sum(g, 0, WIN_SCORE, WIN_SCORE, SIZE);
        uint64_t self_check = game_sum(g, WIN_SCORE, SIZE, WIN_SCORE, SIZE);

        cout << "P1: " << p1_score << ",\tP2: " << p2_score << ",\tCHECK: " << self_check << endl;
    }

    uint64_t p1_score = game_sum(g, WIN_SCORE, SIZE, 0, WIN_SCORE);
    uint64_t p2_score = game_sum(g, 0, WIN_SCORE, WIN_SCORE, SIZE);
    uint64_t self_check = game_sum(g, WIN_SCORE, SIZE, WIN_SCORE, SIZE);

    if (self_check) {
        cout << "ERROR: self check failed" << endl;
    }

    cout << p1_score << endl;
    cout << p2_score << endl;

    // auto p = play(0, 0, 4, 8, true);
    // cout << p.first << " " << p.second << endl;

    return 0;
}

void solve_part_1() {
    size_t p1_pos = 9;
    size_t p2_pos = 10;

    size_t p1_score = 0;
    size_t p2_score = 0;

    size_t dice = 1;
    size_t rolls = 0;

    bool first_plays = true;

    while (p1_score < 1000 && p2_score < 1000) {
        size_t r1 = roll(dice);
        size_t r2 = roll(dice);
        size_t r3 = roll(dice);
        rolls += 3;

        size_t move = r1 + r2 + r3;

        if (first_plays) {
            p1_pos = ((p1_pos - 1 + move) % 10) + 1;
            p1_score += p1_pos;
        } else {
            p2_pos = ((p2_pos - 1 + move) % 10) + 1;
            p2_score += p2_pos;
        }

        cout << "Player " << (first_plays ? "1" : "2") << " rolls "
             << r1 << "+" << r2 << "+" << r3
             << " and moves to space " << (first_plays ? p1_pos : p2_pos)
             << " for a total score of " << (first_plays ? p1_score : p2_score) << endl;

        first_plays = !first_plays;
    }

    cout << min(p1_score, p2_score) * rolls << endl;
}