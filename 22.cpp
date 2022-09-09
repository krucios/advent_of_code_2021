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
#include <list>

using namespace std;

void self_test();

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

struct Cuboid {
    int x1;
    int x2;
    int y1;
    int y2;
    int z1;
    int z2;

    bool is_on;

    void print() {
        cout << (is_on ? "on" : "off")
             << " x=" << x1 << ".." << x2
             << ",y=" << y1 << ".." << y2
             << ",z=" << z1 << ".." << z2 << endl;
    }

    uint64_t volume() {
        return (1ULL + x2 - x1) * (1ULL + y2 - y1) * (1ULL + z2 - z1);
    }
};

bool contains(Cuboid c1, Cuboid c2) {
    return c1.x1 <= c2.x1 && c1.x2 >= c2.x2 && c1.y1 <= c2.y1 && c1.y2 >= c2.y2 && c1.z1 <= c2.z1 && c1.z2 >= c2.z2;
}

bool overlaps(Cuboid c1, Cuboid c2) {
    bool x_overlap = (c1.x1 <= c2.x1 && c2.x1 <= c1.x2) || (c2.x1 <= c1.x1 && c1.x1 <= c2.x2);
    bool y_overlap = (c1.y1 <= c2.y1 && c2.y1 <= c1.y2) || (c2.y1 <= c1.y1 && c1.y1 <= c2.y2);
    bool z_overlap = (c1.z1 <= c2.z1 && c2.z1 <= c1.z2) || (c2.z1 <= c1.z1 && c1.z1 <= c2.z2);

    return x_overlap && y_overlap && z_overlap;
}

