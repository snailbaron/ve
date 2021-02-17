#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "ve.hpp"

template <class T> struct XYModel {
    T x;
    T y;
};
template <class T> using XYVector = ve::Vector<XYModel, T, 2>;
template <class T> using XYPoint = ve::Point<XYModel, T, 2>;

template <class T> struct RGBModel {
    T r;
    T g;
    T b;
};
template <class T> using RGBVector = ve::Vector<RGBModel, T, 3>;
template <class T> using RGBPoint = ve::Point<RGBModel, T, 3>;

template <class T> struct UVModel {
    T u;
    T v;
};
template <class T> using UVVector = ve::Vector<UVModel, T, 2>;
template <class T> using UVPoint = ve::Point<UVModel, T, 2>;

TEST_CASE("Vector initialization")
{
    SECTION("Explitit arguments") {
        auto v = XYVector<int>{1, 2};
        REQUIRE(v.x == 1);
        REQUIRE(v.y == 2);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
    }

    SECTION("Calling default constructor") {
        auto v = XYVector<int>{};
        REQUIRE(v.x == 0);
        REQUIRE(v.y == 0);
    }

    SECTION("Default initialization") {
        XYVector<int> v;
        REQUIRE(v.x == 0);
        REQUIRE(v.y == 0);
    }
}
