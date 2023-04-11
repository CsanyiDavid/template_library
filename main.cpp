#include <iostream>
#include <limits>
#include "vector.h"

using namespace std;

int main() {
    Vector<int> v;
    v.reserve(10);
    cout << numeric_limits<size_t>::max() << endl;
    Vector<double> v2;
    try{
        v.resize(-1);
        v2.resize(-1);
    } catch(std::bad_alloc const&){
        std::cerr << "bad_alloc" << std::endl;
    }
    return 0;
}
