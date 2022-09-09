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

class SNode {
protected:
    bool is_simple = false;
    int val = 0;
    int level = 0;

    SNode* p = nullptr;
    SNode* l = nullptr;
    SNode* r = nullptr;

public:
    SNode(SNode* left, SNode* right, SNode* parent = nullptr) {
        is_simple = false;
        l = left;
        r = right;
        p = parent;
    }

    SNode(const string& s, SNode* parent = nullptr) {
        p = parent;

        is_simple = s.find(',') == string::npos;

        if (is_simple) {
            val = atoi(s.c_str());
        } else {
            size_t pos = 0;
            size_t depth = 0;

            for (size_t i = 0; i < s.length(); i++) {
                if (s[i] == '[') {
                    depth++;
                } else if (s[i] == ']') {
                    depth--;
                } else if (s[i] == ',' && depth == 1) {
                    pos = i;
                }
            }

            if (pos == 0) {
                cout << "ERROR: invalid comma pos found for - " << s << endl;
            }

            string left;
            string right;

            left = s.substr(1, pos - 1);
            right = s.substr(pos + 1, s.length() - pos - 2);

            // cout << left << " <-> " << right << endl;

            l = new SNode(left, this);
            r = new SNode(right, this);
        }
    };

    void setParent(SNode* parent) {
        p = parent;
    }

    void setLevel(int lvl) {
        level = lvl;

        if (!is_simple) {
            l->setLevel(lvl + 1);
            r->setLevel(lvl + 1);
        }
    }

    SNode() = delete;
    SNode(const SNode& other) = delete;
    SNode& operator=(const SNode& other) = delete;

    bool explode() {
        if (is_simple) {
            return false;
        }

        if (level < 4) {
            bool ret_code = l->explode();

            if (!ret_code) {
                ret_code = r->explode();
            }

            return ret_code;
        } else {
            if (!l->is_simple) {
                return l->explode();
            }

            if (!r->is_simple) {
                return r->explode();
            }

            SNode* cur_p;
            SNode* cur_l;

            // Explode left
            cur_p = p;
            cur_l = this;

            while (cur_p != nullptr && cur_p->l == cur_l) {
                cur_p = cur_p->p;
                cur_l = cur_l->p;
            }

            if (cur_p != nullptr) {
                cur_l = cur_p->l;

                while (!cur_l->is_simple) {
                    cur_l = cur_l->r;
                }

                cur_l->val += l->val;
            }

            // Explode right
            cur_p = p;
            cur_l = this;

            while (cur_p != nullptr && cur_p->r == cur_l) {
                cur_p = cur_p->p;
                cur_l = cur_l->p;
            }

            if (cur_p != nullptr) {
                cur_l = cur_p->r;

                while (!cur_l->is_simple) {
                    cur_l = cur_l->l;
                }

                cur_l->val += r->val;
            }

            delete l;
            delete r;

            l = nullptr;
            r = nullptr;

            is_simple = true;
            val = 0;

            return true;
        }
    }

    bool split() {
        if (!is_simple) {
            bool ret_code = l->split();

            if (!ret_code) {
                ret_code = r->split();
            }

            return ret_code;
        } else {
            if (val < 10) {
                return false;
            } else {
                is_simple = false;

                string left = to_string(floor(static_cast<float>(val) / 2));
                string right = to_string(ceil(static_cast<float>(val) / 2));

                l = new SNode(left, this);
                r = new SNode(right, this);

                this->setLevel(level);

                return true;
            }
        }
    }

    bool reduce() {
        bool ret_code = explode();

        if (!ret_code) {
            ret_code = split();
        }

        return ret_code;
    }

    size_t magnitude() {
        if (is_simple) {
            return val;
        } else {
            return 3 * l->magnitude() + 2 * r->magnitude();
        }
    }

    void print() {
        if (is_simple) {
            cout << val;
        } else {
            cout << "[";
            l->print();
            cout << ",";
            r->print();
            cout << "]";
        }
    }

    ~SNode() {
        delete l;
        delete r;
    };
};

class SNum {
private:
    SNode* root;

public:
    SNum(const string& s) {
        root = new SNode(s);
        root->setLevel(0);
    };

    SNum() = delete;
    SNum(const SNum& other) = delete;
    SNum& operator=(const SNum& other) = delete;

    void add(const string& s) {
        SNode* new_right = new SNode(s);
        SNode* new_left = root;

        root = new SNode(new_left, new_right);

        new_left->setParent(root);
        new_right->setParent(root);

        root->setLevel(0);
        while (root->reduce()) {};
    }

    size_t magnitude() {
        return root->magnitude();
    }

    void print() {
        root->print();
        cout << endl;
    }

    ~SNum() {
        delete root;
    };
};

int main() {
    ifstream fin("18.in");
    string line;

    vector<string> v;

    while (getline(fin, line)) {
        v.push_back(line);
    }

    size_t max_magnitude = 0;

    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = 0; j < v.size(); j++) {
            if (i != j) {
                SNum s(v[i]);
                s.add(v[j]);

                size_t cur_magnitude = s.magnitude();

                if (cur_magnitude > max_magnitude) {
                    max_magnitude = cur_magnitude;
                }
            }
        }
    }

    cout << max_magnitude << endl;

    return 0;
}