#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <cassert>
#include <string>
#include <map>

using namespace std;

enum Color {NoColor=0, R=1, Y=2, B=4, O=R|Y, G=Y|B, V=B|R};

template<class K, class V> K max_key(const map<K, V> &m) {
    return (*max_element(m.begin(), m.end(),
        [](const pair<K, V> &a, const pair<K, V> &b) { return a.second < b.second; }
    )).first;
}

struct Case {    
    int total;
    map<Color, int> totals;
    map<Color, char> letters = {{R, 'R'}, {O, 'O'}, {Y, 'Y'}, {G, 'G'}, {B, 'B'}, {V, 'V'}};

    void read(istream &f) {
        f >> total;
        for(Color c : {R, O, Y, G, B, V}) {
            int x;
            f >> x;
            totals[c] = x;
        }
    }

    string toStr(vector<Color> stables) {
        string s;
        for(Color c : stables) { s += letters[c]; }
        return s;
    }

    string solve() {
        vector<Color> stables;
        Color start = max_key(totals);
        stables.push_back(start);
        totals[start] -= 1;

        while((int)stables.size() != total) {
            Color c = next(
                stables.size(),
                stables[0],
                stables.back(),
                totals[R],
                totals[O],
                totals[Y],
                totals[G],
                totals[B],
                totals[V]
            );
            if(c == NoColor) { return "IMPOSSIBLE"; }
            totals[c] -= 1;
            if(c & stables.back()) {
                cout << letters[stables.back()] << " " << letters[c] << endl;
                assert(0);
            }
            stables.push_back(c);
        }

        return toStr(stables);
    }

    Color next(int len, Color begin, Color end, int r, int o, int y, int g, int b, int v) {
        if(r < g || Y < v || b < o ||
            r + y < b || b + y < r || b + r < y) {
                return NoColor;
        }

        assert(r+o+y+g+b+v == total - len);
        if(len + 1 == total) {
            if(r == 1 && !(end & R) && !(begin & R)) { return R; }
            if(o == 1 && !(end & O) && !(begin & O)) { return O; }
            if(y == 1 && !(end & Y) && !(begin & Y)) { return Y; }
            if(g == 1 && !(end & G) && !(begin & G)) { return G; }
            if(b == 1 && !(end & B) && !(begin & B)) { return B; }
            if(v == 1 && !(end & V) && !(begin & V)) { return V; }
        } else {
            switch (end) {
                case R:
                    if(g > 0) { return G; }
                    else {
                        if(b > y) {
                            if(b > 0 && next(len+1, begin, B, r, o, y, g, b-1, v) != NoColor) { return B; }
                            else if(y > 0 && next(len+1, begin, Y, r, o, y-1, g, b, v) != NoColor) { return Y; }
                        } else {
                            if(y > 0 && next(len+1, begin, Y, r, o, y-1, g, b, v) != NoColor) { return Y; }
                            else if(b > 0 && next(len+1, begin, B, r, o, y, g, b-1, v) != NoColor) { return B; }
                        }
                    }
                    break;
                case Y:
                    if(v > 0) { return V; }
                    else {
                        if(b > r) {
                            if(b > 0 && next(len+1, begin, B, r, o, y, g, b-1, v) != NoColor) { return B; }
                            else if(r > 0 && next(len+1, begin, R, r-1, o, y, g, b, v) != NoColor) { return R; }
                        } else {    
                            if(r > 0 && next(len+1, begin, R, r-1, o, y, g, b, v) != NoColor) { return R; }
                            else if(b > 0 && next(len+1, begin, B, r, o, y, g, b-1, v) != NoColor) { return B; }
                        }
                    }
                    break;  
                case B:
                    if(o > 0) { return O; }
                    else if(y > 0 && next(len+1, begin, Y, r, o, y-1, g, b, v) != NoColor) { return Y; }
                    else if(r > 0 && next(len+1, begin, R, r-1, o, y, g, b, v) != NoColor) { return R; }
                    break; 
                case O: if(b > 0) { return B; } break;
                case G: if(r > 0) { return R; } break;
                case V: if(y > 0) { return Y; } break;
                case NoColor: break;
            }
        }
        return NoColor;
    }
};


int main(int argc, char* argv[]) {
    string ifname (argc == 2 ? argv[1] : "B-test.in");
    string ofname (ifname);

    assert(ifname.find(".in") == ifname.size() - 3);
    // replace *.in to *.out:
    ofname.replace(ofname.size() - 3, 3, ".out");

    ifstream ifs(ifname.c_str());
    ifs.exceptions(ios::failbit | ios::badbit);
    assert(ifs.is_open());

    ofstream ofs(ofname.c_str());
    assert(ofs.is_open());

    int n;
    ifs >> n;

    string buf;
    getline(ifs, buf);
    for(int i=0; i<n; i++){
        Case c;
        c.read(ifs);
        ofs << "Case #" << (i+1) << ": ";
        cout << "Case #" << (i+1) << ": " << "total=" << c.total << endl;
        ofs << c.solve();
        ofs << endl;
    }
      
    return 0;
}