list<Cuboid> exclusive_cuboids(Cuboid base, Cuboid exclude) {
    bool x_contains = (base.x1 <= exclude.x1 && exclude.x2 <= base.x2) || (exclude.x1 <= base.x1 && base.x2 <= exclude.x2);
    bool y_contains = (base.y1 <= exclude.y1 && exclude.y2 <= base.y2) || (exclude.y1 <= base.y1 && base.y2 <= exclude.y2);
    bool z_contains = (base.z1 <= exclude.z1 && exclude.z2 <= base.z2) || (exclude.z1 <= base.z1 && base.z2 <= exclude.z2);

    bool x_full_contains = exclude.x1 <= base.x1 && base.x2 <= exclude.x2;
    bool y_full_contains = exclude.y1 <= base.y1 && base.y2 <= exclude.y2;
    bool z_full_contains = exclude.z1 <= base.z1 && base.z2 <= exclude.z2;

    // Count how many corners intersect
    int corner_count = pow(2, static_cast<int>(x_contains) + static_cast<int>(y_contains) + static_cast<int>(z_contains));

    list<Cuboid> l;

    bool x_ex_lower = exclude.x2 < base.x2;
    bool y_ex_lower = exclude.y2 < base.y2;
    bool z_ex_lower = exclude.z2 < base.z2;

    int x = x_ex_lower ? exclude.x2 : exclude.x1;
    int y = y_ex_lower ? exclude.y2 : exclude.y1;
    int z = z_ex_lower ? exclude.z2 : exclude.z1;

    int x_low  = x_ex_lower ? x     : x - 1;
    int x_high = x_ex_lower ? x + 1 : x    ;
    int y_low  = y_ex_lower ? y     : y - 1;
    int y_high = y_ex_lower ? y + 1 : y    ;
    int z_low  = z_ex_lower ? z     : z - 1;
    int z_high = z_ex_lower ? z + 1 : z    ;

    if (exclude.x1 < base.x1) exclude.x1 = base.x1;
    if (exclude.x2 > base.x2) exclude.x2 = base.x2;
    if (exclude.y1 < base.y1) exclude.y1 = base.y1;
    if (exclude.y2 > base.y2) exclude.y2 = base.y2;
    if (exclude.z1 < base.z1) exclude.z1 = base.z1;
    if (exclude.z2 > base.z2) exclude.z2 = base.z2;

    switch (corner_count) {
        case 1: {
            l.push_back((Cuboid){base.x1,   x_low, base.y1,   y_low, base.z1,   z_low, base.is_on});
            l.push_back((Cuboid){ x_high, base.x2, base.y1,   y_low, base.z1,   z_low, base.is_on});
            l.push_back((Cuboid){base.x1,   x_low,  y_high, base.y2, base.z1,   z_low, base.is_on});
            l.push_back((Cuboid){base.x1,   x_low, base.y1,   y_low,  z_high, base.z2, base.is_on});
            l.push_back((Cuboid){ x_high, base.x2,  y_high, base.y2, base.z1,   z_low, base.is_on});
            l.push_back((Cuboid){ x_high, base.x2, base.y1,   y_low,  z_high, base.z2, base.is_on});
            l.push_back((Cuboid){base.x1,   x_low,  y_high, base.y2,  z_high, base.z2, base.is_on});
            l.push_back((Cuboid){ x_high, base.x2,  y_high, base.y2,  z_high, base.z2, base.is_on});
            break;
        }
        case 2: {
            if (x_contains) {
                l.push_back((Cuboid){exclude.x1, exclude.x2, base.y1,   y_low, base.z1,   z_low, base.is_on});
                l.push_back((Cuboid){exclude.x1, exclude.x2,  y_high, base.y2, base.z1,   z_low, base.is_on});
                l.push_back((Cuboid){exclude.x1, exclude.x2, base.y1,   y_low,  z_high, base.z2, base.is_on});
                l.push_back((Cuboid){exclude.x1, exclude.x2,  y_high, base.y2,  z_high, base.z2, base.is_on});

                if (exclude.x1 > base.x1) {
                    l.push_back((Cuboid){       base.x1, exclude.x1 - 1, base.y1, base.y2, base.z1, base.z2, base.is_on});
                }
                if (exclude.x2 < base.x2) {
                    l.push_back((Cuboid){exclude.x2 + 1,        base.x2, base.y1, base.y2, base.z1, base.z2, base.is_on});
                }
            } else if (y_contains) {
                l.push_back((Cuboid){base.x1,   x_low, exclude.y1, exclude.y2, base.z1,   z_low, base.is_on});
                l.push_back((Cuboid){ x_high, base.x2, exclude.y1, exclude.y2, base.z1,   z_low, base.is_on});
                l.push_back((Cuboid){base.x1,   x_low, exclude.y1, exclude.y2,  z_high, base.z2, base.is_on});
                l.push_back((Cuboid){ x_high, base.x2, exclude.y1, exclude.y2,  z_high, base.z2, base.is_on});

                if (exclude.y1 > base.y1) {
                    l.push_back((Cuboid){base.x1, base.x2,        base.y1, exclude.y1 - 1, base.z1, base.z2, base.is_on});
                }
                if (exclude.y2 < base.y2) {
                    l.push_back((Cuboid){base.x1, base.x2, exclude.y2 + 1,        base.y2, base.z1, base.z2, base.is_on});
                }
            } else if (z_contains) {
                l.push_back((Cuboid){base.x1,   x_low, base.y1,   y_low, exclude.z1, exclude.z2, base.is_on});
                l.push_back((Cuboid){ x_high, base.x2, base.y1,   y_low, exclude.z1, exclude.z2, base.is_on});
                l.push_back((Cuboid){base.x1,   x_low,  y_high, base.y2, exclude.z1, exclude.z2, base.is_on});
                l.push_back((Cuboid){ x_high, base.x2,  y_high, base.y2, exclude.z1, exclude.z2, base.is_on});

                if (exclude.z1 > base.z1) {
                    l.push_back((Cuboid){base.x1, base.x2, base.y1, base.y2,        base.z1, exclude.z1 - 1, base.is_on});
                }
                if (exclude.z2 < base.z2) {
                    l.push_back((Cuboid){base.x1, base.x2, base.y1, base.y2, exclude.z2 + 1,        base.z2, base.is_on});
                }
            } else {
                cout << "ERROR: unexpected case with 2 corner overlap" << endl;
            }

            break;
        }
        case 4: {
            if (x_contains && y_contains) {
                l.push_back((Cuboid){exclude.x1, exclude.x2, exclude.y1, exclude.y2, base.z1,   z_low, base.is_on});
                l.push_back((Cuboid){exclude.x1, exclude.x2, exclude.y1, exclude.y2,  z_high, base.z2, base.is_on});

                if (exclude.x1 > base.x1) {
                    l.push_back((Cuboid){       base.x1, exclude.x1 - 1, base.y1, base.y2, base.z1, base.z2, base.is_on});
                }
                if (exclude.x2 < base.x2) {
                    l.push_back((Cuboid){exclude.x2 + 1,        base.x2, base.y1, base.y2, base.z1, base.z2, base.is_on});
                }
                if (exclude.y1 > base.y1) {
                    l.push_back((Cuboid){exclude.x1, exclude.x2,        base.y1, exclude.y1 - 1, base.z1, base.z2, base.is_on});
                }
                if (exclude.y2 < base.y2) {
                    l.push_back((Cuboid){exclude.x1, exclude.x2, exclude.y2 + 1,        base.y2, base.z1, base.z2, base.is_on});
                }
            } else if (x_contains && z_contains) {
                l.push_back((Cuboid){exclude.x1, exclude.x2, base.y1,   y_low, exclude.z1, exclude.z2, base.is_on});
                l.push_back((Cuboid){exclude.x1, exclude.x2,  y_high, base.y2, exclude.z1, exclude.z2, base.is_on});

                if (exclude.x1 > base.x1) {
                    l.push_back((Cuboid){       base.x1, exclude.x1 - 1, base.y1, base.y2, base.z1, base.z2, base.is_on});
                }
                if (exclude.x2 < base.x2) {
                    l.push_back((Cuboid){exclude.x2 + 1,        base.x2, base.y1, base.y2, base.z1, base.z2, base.is_on});
                }
                if (exclude.z1 > base.z1) {
                    l.push_back((Cuboid){exclude.x1, exclude.x2, base.y1, base.y2,        base.z1, exclude.z1 - 1, base.is_on});
                }
                if (exclude.z2 < base.z2) {
                    l.push_back((Cuboid){exclude.x1, exclude.x2, base.y1, base.y2, exclude.z2 + 1,        base.z2, base.is_on});
                }
            } else if (y_contains && z_contains) {
                l.push_back((Cuboid){base.x1,   x_low, exclude.y1, exclude.y2, exclude.z1, exclude.z2, base.is_on});
                l.push_back((Cuboid){ x_high, base.x2, exclude.y1, exclude.y2, exclude.z1, exclude.z2, base.is_on});

                if (exclude.y1 > base.y1) {
                    l.push_back((Cuboid){base.x1, base.x2,        base.y1, exclude.y1 - 1, base.z1, base.z2, base.is_on});
                }
                if (exclude.y2 < base.y2) {
                    l.push_back((Cuboid){base.x1, base.x2, exclude.y2 + 1,        base.y2, base.z1, base.z2, base.is_on});
                }
                if (exclude.z1 > base.z1) {
                    l.push_back((Cuboid){base.x1, base.x2, exclude.y1, exclude.y2,        base.z1, exclude.z1 - 1, base.is_on});
                }
                if (exclude.z2 < base.z2) {
                    l.push_back((Cuboid){base.x1, base.x2, exclude.y1, exclude.y2, exclude.z2 + 1,        base.z2, base.is_on});
                }
            } else {
                cout << "ERROR: unexpected case with 4 corner overlap" << endl;
            }
            break;
        }
        case 8: {
            l.push_back((Cuboid){exclude.x1, exclude.x2, exclude.y1, exclude.y2, exclude.z1, exclude.z2, base.is_on});

            if (exclude.x1 > base.x1) {
                l.push_back((Cuboid){       base.x1, exclude.x1 - 1, base.y1, base.y2, base.z1, base.z2, base.is_on});
            }
            if (exclude.x2 < base.x2) {
                l.push_back((Cuboid){exclude.x2 + 1,        base.x2, base.y1, base.y2, base.z1, base.z2, base.is_on});
            }
            if (exclude.y1 > base.y1) {
                l.push_back((Cuboid){exclude.x1, exclude.x2,        base.y1, exclude.y1 - 1, base.z1, base.z2, base.is_on});
            }
            if (exclude.y2 < base.y2) {
                l.push_back((Cuboid){exclude.x1, exclude.x2, exclude.y2 + 1,        base.y2, base.z1, base.z2, base.is_on});
            }
            if (exclude.z1 > base.z1) {
                l.push_back((Cuboid){exclude.x1, exclude.x2, exclude.y1, exclude.y2,        base.z1, exclude.z1 - 1, base.is_on});
            }
            if (exclude.z2 < base.z2) {
                l.push_back((Cuboid){exclude.x1, exclude.x2, exclude.y1, exclude.y2, exclude.z2 + 1,        base.z2, base.is_on});
            }
            break;
        }
        default:
            cout << "ERROR: Unexpected corner count: " << corner_count << endl;
    }

    int remove_count = 0;
    for (list<Cuboid>::iterator i = l.begin(); i != l.end(); i++) {
        if (contains(exclude, *i)) {
            i = l.erase(i);
            remove_count++;
        }
    }

    if (remove_count != 1) {
        cout << "ERROR: expect only one sub-cuboid to remove, but got " << remove_count << endl;
    }

    return l;
}

