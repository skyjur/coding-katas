#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

ifstream ifs ("A-test.in");
ofstream ofs ("A-test.out");


struct Horse {
    int k, s;

    void read() {
        ifs >> k >> s;
    }
};


struct Case {
    int D, N;
    vector<Horse> horses;

    void read() {
        ifs >> D >> N;

        for(int i=0; i<N; i++) {
            Horse h;
            h.read();
            horses.push_back(h);
        }

        cout << "D=" << D << " N=" << N << " horses=" << endl;
        for(Horse h : horses) {
            cout << "  | k=" << h.k << " s=" << h.s << endl;
        }
    }

    void solve(){
        double t = .0;
        for(Horse h : horses) {
            int d = D - h.k;
            t = max(t, (double) d / (double) h.s);
        }

        double r = D/t;

        cout << "t=" << t << " r=" << r << endl;

        ofs << r;
    }
};

int main() {
    int n;
    ifs >> n;
    ofs.precision(6);
    ofs.setf(ios::fixed);

    for(int i=0; i<n; i++){
        Case c;
        c.read();

        ofs << "Case #" << (i+1) << ": ";
        c.solve();
        ofs << endl;
    }
}