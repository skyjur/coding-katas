#include <algorithm>
#include <iostream>

using namespace std;

int main(){
    cout << max(1, 2) << endl;
    cout << max({1, 2, 3}) << endl;
    cout << max({1,2,3}, [](const int &a, const int &b) { return a < b; }) << endl;
    vector<int> v = {1,2,3,4};
    cout << *max_element(v.begin(), v.end(), [](int a, int b) { return a < b; }) << endl;
}