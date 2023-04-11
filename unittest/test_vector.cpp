#define CATCH_CONFIG_MAIN

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

    Vector<Vector<char>> v3(5, Vector<char>(2, 'x'));
    REQUIRE(v3.size() == 5);
    REQUIRE(v3.capacity() == 8);
    REQUIRE(v3[4].size()==2);
    REQUIRE(v3[4].capacity()==2);
    REQUIRE(v3[4][1] == 'x');
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
    
    Vector<bool> v2;
    size_t new_size{3 * (std::numeric_limits<size_t>::max()/4)};
    try{
        v2.resize(new_size);
        REQUIRE(v2.size() == new_size);
    } catch(const std::bad_alloc& e){
        std::cerr << "bad_alloc" << std::endl;
    }

    Vector<Vector<long double>> v3;
    REQUIRE_THROWS_AS(v3.resize(-1, Vector<long double>(-1)), std::bad_alloc);
}
