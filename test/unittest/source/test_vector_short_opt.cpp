#include "catch/catch.hpp"

#include "vector_short_opt.h"

#include "util_num_elems.h"

#include <stdexcept>
#include <cstddef> // std::size_t


template<typename T>
struct vec4
{
    typedef opt::vector_short_opt<T, 4> type;
};

template<typename T>
struct vect
{
    typedef std::vector<T> type;
};

void requireEqual(vec4<int>::type const & v4, vect<int>::type const & vr)
{
    REQUIRE(v4.size() == vr.size());

    vec4<int>::type::size_type v4i = 0;
    vect<int>::type::size_type vri = 0;

    for (; v4i != v4.size() && vri != vr.size(); ++v4i, ++vri)
    {
        REQUIRE(v4[v4i] == vr[vri]);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Default ctor", "[opt][ctor][default]")
{
    vec4<int>::type const v4;

    REQUIRE(v4.capacity() >= v4.size());

    REQUIRE(v4.size() == 0);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Fill ctor", "[opt][ctor][fill]")
{
    int const v = 7;

    SECTION("Zero-size")
    {
        std::size_t const s = 0;
        vec4<int>::type const v4(s, v);
        vect<int>::type const vr(s, v);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(v4.size() == s);

        requireEqual(v4, vr);
    }

    SECTION("One-size")
    {
        std::size_t const s = 1;
        vec4<int>::type const v4(s, v);
        vect<int>::type const vr(s, v);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(v4.size() == s);

        requireEqual(v4, vr);
    }

    SECTION("Sixteen-size")
    {
        std::size_t const s = 16;
        vec4<int>::type const v4(s, v);
        vect<int>::type const vr(s, v);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(v4.size() == s);

        requireEqual(v4, vr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Range ctor", "[opt][ctor][range]")
{
    int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};

    SECTION("Zero-range")
    {
        std::size_t const s = 0;
        vec4<int>::type const v4(arr, arr + s);
        vect<int>::type const vr(arr, arr + s);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(v4.size() == s);

        requireEqual(v4, vr);
    }

    SECTION("One-range")
    {
        std::size_t const s = 1;
        vec4<int>::type const v4(arr, arr + s);
        vect<int>::type const vr(arr, arr + s);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(v4.size() == s);

        requireEqual(v4, vr);
    }

    SECTION("Sixteen-range")
    {
        std::size_t const s = 16;
        vec4<int>::type const v4(arr, arr + s);
        vect<int>::type const vr(arr, arr + s);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(v4.size() == s);

        requireEqual(v4, vr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Copy ctor", "[opt][ctor][copy]")
{
    int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};

    SECTION("Zero-range")
    {
        std::size_t const s = 0;
        vec4<int>::type const ov4(arr, arr + s);
        vect<int>::type const ovr(arr, arr + s);

        vec4<int>::type const cv4(ov4);

        REQUIRE(cv4.capacity() >= cv4.size());
        REQUIRE(cv4.size() == s);

        requireEqual(cv4, ovr);
    }

    SECTION("One-range")
    {
        std::size_t const s = 1;
        vec4<int>::type const ov4(arr, arr + s);
        vect<int>::type const ovr(arr, arr + s);

        vec4<int>::type const cv4(ov4);

        REQUIRE(cv4.capacity() >= cv4.size());
        REQUIRE(cv4.size() == s);

        requireEqual(cv4, ovr);
    }

    SECTION("Sixteen-range")
    {
        std::size_t const s = 16;
        vec4<int>::type const ov4(arr, arr + s);
        vect<int>::type const ovr(arr, arr + s);

        vec4<int>::type const cv4(ov4);

        REQUIRE(cv4.capacity() >= cv4.size());
        REQUIRE(cv4.size() == s);

        requireEqual(cv4, ovr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Copy assignment operator", "[opt][operator][copy][assignment]")
{
    int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};

    SECTION("Zero-size")
    {
        vec4<int>::type::size_type const s = 0;
        vec4<int>::type const ov4(arr, arr + s);
        vect<int>::type const ovr(arr, arr + s);
        vec4<int>::type const dv4(arr + 2, arr + 5);

        vec4<int>::type cv4(dv4);

        cv4 = ov4;

        REQUIRE(cv4.capacity() >= cv4.size());
        REQUIRE(cv4.size() == s);

        requireEqual(cv4, ovr);
    }

    SECTION("One-size")
    {
        vec4<int>::type::size_type const s = 1;
        vec4<int>::type const ov4(arr, arr + s);
        vect<int>::type const ovr(arr, arr + s);
        vec4<int>::type const dv4(arr + 2, arr + 5);

        vec4<int>::type cv4(dv4);

        cv4 = ov4;

        REQUIRE(cv4.capacity() >= cv4.size());
        REQUIRE(cv4.size() == s);

        requireEqual(cv4, ovr);
    }

    SECTION("Sixteen-size")
    {
        vec4<int>::type::size_type const s = 16;
        vec4<int>::type const ov4(arr, arr + s);
        vect<int>::type const ovr(arr, arr + s);
        vec4<int>::type const dv4(arr + 2, arr + 5);

        vec4<int>::type cv4(dv4);

        cv4 = ov4;

        REQUIRE(cv4.capacity() >= cv4.size());
        REQUIRE(cv4.size() == s);

        requireEqual(cv4, ovr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Begin", "[opt][begin]")
{
    SECTION("Empty")
    {
        SECTION("Const")
        {
            vec4<int>::type const v4;

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.begin() == v4.end());
        }

        SECTION("Non-const")
        {
            vec4<int>::type v4;

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.begin() == v4.end());
        }
    }

    SECTION("Non-empty")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 1;

        SECTION("Const")
        {
            vec4<int>::type const v4(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.begin() != v4.end());
            REQUIRE(*v4.begin() == v);
        }

        SECTION("Non-const")
        {
            vec4<int>::type v4(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.begin() != v4.end());
            REQUIRE(*v4.begin() == v);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("End", "[opt][end]")
{
    SECTION("Empty")
    {
        SECTION("Const")
        {
            vec4<int>::type const v4;

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.end() == v4.begin());
        }

        SECTION("Non-const")
        {
            vec4<int>::type v4;

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.end() == v4.begin());
        }
    }

    SECTION("Non-empty")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 1;

        SECTION("Const")
        {
            vec4<int>::type const v4(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.end() != v4.begin());
            REQUIRE(*(v4.end() - 1) == v);
        }

        SECTION("Non-const")
        {
            vec4<int>::type v4(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.end() != v4.begin());
            REQUIRE(*(v4.end() - 1) == v);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Resize", "[opt][resize]")
{
    SECTION("Empty")
    {
        vec4<int>::type v4;
        vect<int>::type vr;

        SECTION("To zero")
        {
            std::size_t const r = 0;

            v4.resize(r);
            vr.resize(r);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == r);

            requireEqual(v4, vr);
        }

        SECTION("To non-zero")
        {
            std::size_t const r = 17;

            v4.resize(r);
            vr.resize(r);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == r);

            requireEqual(v4, vr);
        }
    }

    SECTION("Non-empty")
    {
        int const v = 7;
        std::size_t const s = 3;
        vec4<int>::type v4(s, v);
        vect<int>::type vr(s, v);

        SECTION("To zero")
        {
            std::size_t const r = 0;

            v4.resize(r);
            vr.resize(r);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == r);

            requireEqual(v4, vr);
        }

        SECTION("To non-zero")
        {
            std::size_t const r = 17;

            v4.resize(r);
            vr.resize(r);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == r);

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Reserve", "[opt][reserve]")
{
    SECTION("Empty")
    {
        vec4<int>::type v4;

        SECTION("To zero")
        {
            vec4<int>::type::size_type const r = 0;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == 0);
        }

        SECTION("To non-zero")
        {
            vec4<int>::type::size_type const r = 7;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == 0);
        }
    }

    SECTION("Non-empty")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 4;
        vec4<int>::type v4(s, v);

        SECTION("To zero")
        {
            vec4<int>::type::size_type const r = 0;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == s);
        }

        SECTION("To same")
        {
            vec4<int>::type::size_type const r = s;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == s);
        }

        SECTION("To more")
        {
            vec4<int>::type::size_type const r = s + 3;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == s);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Subscript operator", "[opt][operator][subscript]")
{
    int const arr[] = {0, 1, 2};
    std::size_t const s = num_elems(arr);

    SECTION("Const")
    {
        vec4<int>::type const v4(arr, arr + s);
        vect<int>::type const vr(arr, arr + s);

        requireEqual(v4, vr);
    }

    SECTION("Non-const")
    {
        vec4<int>::type v4(arr, arr + s);
        vect<int>::type const vr(arr, arr + s);

        requireEqual(v4, vr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("At", "[opt][at]")
{
    SECTION("Const")
    {
        SECTION("Empty")
        {
            vec4<int>::type const v4;

            REQUIRE_THROWS_AS(v4.at(0), std::out_of_range);
        }

        SECTION("Non-empty")
        {
            int const arr[] = {0, 1, 2};
            std::size_t const s = num_elems(arr);
            vec4<int>::type const v4(arr, arr + s);
            vect<int>::type const vr(arr, arr + s);

            requireEqual(v4, vr);

            REQUIRE_THROWS_AS(v4.at(s), std::out_of_range);
        }
    }

    SECTION("Non-const")
    {
        SECTION("Empty")
        {
            vec4<int>::type v4;

            REQUIRE_THROWS_AS(v4.at(0), std::out_of_range);
        }

        SECTION("Non-empty")
        {
            int const arr[] = {0, 1, 2};
            std::size_t const s = num_elems(arr);
            vec4<int>::type const v4(arr, arr + s);
            vect<int>::type const vr(arr, arr + s);

            requireEqual(v4, vr);

            REQUIRE_THROWS_AS(v4.at(s), std::out_of_range);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Front", "[opt][front]")
{
    int const f = 7;
    int const b = 11;
    int const arr[2] = {f, b};

    SECTION("Const")
    {
        vec4<int>::type const v4(arr, arr + 2);

        REQUIRE(v4.front() == f);
    }

    SECTION("Non-const")
    {
        vec4<int>::type v4(arr, arr + 2);

        REQUIRE(v4.front() == f);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Back", "[opt][back]")
{
    int const f = 7;
    int const b = 11;
    int const arr[2] = {f, b};

    SECTION("Const")
    {
        vec4<int>::type const v4(arr, arr + 2);

        REQUIRE(v4.back() == b);
    }

    SECTION("Non-const")
    {
        vec4<int>::type v4(arr, arr + 2);

        REQUIRE(v4.back() == b);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Range assign", "[opt][assign][range]")
{
    int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};

    SECTION("Empty")
    {
        vec4<int>::type v4;
        vect<int>::type vr;

        SECTION("Zero-range")
        {
            std::size_t const s = 0;

            v4.assign(arr, arr + s);
            vr.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("One-range")
        {
            std::size_t const s = 1;

            v4.assign(arr, arr + s);
            vr.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("Sixteen-range")
        {
            std::size_t const s = 16;

            v4.assign(arr, arr + s);
            vr.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }
    }

    SECTION("Non-empty")
    {
        int const v = 7;
        std::size_t const ss = 5;

        vec4<int>::type v4(ss, v);
        vect<int>::type vr(ss, v);

        SECTION("Zero-range")
        {
            std::size_t const s = 0;

            v4.assign(arr, arr + s);
            vr.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("One-range")
        {
            std::size_t const s = 1;

            v4.assign(arr, arr + s);
            vr.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("Sixteen-range")
        {
            std::size_t const s = 16;

            v4.assign(arr, arr + s);
            vr.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Fill assign", "[opt][assign][fill]")
{
    int const v = 7;

    SECTION("Empty")
    {
        vec4<int>::type v4;
        vect<int>::type vr;

        SECTION("Zero-size")
        {
            std::size_t const s = 0;

            v4.assign(s, v);
            vr.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("One-size")
        {
            std::size_t const s = 1;

            v4.assign(s, v);
            vr.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("Sixteen-size")
        {
            std::size_t const s = 16;

            v4.assign(s, v);
            vr.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }
    }

    SECTION("Non-empty")
    {
        int const vv = 11;
        std::size_t const ss = 5;

        vec4<int>::type v4(ss, vv);
        vect<int>::type vr(ss, vv);

        SECTION("Zero-size")
        {
            std::size_t const s = 0;

            v4.assign(s, v);
            vr.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("One-size")
        {
            std::size_t const s = 1;

            v4.assign(s, v);
            vr.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("Sixteen-size")
        {
            std::size_t const s = 16;

            v4.assign(s, v);
            vr.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Push back", "[opt][push back]")
{
    vec4<int>::type v4;
    vect<int>::type vr;

    for (int i = 1; i < 5; ++i)
    {
        v4.push_back(i);
        vr.push_back(i);
    }

    REQUIRE(v4.capacity() >= v4.size());

    requireEqual(v4, vr);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Pop back", "[opt][pop back]")
{
    int const arr[] = {0, 1, 2, 3};
    std::size_t const s = num_elems(arr);

    vec4<int>::type v4(arr, arr + s);
    vect<int>::type vr(arr, arr + s);

    while (!v4.empty())
    {
        v4.pop_back();
        vr.pop_back();

        REQUIRE(v4.capacity() >= v4.size());

        requireEqual(v4, vr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert single", "[opt][insert][single]")
{
    SECTION("Empty")
    {
        int const v1 = 7;
        int const v2 = 17;

        vec4<int>::type v4;
        vect<int>::type vr;

        SECTION("To begin")
        {
            v4.insert(v4.begin(), v1);
            vr.insert(vr.begin(), v1);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);

            v4.insert(v4.begin(), v2);
            vr.insert(vr.begin(), v2);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);
        }

        SECTION("To end")
        {
            v4.insert(v4.end(), v1);
            vr.insert(vr.end(), v1);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);

            v4.insert(v4.end(), v2);
            vr.insert(vr.end(), v2);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert fill", "[opt][insert][fill]")
{
    SECTION("Empty")
    {
        int const v1 = 7;
        int const v2 = 17;

        std::size_t n = 3;

        vec4<int>::type v4;
        vect<int>::type vr;

        SECTION("To begin")
        {
            v4.insert(v4.begin(), n, v1);
            vr.insert(vr.begin(), n, v1);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);

            v4.insert(v4.begin(), n, v2);
            vr.insert(vr.begin(), n, v2);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);
        }

        SECTION("To end")
        {
            v4.insert(v4.end(), n, v1);
            vr.insert(vr.end(), n, v1);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);

            v4.insert(v4.end(), n, v2);
            vr.insert(vr.end(), n, v2);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert raange", "[opt][insert][range]")
{
    SECTION("Empty")
    {
        int const v1 = 7;
        int const v2 = 17;

        std::size_t n = 3;

        vec4<int>::type v4;
        vect<int>::type vr;

        SECTION("To begin")
        {
            v4.insert(v4.begin(), n, v1);
            vr.insert(vr.begin(), n, v1);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);

            v4.insert(v4.begin(), n, v2);
            vr.insert(vr.begin(), n, v2);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);
        }

        SECTION("To end")
        {
            v4.insert(v4.end(), n, v1);
            vr.insert(vr.end(), n, v1);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);

            v4.insert(v4.end(), n, v2);
            vr.insert(vr.end(), n, v2);

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Erase single", "[opt][erase][single]")
{
    int const arr[] = {0, 1, 2, 3, 4};
    std::size_t const s = num_elems(arr);

    vec4<int>::type v4(arr, arr + s);
    vect<int>::type vr(arr, arr + s);

    SECTION("Front")
    {
        vec4<int>::type::iterator i = v4.erase(v4.begin());
        (void) vr.erase(vr.begin());

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.begin());

        requireEqual(v4, vr);
    }

    SECTION("Middle")
    {
        std::size_t const o = 2;
        vec4<int>::type::iterator i = v4.erase(v4.begin() + o);
        (void) vr.erase(vr.begin() + o);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.begin() + o);

        requireEqual(v4, vr);
    }

    SECTION("Back")
    {
        std::size_t const o = 4;
        vec4<int>::type::iterator i = v4.erase(v4.begin() + o);
        (void) vr.erase(vr.begin() + o);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.end());

        requireEqual(v4, vr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Erase range", "[opt][erase][range]")
{
    int const arr[] = {0, 1, 2, 3, 4};
    std::size_t const s = num_elems(arr);

    vec4<int>::type v4(arr, arr + s);
    vect<int>::type vr(arr, arr + s);

    SECTION("Front")
    {
        std::size_t const o = 2;
        vec4<int>::type::iterator i = v4.erase(v4.begin(), v4.begin() + o);
        (void) vr.erase(vr.begin(), vr.begin() + o);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.begin());

        requireEqual(v4, vr);
    }

    SECTION("Middle")
    {
        std::size_t const o1 = 2;
        std::size_t const o2 = 4;
        vec4<int>::type::iterator i = v4.erase(v4.begin() + o1, v4.begin() + o2);
        (void) vr.erase(vr.begin() + o1, vr.begin() + o2);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.begin() + 2);

        requireEqual(v4, vr);
    }

    SECTION("Back")
    {
        std::size_t const o = 4;
        vec4<int>::type::iterator i = v4.erase(v4.begin() + o, v4.end());
        (void) vr.erase(vr.begin() + o, vr.end());

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.end());

        requireEqual(v4, vr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Swap", "[opt][swap]")
{
    int const arr_a[] = {2, 3, 5, 7};
    int const arr_b[] = {11, 13, 17, 19, 23, 29, 31};

    vec4<int>::type v4_a(arr_a, arr_a + num_elems(arr_a));
    vec4<int>::type v4_b(arr_b, arr_b + num_elems(arr_b));

    vec4<int>::type::size_type s_a = v4_a.size();
    int const * ptr_a = &v4_a.front();
    vec4<int>::type::size_type s_b = v4_b.size();
    int const * ptr_b = &v4_b.front();

    v4_a.swap(v4_b);

    REQUIRE(v4_b.size() == s_a);
    REQUIRE(&v4_b.front() == ptr_a);
    REQUIRE(v4_a.size() == s_b);
    REQUIRE(&v4_a.front() == ptr_b);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Clear", "[opt][clear]")
{
    SECTION("Empty")
    {
        vec4<int>::type v4;

        v4.clear();

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == 0);
        REQUIRE(v4.empty());
    }

    SECTION("Non-empty")
    {
        int const arr[] = {0, 1, 2, 3};

        vec4<int>::type v4(arr, arr + num_elems(arr));

        v4.clear();

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == 0);
        REQUIRE(v4.empty());
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Empty", "[opt][empty]")
{
    SECTION("Empty")
    {
        vec4<int>::type v4;

        REQUIRE(v4.empty());
    }

    SECTION("Non-empty")
    {
        int const arr[] = {0, 1, 2, 3};

        vec4<int>::type v4(arr, arr + num_elems(arr));

        REQUIRE(!v4.empty());
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Size", "[opt][size]")
{
    int const v = 7;

    SECTION("Zero-size")
    {
        vec4<int>::type::size_type const s = 0;
        vec4<int>::type v4(s, v);

        REQUIRE(v4.size() == s);
    }

    SECTION("One-size")
    {
        vec4<int>::type::size_type const s = 1;
        vec4<int>::type v4(s, v);

        REQUIRE(v4.size() == s);
    }

    SECTION("Sixteen-size")
    {
        vec4<int>::type::size_type const s = 16;
        vec4<int>::type v4(s, v);

        REQUIRE(v4.size() == s);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Capacity", "[opt][capacity]")
{
    vec4<int>::type v4;

    SECTION("Zero")
    {
        vec4<int>::type::size_type const c = 0;

        v4.reserve(c);

        REQUIRE(v4.capacity() >= c);
    }

    SECTION("Non-zero")
    {
        vec4<int>::type::size_type const c = 7;

        v4.reserve(c);

        REQUIRE(v4.capacity() >= c);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Max size", "[opt][max size]")
{
    vec4<int>::type v4;

    REQUIRE(v4.max_size() >= 1);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Get allocator", "[opt][get allocator]")
{
    vec4<int>::type v4;
    vec4<int>::type::allocator_type a = v4.get_allocator();
    (void) a;
}
////////////////////////////////////////////////////////////////////////////////
