#include <map>
#include <iostream>

using namespace std;

int main(){
    map<int, string> m = {{1, "One"}, {2, "Two"}};

    for(auto i: m) {
        cout << i.first << " " << i.second << endl;
    }
}