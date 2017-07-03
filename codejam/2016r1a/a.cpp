#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <cassert>
#include <string>

using namespace std;


struct Case {
    string s;

    void read(istream &f) {
        getline(f, s);
    }

    string solve() {
        string s2 = "";
        s2 += s[0];
        
        for(auto it=(s.begin()+1); it != s.end(); it++) {
            char c = *it;
            if(c >= s2[0]) {
                s2 = c + s2;
            } else {
                s2 += c;
            }
        }

        return s2;
    }
};

int main(int argc, char* argv[]) {
    assert(argc == 2);
    string ifname (argv[1]);
    string ofname(argv[1]);

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
        ofs << c.solve();
        ofs << endl;
    }
      
    return 0;
}