int main() {
    ifstream fin("22.in");
    string line;

    self_test();

    list<Cuboid> l;
    while (getline(fin, line)) {
        istringstream istream(line);

        string on_str;
        Cuboid cur;

        istream >> on_str;

        cur.is_on = on_str == "on";

        remove_substr(istream, " x=");
        istream >> cur.x1;
        remove_substr(istream, "..");
        istream >> cur.x2;
        remove_substr(istream, ",y=");
        istream >> cur.y1;
        remove_substr(istream, "..");
        istream >> cur.y2;
        remove_substr(istream, ",z=");
        istream >> cur.z1;
        remove_substr(istream, "..");
        istream >> cur.z2;

        cur.print();

        queue<Cuboid> q;
        q.push(cur);

        while (!q.empty()) {
            Cuboid c = q.front();
            q.pop();

            bool add_cur = c.is_on;
            bool add_li  = true;

            cout << "List size: " << l.size() << ", Queue size: " << q.size() << endl;

            list<Cuboid> new_l;
            bool stop_checking = false;
            for (list<Cuboid>::iterator i = l.begin(); i != l.end(); i++) {
                bool add_li  = true;

                if (!stop_checking) {
                    if (contains(c, *i)) {
                        add_li = false;
                    } else if (overlaps(c, *i)) {
                        if (c.is_on) {
                            if (contains(*i, c)) {
                                add_cur = false;
                                stop_checking = true;
                            } else {
                                auto new_cuboids = exclusive_cuboids(c, *i);

                                for (auto& e : new_cuboids) {
                                    q.push(e);
                                }

                                add_cur = false;
                                stop_checking = true;
                            }
                        } else {
                            auto new_cuboids = exclusive_cuboids(*i, c);

                            add_li = false;
                            for (auto& e : new_cuboids) {
                                new_l.push_back(e);
                            }
                        }
                    }
                }

                if (add_li) {
                    new_l.push_back(*i);
                }
            }

            if (add_cur) {
                new_l.push_back(c);
            }

            l.swap(new_l);
        }
    }

    cout << "Output:" << endl;
    uint64_t total = 0;
    for (auto& c : l) {
        cout << "Volume " << c.volume() << " ";
        c.print();

        total += c.volume();
    }

    cout << total << endl;

    return 0;
}

