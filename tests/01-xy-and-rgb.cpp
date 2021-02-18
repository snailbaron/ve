#include <ve.hpp>

#include <catch2/catch.hpp>

#include <type_traits>

#define HAS_TYPE(EXPRESSION, TYPE) \
    static_assert(std::is_same<decltype(EXPRESSION), TYPE>());

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

TEST_CASE("Initialization, explicit arguments")
{
    auto v = XYVector<int>{1, 2};
    auto p = XYPoint<int>{3, 4};
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(p.x == 3);
    REQUIRE(p.y == 4);
    REQUIRE(p[0] == 3);
    REQUIRE(p[1] == 4);
}

TEST_CASE("Initialization default constructor", "[initialization]")
{
    auto v = XYVector<int>{};
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);

    auto p = XYPoint<int>{};
    REQUIRE(p.x == 0);
    REQUIRE(p.y == 0);
}

TEST_CASE("Default initialization", "[initialization]")
{
    XYVector<int> v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);

    XYPoint<int> p;
    REQUIRE(p.x == 0);
    REQUIRE(p.y == 0);
}

TEST_CASE("Vector conversions")
{
    XYVector<short> v;

    HAS_TYPE(v, XYVector<short>);
    HAS_TYPE(1.f * v, XYVector<float>);
}

TEST_CASE("Vector arithmetics")
{
    auto u = XYVector<int>{1, 2};
    auto v = XYVector<int>{3, 4};
}
