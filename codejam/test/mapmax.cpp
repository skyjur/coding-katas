#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

template<class K, class V> K max_key(const map<K, V> &m) {
    return (*max_element(m.begin(), m.end(),
        [](const pair<K, V> &a, const pair<K, V> &b) { return a.second < b.second; }
    )).first;
}

int main(){
    map<int, string> m = {{1, "Adam"}, {2, "John"}, {0, "Zed"}};

    cout << max_key(m);
}