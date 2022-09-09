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
#include <stack>
#include <list>

using namespace std;

static const size_t SPACE_COUNT = 15;

struct game_state {
    uint64_t cost;
    array<int, 8> pos; // i / 2 is amp type
};

/*
#############
#01.2.3.4.56#
###7#9#B#D###
  #8#A#C#E#
  #########
*/
static const int E[SPACE_COUNT][SPACE_COUNT] = {
  // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
    {1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0}, // 1
    {0, 2, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0}, // 2
    {0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0}, // 3
    {0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0}, // 4
    {0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0}, // 5
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
    {0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // 7
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 9
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 10
    {0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // 11
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // 12
    {0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 13
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}  // 14
};

static const int D[SPACE_COUNT][SPACE_COUNT] = {
  // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
   { 0, 1, 3, 5, 7, 9,10, 3, 4, 5, 6, 7, 8, 9,10}, // 0
   { 1, 0, 2, 4, 6, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9}, // 1
   { 3, 2, 0, 2, 4, 6, 7, 2, 3, 2, 3, 4, 5, 6, 7}, // 2
   { 5, 4, 2, 0, 2, 4, 5, 4, 5, 2, 3, 2, 3, 4, 5}, // 3
   { 7, 6, 4, 2, 0, 2, 3, 6, 7, 4, 5, 2, 3, 2, 3}, // 4
   { 9, 8, 6, 4, 2, 0, 1, 8, 9, 6, 7, 4, 5, 2, 3}, // 5
   {10, 9, 7, 5, 3, 1, 0, 9,10, 7, 8, 5, 6, 3, 4}, // 6
   { 3, 2, 2, 4, 6, 8, 9, 0, 1, 4, 5, 6, 7, 8, 9}, // 7
   { 4, 3, 3, 5, 7, 9,10, 1, 0, 5, 6, 7, 8, 9,10}, // 8
   { 5, 4, 2, 2, 4, 6, 7, 4, 5, 0, 1, 4, 5, 6, 7}, // 9
   { 6, 5, 3, 3, 5, 7, 8, 5, 6, 1, 0, 5, 6, 7, 8}, // 10
   { 7, 6, 4, 2, 2, 4, 5, 6, 7, 4, 5, 0, 1, 4, 5}, // 11
   { 8, 7, 5, 3, 3, 5, 6, 7, 8, 5, 6, 1, 0, 5, 6}, // 12
   { 9, 8, 6, 4, 2, 2, 3, 8, 9, 6, 7, 4, 5, 0, 1}, // 13
   {10, 9, 7, 5, 3, 3, 4, 9,10, 7, 8, 5, 6, 1, 0}  // 14
};

static const int target[4][2] = {
    { 7,  8},
    { 9, 10},
    {11, 12},
    {13, 14}
};

static const int cost[4] = {
    1,
    10,
    100,
    1000
};

static array<array<vector<int>, SPACE_COUNT>, SPACE_COUNT> paths;

static int valid_pos [4][9] = {
                                {0, 1, 2, 3, 4, 5, 6,  7,  8},
                                {0, 1, 2, 3, 4, 5, 6,  9, 10},
                                {0, 1, 2, 3, 4, 5, 6, 11, 12},
                                {0, 1, 2, 3, 4, 5, 6, 13, 14}
                              };

bool is_hall(int pos) { return (0 <= pos) && (pos <= 6); }

static uint64_t min_score = 15000;

bool can_go_home(const array<int, 8>& a, int type) {
    int free_pos;
    int check_pos;

    if (type == 0) { free_pos =  7; check_pos =  8; };
    if (type == 1) { free_pos =  9; check_pos = 10; };
    if (type == 2) { free_pos = 11; check_pos = 12; };
    if (type == 3) { free_pos = 13; check_pos = 14; };

    bool ans = true;

    for (size_t i = 0; i < 8; i++) {
        if (a[i] == free_pos) return false;
        if (a[i] == check_pos && ((i / 2) != type)) return false;
    }

    return true;
}

bool has_settled(const array<int, 8>& a, int type, int pos) {
    if (type == 0) return (pos ==  8 || (pos == 7  && (a[0] ==  8 || a[1] ==  8)));
    if (type == 1) return (pos == 10 || (pos == 9  && (a[2] == 10 || a[3] == 10)));
    if (type == 2) return (pos == 12 || (pos == 11 && (a[4] == 12 || a[5] == 12)));
    if (type == 3) return (pos == 14 || (pos == 13 && (a[6] == 14 || a[7] == 14)));

    return false;
}

bool is_done(const array<int, 8>& a, int type) {
    if (type == 0) return (a[0] ==  7 && a[1] ==  8) || (a[0] ==  8 && a[1] ==  7);
    if (type == 1) return (a[2] ==  9 && a[3] == 10) || (a[2] == 10 && a[3] ==  9);
    if (type == 2) return (a[3] == 11 && a[5] == 12) || (a[4] == 12 && a[5] == 11);
    if (type == 3) return (a[5] == 13 && a[7] == 14) || (a[6] == 14 && a[7] == 13);

    return false;
}

bool is_done(const array<int, 8>& a) {
    bool ret  = is_done(a, 0);
         ret &= is_done(a, 1);
         ret &= is_done(a, 2);
         ret &= is_done(a, 3);

    return ret;
}

bool is_path_available(const game_state& g, int from, int to) {
    bool ans = true;

    for (auto p : paths[from][to]) {
        ans &= find(g.pos.begin(), g.pos.end(), p) == g.pos.end();
    }

    return ans;
}

void solve(game_state s) {
    if (s.cost > min_score) {
        return;
    }

    if (is_done(s.pos)) {
        if (s.cost < min_score) {
            min_score = s.cost;
        }
        return;
    }

    for (size_t a = 0; a < 8; a++) {
        for (size_t p = 0; p < 9; p++) {
            int type = a / 2;
            int from = s.pos[a];
            int to   = valid_pos[type][p];

            if (is_path_available(s, from, to)
                && (   (is_hall(from) && !is_hall(to) && can_go_home(s.pos, type))
                    || (is_hall(to) && !is_hall(from) && !has_settled(s.pos, type, from)))
               ) {
                game_state ns = s;

                ns.cost += cost[type] * D[from][to];
                ns.pos[a] = to;

                solve(ns);
            }
        }
    }
}

int main() {

    // Build position to check map
    {
        paths[0][1]  = {1};
        paths[0][2]  = {1, 2};
        paths[0][3]  = {1, 2, 3};
        paths[0][4]  = {1, 2, 3, 4};
        paths[0][5]  = {1, 2, 3, 4, 5};
        paths[0][6]  = {1, 2, 3, 4, 5, 6};
        paths[0][7]  = {1, 7};
        paths[0][8]  = {1, 7, 8};
        paths[0][9]  = {1, 2, 9};
        paths[0][10] = {1, 2, 9, 10};
        paths[0][11] = {1, 2, 3, 11};
        paths[0][12] = {1, 2, 3, 11, 12};
        paths[0][13] = {1, 2, 3, 4, 13};
        paths[0][14] = {1, 2, 3, 4, 13, 14};

        paths[1][0]  = {0};
        paths[1][2]  = {2};
        paths[1][3]  = {2, 3};
        paths[1][4]  = {2, 3, 4};
        paths[1][5]  = {2, 3, 4, 5};
        paths[1][6]  = {2, 3, 4, 5, 6};
        paths[1][7]  = {7};
        paths[1][8]  = {7, 8};
        paths[1][9]  = {2, 9};
        paths[1][10] = {2, 9, 10};
        paths[1][11] = {2, 3, 11};
        paths[1][12] = {2, 3, 11, 12};
        paths[1][13] = {2, 3, 4, 13};
        paths[1][14] = {2, 3, 4, 13, 14};

        paths[2][0]  = {0, 1};
        paths[2][1]  = {1};
        paths[2][3]  = {3};
        paths[2][4]  = {3, 4};
        paths[2][5]  = {3, 4, 5};
        paths[2][6]  = {3, 4, 5, 6};
        paths[2][7]  = {7};
        paths[2][8]  = {7, 8};
        paths[2][9]  = {9};
        paths[2][10] = {9, 10};
        paths[2][11] = {3, 11};
        paths[2][12] = {3, 11, 12};
        paths[2][13] = {3, 4, 13};
        paths[2][14] = {3, 4, 13, 14};

        paths[3][0]  = {0, 1, 2};
        paths[3][1]  = {1, 2};
        paths[3][2]  = {2};
        paths[3][4]  = {4};
        paths[3][5]  = {4, 5};
        paths[3][6]  = {4, 5, 6};
        paths[3][7]  = {2, 7};
        paths[3][8]  = {2, 7, 8};
        paths[3][9]  = {9};
        paths[3][10] = {9, 10};
        paths[3][11] = {11};
        paths[3][12] = {11, 12};
        paths[3][13] = {4, 13};
        paths[3][14] = {4, 13, 14};

        paths[4][0]  = {0, 1, 2, 3};
        paths[4][1]  = {1, 2, 3};
        paths[4][2]  = {2, 3};
        paths[4][3]  = {3};
        paths[4][5]  = {5};
        paths[4][6]  = {5, 6};
        paths[4][7]  = {2, 3, 7};
        paths[4][8]  = {2, 3, 7, 8};
        paths[4][9]  = {3, 9};
        paths[4][10] = {3, 9, 10};
        paths[4][11] = {11};
        paths[4][12] = {11, 12};
        paths[4][13] = {13};
        paths[4][14] = {13, 14};

        paths[5][0]  = {0, 1, 2, 3, 4};
        paths[5][1]  = {1, 2, 3, 4};
        paths[5][2]  = {2, 3, 4};
        paths[5][3]  = {3, 4};
        paths[5][4]  = {4};
        paths[5][6]  = {6};
        paths[5][7]  = {2, 3, 4, 7};
        paths[5][8]  = {2, 3, 4, 7, 8};
        paths[5][9]  = {3, 4, 9};
        paths[5][10] = {3, 4, 9, 10};
        paths[5][11] = {4, 11};
        paths[5][12] = {4, 11, 12};
        paths[5][13] = {13};
        paths[5][14] = {13, 14};

        paths[6][0]  = {0, 1, 2, 3, 4, 5};
        paths[6][1]  = {1, 2, 3, 4, 5};
        paths[6][2]  = {2, 3, 4, 5};
        paths[6][3]  = {3, 4, 5};
        paths[6][4]  = {4, 5};
        paths[6][5]  = {5};
        paths[6][7]  = {2, 3, 4, 5, 7};
        paths[6][8]  = {2, 3, 4, 5, 7, 8};
        paths[6][9]  = {3, 4, 5, 9};
        paths[6][10] = {3, 4, 5, 9, 10};
        paths[6][11] = {4, 5, 11};
        paths[6][12] = {4, 5, 11, 12};
        paths[6][13] = {5, 13};
        paths[6][14] = {5, 13, 14};

        paths[7][0]  = {0, 1};
        paths[7][1]  = {1};
        paths[7][2]  = {2};
        paths[7][3]  = {2, 3};
        paths[7][4]  = {2, 3, 4};
        paths[7][5]  = {2, 3, 4, 5};
        paths[7][6]  = {2, 3, 4, 5, 6};
        paths[7][8]  = {8};
        paths[7][9]  = {2, 9};
        paths[7][10] = {2, 9, 10};
        paths[7][11] = {2, 3, 11};
        paths[7][12] = {2, 3, 11, 12};
        paths[7][13] = {2, 3, 4, 13};
        paths[7][14] = {2, 3, 4, 13, 14};

        paths[8][0]  = {0, 1, 7};
        paths[8][1]  = {1, 7};
        paths[8][2]  = {2, 7};
        paths[8][3]  = {2, 3, 7};
        paths[8][4]  = {2, 3, 4, 7};
        paths[8][5]  = {2, 3, 4, 5, 7};
        paths[8][6]  = {2, 3, 4, 5, 6, 7};
        paths[8][7]  = {7};
        paths[8][9]  = {2, 7, 9};
        paths[8][10] = {2, 7, 9, 10};
        paths[8][11] = {2, 7, 3, 11};
        paths[8][12] = {2, 3, 7, 11, 12};
        paths[8][13] = {2, 3, 4, 7, 13};
        paths[8][14] = {2, 3, 4, 7, 13, 14};

        paths[9][0]  = {0, 1, 2};
        paths[9][1]  = {1, 2};
        paths[9][2]  = {2};
        paths[9][3]  = {3};
        paths[9][4]  = {3, 4};
        paths[9][5]  = {3, 4, 5};
        paths[9][6]  = {3, 4, 5, 6};
        paths[9][7]  = {2, 7};
        paths[9][8]  = {2, 7, 8};
        paths[9][10] = {10};
        paths[9][11] = {3, 11};
        paths[9][12] = {3, 11, 12};
        paths[9][13] = {3, 4, 13};
        paths[9][14] = {3, 4, 13, 14};

        paths[10][0]  = {0, 1, 2, 9};
        paths[10][1]  = {1, 2, 9};
        paths[10][2]  = {2, 9};
        paths[10][3]  = {3, 9};
        paths[10][4]  = {3, 4, 9};
        paths[10][5]  = {3, 4, 5, 9};
        paths[10][6]  = {3, 4, 5, 6, 9};
        paths[10][7]  = {2, 7, 9};
        paths[10][8]  = {2, 7, 8, 9};
        paths[10][10] = {9, 10};
        paths[10][11] = {3, 9, 11};
        paths[10][12] = {3, 9, 11, 12};
        paths[10][13] = {3, 4, 9, 13};
        paths[10][14] = {3, 4, 9, 13, 14};

        paths[11][0]  = {0, 1, 2, 3};
        paths[11][1]  = {1, 2, 3};
        paths[11][2]  = {2, 3};
        paths[11][3]  = {3};
        paths[11][4]  = {4};
        paths[11][5]  = {4, 5};
        paths[11][6]  = {4, 5, 6};
        paths[11][7]  = {2, 3, 7};
        paths[11][8]  = {2, 3, 7, 8};
        paths[11][9]  = {3, 9};
        paths[11][10] = {3, 9, 10};
        paths[11][12] = {12};
        paths[11][13] = {4, 13};
        paths[11][14] = {4, 13, 14};

        paths[12][0]  = {0, 1, 2, 3, 11};
        paths[12][1]  = {1, 2, 3, 11};
        paths[12][2]  = {2, 3, 11};
        paths[12][3]  = {3, 11};
        paths[12][4]  = {4, 11};
        paths[12][5]  = {4, 5, 11};
        paths[12][6]  = {4, 5, 6, 11};
        paths[12][7]  = {2, 3, 7, 11};
        paths[12][8]  = {2, 3, 7, 8, 11};
        paths[12][9]  = {3, 9, 11};
        paths[12][10] = {3, 9, 10, 11};
        paths[12][11] = {11};
        paths[12][13] = {4, 11, 13};
        paths[12][14] = {4, 11, 13, 14};

        paths[13][0]  = {0, 1, 2, 3, 4};
        paths[13][1]  = {1, 2, 3, 4};
        paths[13][2]  = {2, 3, 4};
        paths[13][3]  = {3, 4};
        paths[13][4]  = {4};
        paths[13][5]  = {5};
        paths[13][6]  = {5, 6};
        paths[13][7]  = {2, 3, 4, 7};
        paths[13][8]  = {2, 3, 4, 7, 8};
        paths[13][9]  = {3, 4, 9};
        paths[13][10] = {3, 4, 9, 10};
        paths[13][11] = {4, 11};
        paths[13][12] = {4, 11, 12};
        paths[13][14] = {14};

        paths[14][0]  = {0, 1, 2, 3, 4, 13};
        paths[14][1]  = {1, 2, 3, 4, 13};
        paths[14][2]  = {2, 3, 4, 13};
        paths[14][3]  = {3, 4, 13};
        paths[14][4]  = {4, 13};
        paths[14][5]  = {5, 13};
        paths[14][6]  = {5, 6, 13};
        paths[14][7]  = {2, 3, 4, 7, 13};
        paths[14][8]  = {2, 3, 4, 7, 8, 13};
        paths[14][9]  = {3, 4, 9, 13};
        paths[14][10] = {3, 4, 9, 10, 13};
        paths[14][11] = {4, 11, 13};
        paths[14][12] = {4, 11, 12, 13};
        paths[14][13] = {13};
    }

    for (size_t i = 0; i < SPACE_COUNT - 1; i++) {
        for (size_t j = i + 1; j < SPACE_COUNT; j++) {
            if (E[i][j] != E[j][i]) {
                cout << "ERROR: E[" << i << "][" << j << "]" << endl;
            }
        }
    }

    game_state s;
    s.cost = 0;
    s.pos = {8, 14, 7, 11, 9, 12, 10, 13};

    solve(s);

    cout << min_score << endl;

    return 0;
}
