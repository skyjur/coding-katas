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
#define M_PI           3.14159265358979323846

using namespace std;


struct Cake {
    int id;
    int r;
    int h;

    double side_surface() {
        return 2*M_PI*r*h;
    }

    double top_surface(){
        return M_PI*r*r;
    }

    double surface() {
        return side_surface() + top_surface();
    }

    string str(){
        ostringstream s;
        s << "Cake(r=" << r << ", h=" <<  h << ")";
        return s.str();
    }
};


struct Case {
    int n, k;
    vector<int> radius;
    vector<int> height;
    vector<Cake> cakes;

    void read(istream &f) {
        f >> n >> k;
        cout << n << " " << k << endl;
        for(int i=0; i<n; i++) {
            Cake c;
            f >> c.r >> c.h;
            c.id = i;
            cakes.push_back(c);
            cout << c.r << " " << c.h << endl;
        }
    }

    double solve() {

        sort(cakes.begin(), cakes.end(), [](Cake a, Cake b) {
            return a.surface() > b.surface();
        });

        sort(cakes.begin(), cakes.end(), [](Cake a, Cake b) {
            return a.r > b.r;
        });

        double smax=0;

        for(Cake base : cakes) {
            vector<Cake> l = {};

            for(Cake c : cakes) {
                if(c.r <= base.r && c.id != base.id) {
                    l.push_back(c);
                }
            }

            if(l.size() + 1 < (unsigned int)k) { continue; }

            sort(l.begin(), l.end(), [](Cake a, Cake b) {
                return a.side_surface() > b.side_surface();
            });

            double S = base.side_surface() + base.top_surface();       
            
            for(int j=0; j<(k-1); j++) {
                S += l[j].side_surface();
            }

            smax = max(smax, S);
        }

        cout << " =" << smax;

        return smax;

    }
};

int main(int argc, char* argv[]) {
    string ifname (argc == 2 ? argv[1] : "A-test.in");
    string ofname(ifname);

    assert(ifname.find(".in") == ifname.size() - 3);
    // replace *.in to *.out:
    ofname.replace(ofname.size() - 3, 3, ".out");

    ifstream ifs(ifname.c_str());
    ifs.exceptions(ios::failbit | ios::badbit);
    assert(ifs.is_open());

    ofstream ofs(ofname.c_str());
    assert(ofs.is_open());

    ofs.precision(9);
    ofs.setf(ios::fixed);
    cout.precision(9);
    cout.setf(ios::fixed);

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