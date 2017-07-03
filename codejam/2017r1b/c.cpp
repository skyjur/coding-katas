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


struct Graph;
struct Edge;
struct Node;


struct Node {
    Graph &g;
    int id;
    int e;  // max horse distance
    int s;  // 
    vector<Edge*> edges = {};
    Node(Graph &g_, int id_) : g(g_), id(id_) { edges = {}; }
};


struct Edge {
    int id;
    Node &a;
    Node &b;
    int dist;
    Edge(int id_, Node &a_, Node &b_, int dist_) : id(id_), a(a_), b(b_), dist(dist_) {}
};

struct Pair {
    Node &a;
    Node &b;
    Pair(Node &a_, Node &b_) : a(a_), b(b_) {}
};


struct Graph {
    int n=0;
    vector<Node> nodes = {};
    vector<Edge> edges = {};
    vector<Pair> pairs = {};

    void init(int n_) {
        assert(n == 0);
        n = n_;
        for(int i=0; i<n; i++) {
            Node n(*this, i);
            nodes.push_back(n);
        }
    }

    void add_edge(int a, int b, int dist) {
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        Edge *e = new Edge(edges.size(), nodes[a], nodes[b], dist);
        edges.push_back(*e);
        nodes[a].edges.push_back(e);
    }

    void add_pair(int a, int b) {
        a -= 1;
        b -= 1;
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        assert(nodes[a].id == a);
        assert(nodes[b].id == b);
        pairs.push_back(Pair(
            nodes[a], nodes[b]
        ));
    }

    string toDot() {
        ostringstream s;

        s << "digraph G {" << endl;

        for(Node a : nodes) {
            if(a.edges.begin() == a.edges.end()) { continue; }
            cout << "\n  /**a.id " << a.id << " edges " << a.edges.size() << " **/\n" << endl;
            for(Edge *e : a.edges) {
                s << "  n" << a.id << "[label=\"n" ;
                s << a.id << " E=" << a.e << " S=" << a.s << "\"];" << endl;
                s << "  n" << a.id << " -> ";
                s << "n" << e->b.id << "[label=" << e->dist << "]";
                s << ";" << endl;
            }
        }

        int i=1;
        for(Pair p : pairs) {
                s << "  n" << p.a.id << " -> n" << p.b.id << "[color=red label=" << i << "];" << endl;
                i++;
            }

        s << "}" << endl;

        return s.str();
    }
};


struct Case {
    int n, q;
    Graph g;
    vector<int> U = {};
    vector<int> V = {};

    void read(istream &f) {
        f >> n >> q;
        cout << "n=" << n << " q=" << q << endl;
        g.init(n);
        for(int i=0; i<n; i++) {
            f >> g.nodes[i].e >> g.nodes[i].s;
        }
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int dist;
                f >> dist;
                if(dist != -1) {
                    g.add_edge(i, j, dist);
                }
            }
        }
        for(int i=0; i<q; i++) {
            int u, v;
            f >> u >> v;
            U.push_back(u);
            V.push_back(v);
            g.add_pair(u, v);
        }

        cout << "Graph read.";

        cout << g.toDot();
    }

    string solve() {
        ostringstream s("");
        s.setf(ios::fixed);
        s.precision(6);

        vector<vector<double>> m(100, vector<double>(100, 10e19));

        for(Node a : g.nodes) {
            assert(a.id < 100 && a.id >= 0);
            for(Edge *e : a.edges) {
                m[a.id][e->b.id] = (double)e->dist;
            }
        }

        for(Node k : g.nodes) {
            for(Node i : g.nodes) {
                for(Node j : g.nodes) {
                    if(m[i.id][k.id] + m[k.id][j.id] < m[i.id][j.id]) {
                        m[i.id][j.id] = m[i.id][k.id] + m[k.id][j.id];
                    }
                }
            }
        }

        for(Node i : g.nodes) {
            for(Node j : g.nodes) {
                if(m[i.id][j.id] <= (double)i.e) {
                    m[i.id][j.id] = m[i.id][j.id] / (double)i.s;
                } else {
                    m[i.id][j.id] = 10e19;
                }
            }
        }

        for(Node k : g.nodes) {
            for(Node i : g.nodes) {
                for(Node j : g.nodes) {
                    if(m[i.id][k.id] + m[k.id][j.id] < m[i.id][j.id]) {
                        m[i.id][j.id] = m[i.id][k.id] + m[k.id][j.id];
                    }
                }
            }
        }

        for(Pair p : g.pairs) {
            s << " " << m[p.a.id][p.b.id];
        }

        cout << s.str() << endl;

        return s.str();
    }
};

int main(int argc, char* argv[]) {
    string ifname (argc == 2 ? argv[1] : "C-test.in");
    string ofname(ifname);

    assert(ifname.find(".in") == ifname.size() - 3);
    // replace *.in to *.out:
    ofname.replace(ofname.size() - 3, 3, ".out");

    ifstream ifs(ifname.c_str());
    ifs.exceptions(ios::failbit | ios::badbit);
    assert(ifs.is_open());

    ofstream ofs(ofname.c_str());
    assert(ofs.is_open());

    int t;
    ifs >> t;

    for(int i=1; i<=t; i++){
        cout << "Loading Case #" << i << "..." << endl;
        Case c;
        c.read(ifs);
        ofs << "Case #" << i << ":";
        ofs << c.solve();
        ofs << endl;
    }
      
    return 0;
}