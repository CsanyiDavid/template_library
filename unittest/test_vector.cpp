#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include"../vector.h"

TEST_CASE("constructor"){
    Vector<int> v1;
    CHECK(v1.size() == 0);
    CHECK(v1.capacity() == 2);

    Vector<double> v2(3);
    CHECK(v2.size() == 3);
    CHECK(v2.capacity() == 4);
    CHECK(v2[0] == 0.0);

    Vector<Vector<char>> v3(5, Vector<char>(2, 'x'));
    CHECK(v3.size() == 5);
    CHECK(v3.capacity() == 8);
    CHECK(v3[4].size()==2);
    CHECK(v3[4].capacity()==2);
    CHECK(v3[4][1] == 'x');
}

TEST_CASE("reserve and capacity"){
    Vector<int> v;
    CHECK(v.capacity() == 2);
    v.resize(1);
    CHECK(v.capacity() == 2);
    v.reserve(10);
    CHECK(v.capacity() == 10);
    v.reserve(4);
    CHECK(v.capacity() == 10);
    v.resize(11);
    CHECK(v.capacity() == 20);
}

TEST_CASE("resize and size"){
    Vector<float> v;
    CHECK(v.size() == 0);
    v.reserve(5);
    CHECK(v.size() == 0);
    v.resize(7);
    CHECK(v.size() == 7);
    v.resize(2);
    CHECK(v.size() == 2);
    v.resize(-1);
}
