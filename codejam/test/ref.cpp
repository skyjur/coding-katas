#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct B;
struct C;

struct A {
    B &b;
    int j=0;
    A(B &b_, int j_) : b(b_), j(j_) {}
};

struct C {
    B &b;
    C(B &b_) : b(b_) {}
};

struct B {
    int i=0;
    C *c;

    B() {
        c = new C(*this);
    }
};




int main() {
    vector<int> v = {1};
    map<int, int> m = {{1, 1}};
    int &i = v[0];
    i++;
    int &j = m[1];
    j++;
    cout << v[0] << endl;
    cout << m[1] << endl << endl;

    B b;
    A a(b, 5);
    a.b.i=3;
    cout << "A.j=" << a.j << endl;
    cout << "b.i=" << b.i << endl;
    cout << "a.b.i=" << a.b.i << endl;
    cout <<" *a.b == *b ? " << (&a.b == &b ? "y" : "n") << endl << endl;
    cout <<" b.c->b == &b ? " << (&b.c->b == &b ? "y" : "n") << endl << endl;

    int x = 1;
    vector<int*> vx;
    vx.push_back(&x);
    x++;
    (*vx[0])++;
    for(int *i : vx) {
        cout << "vx[] = " << *i;
    }
}