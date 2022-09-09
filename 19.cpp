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
#include <set>
#include <map>

using namespace std;

void remove_substr(istream& ss, const char* substr) {
    for (int i = 0; i < strlen(substr); i++) {
        if (ss.peek() == substr[i]) {
            ss.ignore();
        }
    }
}

struct Point {
    int x;
    int y;
    int z;

    Point() : x(0), y(0), z(0) {};
    Point(int x, int y, int z) : x(x), y(y), z(z) {};
    Point(const Point& o) : x(o.x), y(o.y), z(o.z) {};
    Point& operator=(const Point& o) { x = o.x; y = o.y; z = o.z; return *this; };

    Point operator*(const Point& o) const {
        Point ret;

        ret.x = x * o.x;
        ret.y = y * o.y;
        ret.z = z * o.z;
        
        return ret;
    };

    Point operator-(const Point& o) const {
        Point ret;

        ret.x = x - o.x;
        ret.y = y - o.y;
        ret.z = z - o.z;

        return ret;
    }

    bool operator==(const Point& o) const {
        return (x == o.x) && (y == o.y) && (z == o.z);
    }

    bool operator<(const Point& o) const {
        return (x < o.x) || (x == o.x && y < o.y) || (x == o.x && y == o.y && z < o.z);
    }

    size_t distance(const Point& to) const {
        return (x - to.x) * (x - to.x)
             + (y - to.y) * (y - to.y)
             + (z - to.z) * (z - to.z);
    }

    size_t taxicab_distance(const Point& to) const {
        return abs(x - to.x) + abs(y - to.y) + abs(z - to.z);
    }
};

struct Scanner {
    bool solved;
    Point pos;
    vector<Point> beacons;
    set<size_t> beacon_hash;
};

Point translate(const Point& p, int i) {
    Point r;

    switch (i) {
        case  0: r.x =  p.x; r.y =  p.y; r.z =  p.z; break;
        case  1: r.x =  p.x; r.y =  p.z; r.z = -p.y; break;
        case  2: r.x =  p.x; r.y = -p.y; r.z = -p.z; break;
        case  3: r.x =  p.x; r.y = -p.z; r.z =  p.y; break;

        case  4: r.x = -p.x; r.y = -p.y; r.z =  p.z; break;
        case  5: r.x = -p.x; r.y =  p.z; r.z =  p.y; break;
        case  6: r.x = -p.x; r.y =  p.y; r.z = -p.z; break;
        case  7: r.x = -p.x; r.y = -p.z; r.z = -p.y; break;

        case  8: r.x =  p.y; r.y = -p.x; r.z =  p.z; break;
        case  9: r.x =  p.y; r.y =  p.z; r.z =  p.x; break;
        case 10: r.x =  p.y; r.y =  p.x; r.z = -p.z; break;
        case 11: r.x =  p.y; r.y = -p.z; r.z = -p.x; break;

        case 12: r.x = -p.y; r.y =  p.x; r.z =  p.z; break;
        case 13: r.x = -p.y; r.y =  p.z; r.z = -p.x; break;
        case 14: r.x = -p.y; r.y = -p.x; r.z = -p.z; break;
        case 15: r.x = -p.y; r.y = -p.z; r.z =  p.x; break;

        case 16: r.x =  p.z; r.y = -p.x; r.z = -p.y; break;
        case 17: r.x =  p.z; r.y = -p.y; r.z =  p.x; break;
        case 18: r.x =  p.z; r.y =  p.x; r.z =  p.y; break;
        case 19: r.x =  p.z; r.y =  p.y; r.z = -p.x; break;

        case 20: r.x = -p.z; r.y = -p.x; r.z =  p.y; break;
        case 21: r.x = -p.z; r.y =  p.y; r.z =  p.x; break;
        case 22: r.x = -p.z; r.y =  p.x; r.z = -p.y; break;
        case 23: r.x = -p.z; r.y = -p.y; r.z = -p.x; break;
    }

    return r;
}

int main() {
    ifstream fin("19.in");
    string line;

    vector<Scanner> scanners;
    Scanner* cur_scanner;

    while (getline(fin, line)) {
        istringstream ss(line);

        if (line != "") {
            if (line[0] == '-' && line[1] == '-') {
                cur_scanner = new Scanner();
            } else {
                int x, y, z;

                ss >> x;
                remove_substr(ss, ",");
                ss >> y;
                remove_substr(ss, ",");
                ss >> z;

                cur_scanner->beacons.emplace_back(x, y, z);
            }
        } else {
            scanners.push_back(*cur_scanner);
        }
    }

    for (size_t i = 0; i < scanners.size(); i++) {
        cout << "--- Scanner " << i << " ---" << endl;
        for (const auto& p : scanners[i].beacons) {
            cout << p.x << "," << p.y << "," << p.z << endl;
        }
        cout << endl;
    }


    for (size_t s = 0; s < scanners.size(); s++) {
        for (size_t i = 0; i < scanners[s].beacons.size() - 1; i++) {
            for (size_t j = i + 1; j < scanners[s].beacons.size(); j++) {
                scanners[s].beacon_hash.insert(scanners[s].beacons[i].distance(scanners[s].beacons[j]));
            }
        }
    }

    scanners[0].solved = true;

    while (!all_of(scanners.begin(), scanners.end(), [](const Scanner& s){ return s.solved; })) {
        for (size_t i = 0; i < scanners.size(); i++) {
            if (!scanners[i].solved) continue;

            for (size_t j = 0; j < scanners.size(); j++) {
                if (i == j || scanners[j].solved) continue;

                vector<size_t> v;
                set_intersection(scanners[i].beacon_hash.begin(), scanners[i].beacon_hash.end(),
                                scanners[j].beacon_hash.begin(), scanners[j].beacon_hash.end(),
                                back_inserter(v));

                cout << "Between " << i << " and " << j << " : " << v.size() << endl;

                if (v.size() >= 66) {
                    bool trans_found = false;

                    for (size_t trans = 0; trans < 24 && !trans_found; trans++) {
                        vector<Point> beacons;

                        for (const auto& b : scanners[j].beacons) {
                            beacons.push_back(translate(b, trans));
                        }

                        map<Point, size_t> m;

                        for (const auto& b1 : scanners[i].beacons) {
                            for (const auto& b2 : beacons) {
                                Point diff = b2 - b1;
                                m[diff]++;
                            }
                        }

                        for (const auto& [key, val] : m) {
                            if (val >= 12) {
                                trans_found = true;

                                scanners[j].solved = true;
                                scanners[j].beacons.clear();
                                scanners[j].pos = key;

                                for (const auto& b : beacons) {
                                    scanners[j].beacons.push_back(b - key);
                                }

                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    set<Point> unique_beacons;

    for (const auto& s : scanners) {
        for (const auto& b : s.beacons) {
            unique_beacons.insert(b);
        }
    }

    cout << unique_beacons.size() << endl;

    size_t max_distance = 0;
    for (size_t i = 0; i < scanners.size() - 1; i++) {
        for (size_t j = i + 1; j < scanners.size(); j++) {
            size_t distance = scanners[i].pos.taxicab_distance(scanners[j].pos);

            if (distance > max_distance) {
                max_distance = distance;
            }
        }
    }

    cout << max_distance << endl;

    return 0;
}