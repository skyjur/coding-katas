#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <cassert>
#include <string>
#include <sstream>

using namespace std;


struct Case {
    int n;
    vector<string> lines;

    void read(istream &f) {
        f >> n;
        for(int i=0; i<n; i++) {
            string d;
            f >> d;
            lines.push_back(d);
        }
    }

    string solve() {
        ostringstream s;

        s << endl;
        for(string d : lines) {
            s << d << endl;
        }
        s << endl;

        return s.str();
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

    for(int i=0; i<n; i++){
        Case c;
        c.read(ifs);
        ofs << "Case #" << (i+1) << ": ";
        ofs << c.solve();
        ofs << endl;
    }
      
    return 0;
}