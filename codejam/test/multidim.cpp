#include <vector>
#include <iostream>

using namespace std;

int main(){
    vector<vector<int>> m(10, vector<int>(10, 5));

    for(vector<int> r : m) {
        for(int c : r) {
            cout << c << " ";
        }
        cout << endl;
    }
}