void self_test() {
    Cuboid a, b;

    cout << "Self testing: contains" << endl;
    a = {-1, 5, 1, 5, 1, 4, false};
    b = {1, 4, 1, 4, 1, 4, false};
    cout << ((contains(a, b) == true) ? "PASS" : "FAIL") << endl;

    a = {0, 5, 0, 5, 0, 5, false};
    b = {0, 5, 0, 5, 0, 5, false};
    cout << ((contains(a, b) == true) ? "PASS" : "FAIL") << endl;

    a = {1, 3, 0, 5, 0, 5, false};
    b = {0, 5, 0, 5, 0, 5, false};
    cout << ((contains(a, b) == false) ? "PASS" : "FAIL") << endl;

    a = {1, 3, 1, 2, -1, 2, false};
    b = {7, 8, 7, 8, 7, 8, false};
    cout << ((contains(a, b) == false) ? "PASS" : "FAIL") << endl;

    cout << "Self testing: overlaps" << endl;
    a = {-1, 5, 1, 5, 1, 4, false};
    b = {1, 4, 1, 4, 1, 4, false};
    cout << ((overlaps(a, b) == true) ? "PASS" : "FAIL") << endl;

    a = {0, 5, 0, 5, 0, 5, false};
    b = {0, 5, 0, 5, 0, 5, false};
    cout << ((overlaps(a, b) == true) ? "PASS" : "FAIL") << endl;

    a = {1, 3, 0, 5, 0, 5, false};
    b = {0, 5, 0, 5, 0, 5, false};
    cout << ((overlaps(a, b) == true) ? "PASS" : "FAIL") << endl;

    a = {1, 3, 1, 2, -1, 2, false};
    b = {7, 8, 7, 8, 7, 8, false};
    cout << ((overlaps(a, b) == false) ? "PASS" : "FAIL") << endl;

    a = {1, 2, 1, 2, 1, 2, false};
    b = {1, 2, 1, 2, 7, 8, false};
    cout << ((overlaps(a, b) == false) ? "PASS" : "FAIL") << endl;

    a = {0, 9, 0, 1, 4, 5, false};
    b = {4, 5, 0, 1, 0, 9, false};
    cout << ((overlaps(a, b) == true) ? "PASS" : "FAIL") << endl;
}