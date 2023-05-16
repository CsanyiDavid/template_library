#define CATCH_CONFIG_MAIN

#include<string>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include"catch.hpp"
#include"../vector.h"

TEST_CASE("constructor"){
    Vector<int> v1;
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() == 2);

    Vector<double> v2(3);
    REQUIRE(v2.size() == 3);
    REQUIRE(v2.capacity() == 4);
    REQUIRE(v2[0] == 0.0);

    Vector<Vector<char>> v3(5, Vector<char>(2, 'x'));
    REQUIRE(v3.size() == 5);
    REQUIRE(v3.capacity() == 8);
    REQUIRE(v3[4].size()==2);
    REQUIRE(v3[4].capacity()==2);
    REQUIRE(v3[4][1] == 'x');
}

TEST_CASE("initializer list constructor"){
    Vector<int> v{1, 2, 3, 5, 6};
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 8);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 5);
    REQUIRE(v[4] == 6);
}

TEST_CASE("copy constructor"){
    Vector<Vector<int>> v(5, Vector<int> (3, 1));
    Vector<Vector<int>> copy{v};
    REQUIRE(v == copy);
}

TEST_CASE("reserve and capacity"){
    Vector<int> v;
    REQUIRE(v.capacity() == 2);
    v.resize(1);
    REQUIRE(v.capacity() == 2);
    v.reserve(10);
    REQUIRE(v.capacity() == 10);
    v.reserve(4);
    REQUIRE(v.capacity() == 10);
    v.resize(11);
    REQUIRE(v.capacity() == 20);
}

TEST_CASE("resize, size and empty"){
    Vector<float> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty());
    v.reserve(5);
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty());
    v.resize(7);
    REQUIRE(v.size() == 7);
    REQUIRE(!v.empty());
    v.resize(2);
    REQUIRE(v.size() == 2);
    REQUIRE(!v.empty());
    
    /*{
        Vector<bool> v2;
        size_t new_size{3 * (std::numeric_limits<size_t>::max()/4)};
        try{
            v2.resize(new_size);
            REQUIRE(v2.size() == new_size);
        } catch(const std::bad_alloc& e){
            //std::cerr << "bad_alloc" << std::endl;
        }

        Vector<Vector<long double>> v3;
        REQUIRE_THROWS_AS(v3.resize(-1, Vector<long double>(-1)), std::bad_alloc);
    }*/

    Vector<int> v4(2, 1);
    REQUIRE(v4.size() == 2);
    v4.resize(4,2);
    REQUIRE(v4.size() == 4);
    REQUIRE(v4[0] == 1);
    REQUIRE(v4[1] == 1);
    REQUIRE(v4[2] == 2);
    REQUIRE(v4[3] == 2);
    v4.resize(3, 555);
    v4.resize(6, 77);
    REQUIRE(v4.size() == 6);
    REQUIRE(v4[0] == 1);
    REQUIRE(v4[1] == 1);
    REQUIRE(v4[2] == 2);
    REQUIRE(v4[3] == 77);
    REQUIRE(v4[4] == 77);
    REQUIRE(v4[5] == 77);
}

TEST_CASE("const operator[]"){
    const Vector<std::string> v{"a", "sfdf", "sgfda", "sf", "sf", "dha"};
    REQUIRE(v[0] == "a");
    REQUIRE(v[1] == "sfdf");
    REQUIRE(v[2] == "sgfda");
    REQUIRE(v[3] == "sf");
    REQUIRE(v[4] == "sf");
    REQUIRE(v[5] == "dha");
}

TEST_CASE("operator[]"){
    Vector<std::string> v{"a", "sfdf", "sgfda", "sf", "sf", "dha"};
    v[4] = "four";
    v[2] = "two";
    REQUIRE(v[0] == "a");
    REQUIRE(v[1] == "sfdf");
    REQUIRE(v[2] == "two");
    REQUIRE(v[3] == "sf");
    REQUIRE(v[4] == "four");
    REQUIRE(v[5] == "dha");
}

TEST_CASE("push_back"){
    Vector<float> v;
    v.push_back(2.1);
    v.push_back(4.5);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 2.1f);
    REQUIRE(v[1] == 4.5f);
    v.resize(10);
    v.push_back(3.3);
    REQUIRE(v.size() == 11);
    REQUIRE(v[9] == 0.0f);
    REQUIRE(v[10] == 3.3f);
    v.resize(1);
    v.push_back(77.78);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 2.1f);
    REQUIRE(v[1] == 77.78f);
}

TEST_CASE("const size, capacity, empty"){
    const Vector<int> v{1, 2, 3, 4, 5, 6};
    REQUIRE(v.size() == 6);
    REQUIRE(v.capacity() == 8);
    REQUIRE(!v.empty());
    const Vector<double> v2;
    REQUIRE(v2.size() == 0);
    REQUIRE(v2.capacity() == 2);
    REQUIRE(v2.empty());
}

TEST_CASE("operator="){
    Vector<int> v1{1, 2, 3, 7, 8};
    Vector<int> v2{3, 4, 4, 8, 9, 10};
    Vector<int> v3(15, 3);
    v3 = v1 = v2;
    REQUIRE(v1.size() == v2.size());
    REQUIRE(v3.size() == v2.size());
    for(unsigned int i=0; i<v1.size(); ++i){
        REQUIRE(v1[i] == v2[i]);
        REQUIRE(v3[i] == v2[i]);
    }
}

