#include <iostream>
#include <limits>
#include <vector>
#include "vector.h"

using namespace std;

int main() {
    vector<int> v(2, 3);
    v.resize(5, 6);
    for(int i=0; i<v.size(); ++i){
        cout << v[i] << ' ';
    }
    cout << endl;
    return 0;
}
