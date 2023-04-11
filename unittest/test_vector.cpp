#define CATCH_CONFIG_MAIN

#include<string>
#include "catch.hpp"
#include"../vector.h"

TEST_CASE("constructor"){
    Vector<int> v1;
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() == 2);

    Vector<double> v2(3);
    REQUIRE(v2.size() == 3);
    REQUIRE(v2.capacity() == 4);
    REQUIRE(v2[0] == 0.0);

    /*Vector<Vector<char>> v3(5, Vector<char>(2, 'x'));
    for(int i=0; i<v3.size(); ++i){
        for(int j=0; j<v3[i].size(); ++j){
            std::cerr << v3[i][j] << " ";
        }
        std::cerr << std::endl;
    }
    REQUIRE(v3.size() == 5);
    REQUIRE(v3.capacity() == 8);
    REQUIRE(v3[4].size()==2);
    REQUIRE(v3[4].capacity()==2);
    REQUIRE(v3[4][1] == 'x');*/
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