TEST_CASE("operator== and operator!="){
    Vector<Vector<std::string>> v1(10, Vector<std::string> (5, "init"));
    Vector<Vector<std::string>> v2(10, Vector<std::string> (5, "init"));
    REQUIRE(v1 == v2);
    REQUIRE_FALSE(v1 != v2);
    v1[4][1] = "da";
    REQUIRE_FALSE(v1 == v2);
    REQUIRE(v1 != v2);
    v2[4][1] = "da";
    REQUIRE(v1 == v2);
    REQUIRE_FALSE(v1 != v2);
}

TEST_CASE("iterator"){
    Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i{0};
    Vector<int>::Iterator it;
    for(it = v.begin(); it!=v.end(); ++it){
        REQUIRE(*it == i);
        ++i;
    }
    for(--it; it!=v.begin(); --it){
        --i;
        REQUIRE(*it == i);
    }
}

TEST_CASE("iterator comparison"){
    Vector<std::string> v(10, "init");
    Vector<std::string>::Iterator it1{v.begin()};
    auto it2{v.begin() + 3};
    REQUIRE(it1 < it2);
    REQUIRE(it1 <= it2);
    REQUIRE_FALSE(it1 > it2);
    REQUIRE_FALSE(it1 >= it2);
    REQUIRE_FALSE(it1 == it2);
    REQUIRE(it1 != it2);
    it1 += 3;
    REQUIRE_FALSE(it1 < it2);
    REQUIRE(it1 <= it2);
    REQUIRE_FALSE(it1 > it2);
    REQUIRE(it1 >= it2);
    REQUIRE(it1 == it2);
    REQUIRE_FALSE(it1 != it2);
    it1 += 1;
    REQUIRE_FALSE(it1 < it2);
    REQUIRE_FALSE(it1 <= it2);
    REQUIRE(it1 > it2);
    REQUIRE(it1 >= it2);
    REQUIRE_FALSE(it1 == it2);
    REQUIRE(it1 != it2);
}

TEST_CASE("iterator +, -, +=, -="){
    Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int>::Iterator it{v.begin()};
    REQUIRE(*it == 0);
    it = it + 5;
    REQUIRE(*it == 5);
    it += 2;
    REQUIRE(*it == 7);
    it -= 4;
    REQUIRE(*it == 3);
    it = it - 2;
    REQUIRE(*it == 1);
}

TEST_CASE("std sort"){
    Vector<int> v;
    srand(std::time(NULL));
    int n{500};
    int max_value{100000};
    for(int i=0; i<n; ++i){
        v.push_back(rand()%max_value);
    }
    std::sort(v.begin(), v.end());
    for(int i=1; i<n; ++i){
        REQUIRE(v[i-1] <= v[i]);
    }
}

TEST_CASE("move assignment"){
    Vector<int> v1{0, 1, 2, 3, 4};
    Vector<int> v2;
    REQUIRE(v1.size() == 5);
    REQUIRE(v2.size() == 0);
    REQUIRE(v1.capacity() == 8);
    v2 = std::move(v1);
    REQUIRE(v1.size() == 0);
    REQUIRE(v2.size() == 5);
    REQUIRE(v2.capacity() == 8);
}

TEST_CASE("move constructor"){
    Vector<int> v1{0, 1, 2, 3, 4};
    REQUIRE(v1.size() == 5);
    REQUIRE(v1.capacity() == 8);
    Vector<int> v2{std::move(v1)};
    REQUIRE(v1.size() == 0);
    REQUIRE(v2.size() == 5);
    REQUIRE(v2.capacity() == 8);
}

TEST_CASE("insert"){
    Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15};
    Vector<int>::Iterator it;
    it = v.insert(v.begin() + 4, 42);
    REQUIRE(*it == 42);
    it = v.insert(v.begin() + 16, 14);
    REQUIRE(*it == 14);
    it = v.insert(v.begin() + 0, -5);
    REQUIRE(*it == -5);

    Vector<int> target{-5, 0, 1, 2, 3, 42, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 14};
    for(unsigned int i=0; i<v.size(); ++i){
        REQUIRE(v[i] == target[i]);
    }
}

TEST_CASE("==, !="){
    Vector<char> v1{'a', 'b', 'k'};
    Vector<char> v2{'a', 'b'};
    REQUIRE(v1 != v2);
    REQUIRE_FALSE(v1 == v2);
    v2.push_back('k');
    REQUIRE_FALSE(v1 != v2);
    REQUIRE(v1 == v2);
    v2.push_back('k');
    v1.push_back('l');
    REQUIRE(v1 != v2);
    REQUIRE_FALSE(v1 == v2);
}

TEST_CASE("<"){
    Vector<int> v1{1, 2};
    Vector<int> v2{1, 2};
    REQUIRE_FALSE(v1 < v2);
    v2.push_back(-1);
    REQUIRE(v1 < v2);
    v1.push_back(-1);
    v1.push_back(3);
    v2.push_back(4);
    v1.push_back(100);
    v2.push_back(3);
    REQUIRE(v1 < v2);
}

TEST_CASE("<="){
    Vector<int> v1{1, 2};
    Vector<int> v2{1, 2};
    REQUIRE(v1 <= v2);
    v2.push_back(-1);
    REQUIRE(v1 <= v2);
    v1.push_back(-1);
    v1.push_back(3);
    v2.push_back(4);
    v1.push_back(100);
    v2.push_back(3);
    REQUIRE(v1 <= v2);
}

TEST_CASE("std sort vector of vectors"){
    Vector<Vector<int>> v{
        {3, 3, 3},
        {3, 2, 4},
        {3, 3, 2},
        {4, 5, 6},
        {1, -1, -5}
    };

    std::sort(v.begin(), v.end());
    Vector<Vector<int>> target{
        {1, -1, -5},
        {3, 2, 4},
        {3, 3, 2},
        {3, 3, 3},
        {4, 5, 6}
    };
    REQUIRE(v == target);
}