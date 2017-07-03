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
    vector<Edge*> edges;
    Node(Graph &g_, int id_) : g(g_), id(id_) {}
};


struct Edge {
    int id;
    Node &a;
    Node &b;
    int dist;
    Edge(int id_, Node &a_, Node &b_, int dist_) : id(id_), a(a_), b(b_), dist(dist_) {}
};


struct Graph {
    int n=0;
    vector<Node> nodes = {};
    vector<Edge> edges = {};

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

    string toDot() {
        ostringstream s;

        s << "digraph G {" << endl;

        for(Node a : nodes) {
            for(Edge *e : a.edges) {
                s << "  n" << a.id << " -> ";
                s << "n" << e->b.id << "[label=" << e->dist << "]";
                s << ";" << endl;
            }
        }

        s << "}" << endl;

        return s.str();
    }
};


struct Case {
    int n;
    Graph g;

    void read(istream &f) {
        f >> n;
        g.init(n);
        string buf;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int dist;
                f >> dist;
                if(dist != -1) {
                    g.add_edge(i, j, dist);
                }
            }
        }

        cout << g.toDot();
    }

    string solve() {
        ostringstream s;

       

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
        cout << "Loading Case #" << i+1 << "..." << endl;
        Case c;
        c.read(ifs);
        ofs << "Case #" << (i+1) << ": ";
        ofs << c.solve();
        ofs << endl;
    }
      
    return 0;
}