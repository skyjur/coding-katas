#include <vector>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

const int NMAX = 100;

enum ModelType
{
    Zero = 0,
    Bishop = 1,
    Rook = 2,
    Queen = 3
};

ModelType getModelType(char c) {
    switch(c) {
        case '.': return Zero; break;
        case '+': return Bishop; break;
        case 'x': return Rook; break;
        case 'o': return Queen; break;
        default:
            char buf[100];
            sprintf(buf, "Invalid model value: %d", (int)c);
            throw invalid_argument(buf);
    }
}

struct Model
{
    int i;  // row
    int j;  // col
    ModelType t;

    Model() {}
    Model(int ii, int jj, ModelType tt) {
        i = ii;
        j = jj;
        t = tt;
    }
    Model(int ii, int jj, char tc) {
        i = ii;
        j = jj;
        t = getModelType(tc);
    }
};

struct CASE
{
    int n;
    vector<Model> models;
};

char getModelChar(ModelType t) {
    switch(t) {
        case Zero: return '.'; break;
        case Bishop: return '+'; break;
        case Rook: return 'x'; break;
        case Queen: return 'o'; break;
        default: throw t;
    }
};

void printgrid(int n, vector<Model> &models)
{
    int grid[NMAX][NMAX] = {0};
    for(Model m : models) {
        grid[m.i][m.j] |= (int)m.t;
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << getModelChar(static_cast<ModelType>(grid[i][j]));
        }
        cout << endl;
    }
};

CASE readcase()
{
    CASE c;
    int m;
    cin >> c.n >> m;
    
    for(int x=0; x<m; x++) {
        Model m;
        char mc;
        int i, j;
        cin >> mc >> i >> j;
        if(mc == 'o') {
            // split queen into bishop and rook
            c.models.push_back(Model(i-1, j-1, '+'));
            c.models.push_back(Model(i-1, j-1, 'x'));
        } else {
            c.models.push_back(Model(i-1, j-1, mc));
        }
    }
    return c;
};

vector<Model> filter(vector<Model> &models, ModelType t) {
    vector<Model> models2;
    for(Model m : models) {
        if(m.t == t) { models2.push_back(m); }
    }
    return models2;
}

bool rookOverlap(int i, int j, vector<Model> &models) {
    for(Model r : models) {
        if(i == r.i || j == r.j) return true;
    }
    return false;
}

bool is_valid(Model a, Model b) {
    if(a.t & Rook && b.t & Rook) {
        return a.i != b.i && a.j != b.j;
    }
    return true;
}


bool is_valid(vector<Model> &models, Model b) {
    if(models.size() == 0) { return true; }
    return all_of(models.begin(), models.end(), [b](Model a) { return is_valid(a, b); });
}

void solveRooks(CASE &c) {
    for(int i=0; i<c.n; i++) {
        if(is_valid(c.models, Model(i, -1, Rook))) {
            for(int j=0; j<c.n; j++) {
                auto m = Model(i, j, Rook);
                if(is_valid(c.models, m)) {
                    c.models.push_back(m);
                    break;
                }
            }
        }
    }
}

struct Point {
    int x;
    int y;

    Point() {}
    Point(int xi, int yi) {
        x = xi;
        y = yi;
    }

    operator==(Point p) const {
        return p.x==x && p.y == y;
    }
};
typedef vector<Point> PointVector;

vector<PointVector> diagonals(int n) {
    vector<PointVector> l;

    for(int i=0; i<n*2-1; i++) {
        PointVector v;
        l.push_back(v);
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            l[i+j].push_back(Point(i, j));
        }
    }

    sort(l.begin(), l.end(), [](PointVector a, PointVector b) { return a.size() < b.size(); });

    return l;
}

void solveBishops(CASE &c) {
}

void test() {
    Model r00 = Model(0, 0, Rook);
    Model r01 = Model(0, 1, Rook);
    Model r11 = Model(1, 1, Rook);

    assert(is_valid(r00, r11) == true);
    assert(is_valid(r00, r01) == false);

    vector<Model> empty;
    assert(is_valid(empty, r00) == true);
    assert(is_valid(empty, r01) == true);
    assert(is_valid(empty, r11) == true);

    vector<Model> ml = {r00};
    assert(is_valid(ml, r11) == true);
    assert(is_valid(ml, r01) == false);

    vector<PointVector>
    a1 = {
        {Point(0, 0)},
        {Point(1, 1)},
        {Point(0, 1), Point(1, 0)}
    },
    b1=diagonals(2),
    b2=diagonals(3);

    assert(a1 == b1);
    assert(b2[0] == PointVector({Point(0, 0)}));
    assert(b2[1] == PointVector({Point(2, 2)}));
    assert(b2[2] == PointVector({Point(0, 1), Point(1, 0)}));
    assert(b2[3] == PointVector({Point(1, 2), Point(2, 1)}));
    assert(b2[4] == PointVector({Point(0, 2), Point(1, 1), Point(2, 0)}));
}

int main()
{  
    test();

    freopen("d-test.in", "r", stdin);
    int x;
    cin >> x;
    for (int i=1; i<=x; i++)
    {
        CASE c;
        c = readcase();
        cout << "Case #" << i << endl;
        printgrid(c.n, c.models);
        cout << "Solving rooks" << endl;
        solveRooks(c);
        printgrid(c.n, c.models);
    }
};