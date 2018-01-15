/*
    Copyright 2018 Krzysztof Karbowiak
*/

#include "catch/catch.hpp"

#include "vector_short_opt.h"

#include "util_num_elems.h"

#include <string>
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

typedef vec4<int>::type vec4i;
typedef vect<int>::type vecti;

typedef vec4<std::string>::type vec4s;
typedef vect<std::string>::type vects;


void requireEqual(vec4i const & v4, vecti const & vr)
{
    REQUIRE(v4.size() == vr.size());

    vec4i::size_type v4i = 0;
    vecti::size_type vri = 0;

    for (; v4i != v4.size() && vri != vr.size(); ++v4i, ++vri)
    {
        REQUIRE(v4[v4i] == vr[vri]);
    }
}

void requireEqual(vec4s const & v4, vects const & vr)
{
    REQUIRE(v4.size() == vr.size());

    vec4s::size_type v4s = 0;
    vects::size_type vrs = 0;

    for (; v4s != v4.size() && vrs != vr.size(); ++v4s, ++vrs)
    {
        REQUIRE(v4[v4s] == vr[vrs]);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Default ctor", "[opt][ctor][default]")
{
    SECTION("int")
    {
        vec4i const v4;

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == 0);
    }

    SECTION("std::string")
    {
        vec4s const v4;

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == 0);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Fill ctor", "[opt][ctor][fill]")
{
    SECTION("int")
    {
        int const v = 7;

        SECTION("Zero-size")
        {
            std::size_t const s = 0;
            vec4i const v4(s, v);
            vecti const vr(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("One-size")
        {
            std::size_t const s = 1;
            vec4i const v4(s, v);
            vecti const vr(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("Sixteen-size")
        {
            std::size_t const s = 16;
            vec4i const v4(s, v);
            vecti const vr(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }
    }

    SECTION("std::string")
    {
        std::string const v = "7";

        SECTION("Zero-size")
        {
            std::size_t const s = 0;
            vec4s const v4(s, v);
            vects const vr(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("One-size")
        {
            std::size_t const s = 1;
            vec4s const v4(s, v);
            vects const vr(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("Sixteen-size")
        {
            std::size_t const s = 16;
            vec4s const v4(s, v);
            vects const vr(s, v);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Range ctor", "[opt][ctor][range]")
{
    SECTION("int")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

        SECTION("Zero-range")
        {
            std::size_t const s = 0;
            vec4i const v4(arr, arr + s);
            vecti const vr(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("One-range")
        {
            std::size_t const s = 1;
            vec4i const v4(arr, arr + s);
            vecti const vr(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("Sixteen-range")
        {
            std::size_t const s = 16;
            vec4i const v4(arr, arr + s);
            vecti const vr(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }
    }

    SECTION("std::string")
    {
        std::string const arr[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

        SECTION("Zero-range")
        {
            std::size_t const s = 0;
            vec4s const v4(arr, arr + s);
            vects const vr(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("One-range")
        {
            std::size_t const s = 1;
            vec4s const v4(arr, arr + s);
            vects const vr(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }

        SECTION("Sixteen-range")
        {
            std::size_t const s = 16;
            vec4s const v4(arr, arr + s);
            vects const vr(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == s);

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Copy ctor", "[opt][ctor][copy]")
{
    SECTION("int")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

        SECTION("Zero-range")
        {
            std::size_t const s = 0;
            vec4i const ov4(arr, arr + s);
            vecti const ovr(arr, arr + s);

            vec4i const cv4(ov4);

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }

        SECTION("One-range")
        {
            std::size_t const s = 1;
            vec4i const ov4(arr, arr + s);
            vecti const ovr(arr, arr + s);

            vec4i const cv4(ov4);

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }

        SECTION("Sixteen-range")
        {
            std::size_t const s = 16;
            vec4i const ov4(arr, arr + s);
            vecti const ovr(arr, arr + s);

            vec4i const cv4(ov4);

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }
    }

    SECTION("std::string")
    {
        std::string const arr[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

        SECTION("Zero-range")
        {
            std::size_t const s = 0;
            vec4s const ov4(arr, arr + s);
            vects const ovr(arr, arr + s);

            vec4s const cv4(ov4);

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }

        SECTION("One-range")
        {
            std::size_t const s = 1;
            vec4s const ov4(arr, arr + s);
            vects const ovr(arr, arr + s);

            vec4s const cv4(ov4);

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }

        SECTION("Sixteen-range")
        {
            std::size_t const s = 16;
            vec4s const ov4(arr, arr + s);
            vects const ovr(arr, arr + s);

            vec4s const cv4(ov4);

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Copy assignment operator", "[opt][operator][copy][assignment]")
{
    SECTION("int")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

        SECTION("Zero-size")
        {
            vec4i::size_type const s = 0;
            vec4i const ov4(arr, arr + s);
            vecti const ovr(arr, arr + s);
            vec4i const dv4(arr + 2, arr + 5);

            vec4i cv4(dv4);

            cv4 = ov4;

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }

        SECTION("One-size")
        {
            vec4i::size_type const s = 1;
            vec4i const ov4(arr, arr + s);
            vecti const ovr(arr, arr + s);
            vec4i const dv4(arr + 2, arr + 5);

            vec4i cv4(dv4);

            cv4 = ov4;

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }

        SECTION("Sixteen-size")
        {
            vec4i::size_type const s = 16;
            vec4i const ov4(arr, arr + s);
            vecti const ovr(arr, arr + s);
            vec4i const dv4(arr + 2, arr + 5);

            vec4i cv4(dv4);

            cv4 = ov4;

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }
    }

    SECTION("std::string")
    {
        std::string const arr[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

        SECTION("Zero-size")
        {
            vec4s::size_type const s = 0;
            vec4s const ov4(arr, arr + s);
            vects const ovr(arr, arr + s);
            vec4s const dv4(arr + 2, arr + 5);

            vec4s cv4(dv4);

            cv4 = ov4;

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }

        SECTION("One-size")
        {
            vec4s::size_type const s = 1;
            vec4s const ov4(arr, arr + s);
            vects const ovr(arr, arr + s);
            vec4s const dv4(arr + 2, arr + 5);

            vec4s cv4(dv4);

            cv4 = ov4;

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }

        SECTION("Sixteen-size")
        {
            vec4s::size_type const s = 16;
            vec4s const ov4(arr, arr + s);
            vects const ovr(arr, arr + s);
            vec4s const dv4(arr + 2, arr + 5);

            vec4s cv4(dv4);

            cv4 = ov4;

            REQUIRE(cv4.capacity() >= cv4.size());
            REQUIRE(cv4.size() == s);

            requireEqual(cv4, ovr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Begin", "[opt][begin]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            SECTION("Const")
            {
                vec4i const v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.begin() == v4.end());
            }

            SECTION("Non-const")
            {
                vec4i v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.begin() == v4.end());
            }
        }

        SECTION("Non-empty")
        {
            int const v = 7;
            vec4i::size_type const s = 1;

            SECTION("Const")
            {
                vec4i const v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.begin() != v4.end());
                REQUIRE(*v4.begin() == v);
            }

            SECTION("Non-const")
            {
                vec4i v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.begin() != v4.end());
                REQUIRE(*v4.begin() == v);
            }
        }
    }

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            SECTION("Const")
            {
                vec4s const v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.begin() == v4.end());
            }

            SECTION("Non-const")
            {
                vec4s v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.begin() == v4.end());
            }
        }

        SECTION("Non-empty")
        {
            std::string const v = "7";
            vec4s::size_type const s = 1;

            SECTION("Const")
            {
                vec4s const v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.begin() != v4.end());
                REQUIRE(*v4.begin() == v);
            }

            SECTION("Non-const")
            {
                vec4s v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.begin() != v4.end());
                REQUIRE(*v4.begin() == v);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("End", "[opt][end]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            SECTION("Const")
            {
                vec4i const v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.end() == v4.begin());
            }

            SECTION("Non-const")
            {
                vec4i v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.end() == v4.begin());
            }
        }

        SECTION("Non-empty")
        {
            int const v = 7;
            vec4i::size_type const s = 1;

            SECTION("Const")
            {
                vec4i const v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.end() != v4.begin());
                REQUIRE(*(v4.end() - 1) == v);
            }

            SECTION("Non-const")
            {
                vec4i v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.end() != v4.begin());
                REQUIRE(*(v4.end() - 1) == v);
            }
        }
    }

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            SECTION("Const")
            {
                vec4s const v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.end() == v4.begin());
            }

            SECTION("Non-const")
            {
                vec4s v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.end() == v4.begin());
            }
        }

        SECTION("Non-empty")
        {
            std::string const v = "7";
            vec4s::size_type const s = 1;

            SECTION("Const")
            {
                vec4s const v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.end() != v4.begin());
                REQUIRE(*(v4.end() - 1) == v);
            }

            SECTION("Non-const")
            {
                vec4s v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.end() != v4.begin());
                REQUIRE(*(v4.end() - 1) == v);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Rbegin", "[opt][rbegin]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            SECTION("Const")
            {
                vec4i const v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rbegin() == v4.rend());
            }

            SECTION("Non-const")
            {
                vec4i v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rbegin() == v4.rend());
            }
        }

        SECTION("Non-empty")
        {
            int const v = 7;
            vec4i::size_type const s = 1;

            SECTION("Const")
            {
                vec4i const v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rbegin() != v4.rend());
                REQUIRE(*v4.rbegin() == v);
            }

            SECTION("Non-const")
            {
                vec4i v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rbegin() != v4.rend());
                REQUIRE(*v4.rbegin() == v);
            }
        }
    }

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            SECTION("Const")
            {
                vec4s const v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rbegin() == v4.rend());
            }

            SECTION("Non-const")
            {
                vec4s v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rbegin() == v4.rend());
            }
        }

        SECTION("Non-empty")
        {
            std::string const v = "7";
            vec4s::size_type const s = 1;

            SECTION("Const")
            {
                vec4s const v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rbegin() != v4.rend());
                REQUIRE(*v4.rbegin() == v);
            }

            SECTION("Non-const")
            {
                vec4s v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rbegin() != v4.rend());
                REQUIRE(*v4.rbegin() == v);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Rend", "[opt][rend]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            SECTION("Const")
            {
                vec4i const v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rend() == v4.rbegin());
            }

            SECTION("Non-const")
            {
                vec4i v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rend() == v4.rbegin());
            }
        }

        SECTION("Non-empty")
        {
            int const v = 7;
            vec4i::size_type const s = 1;

            SECTION("Const")
            {
                vec4i const v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rend() != v4.rbegin());
                REQUIRE(*(v4.rend() - 1) == v);
            }

            SECTION("Non-const")
            {
                vec4i v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rend() != v4.rbegin());
                REQUIRE(*(v4.rend() - 1) == v);
            }
        }
    }

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            SECTION("Const")
            {
                vec4s const v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rend() == v4.rbegin());
            }

            SECTION("Non-const")
            {
                vec4s v4;

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rend() == v4.rbegin());
            }
        }

        SECTION("Non-empty")
        {
            std::string const v = "7";
            vec4s::size_type const s = 1;

            SECTION("Const")
            {
                vec4s const v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rend() != v4.rbegin());
                REQUIRE(*(v4.rend() - 1) == v);
            }

            SECTION("Non-const")
            {
                vec4s v4(s, v);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.rend() != v4.rbegin());
                REQUIRE(*(v4.rend() - 1) == v);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Resize", "[opt][resize]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            vec4i v4;
            vecti vr;

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
            vec4i v4(s, v);
            vecti vr(s, v);

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

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            vec4s v4;
            vects vr;

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
            std::string const v = "7";
            std::size_t const s = 3;
            vec4s v4(s, v);
            vects vr(s, v);

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
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Reserve", "[opt][reserve]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            vec4i v4;

            SECTION("To zero")
            {
                vec4i::size_type const r = 0;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == 0);
            }

            SECTION("To non-zero")
            {
                vec4i::size_type const r = 7;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == 0);
            }
        }

        SECTION("Non-empty")
        {
            int const v = 7;
            vec4i::size_type const s = 4;
            vec4i v4(s, v);

            SECTION("To zero")
            {
                vec4i::size_type const r = 0;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == s);
            }

            SECTION("To same")
            {
                vec4i::size_type const r = s;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == s);
            }

            SECTION("To more")
            {
                vec4i::size_type const r = s + 3;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == s);
            }
        }
    }

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            vec4s v4;

            SECTION("To zero")
            {
                vec4s::size_type const r = 0;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == 0);
            }

            SECTION("To non-zero")
            {
                vec4s::size_type const r = 7;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == 0);
            }
        }

        SECTION("Non-empty")
        {
            std::string const v = "7";
            vec4s::size_type const s = 4;
            vec4s v4(s, v);

            SECTION("To zero")
            {
                vec4s::size_type const r = 0;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == s);
            }

            SECTION("To same")
            {
                vec4s::size_type const r = s;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == s);
            }

            SECTION("To more")
            {
                vec4s::size_type const r = s + 3;

                v4.reserve(r);

                REQUIRE(v4.capacity() >= v4.size());

                REQUIRE(v4.capacity() >= r);
                REQUIRE(v4.size() == s);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Subscript operator", "[opt][operator][subscript]")
{
    SECTION("int")
    {
        int const arr[] = {0, 1, 2};
        std::size_t const s = num_elems(arr);

        SECTION("Const")
        {
            vec4i const v4(arr, arr + s);
            vecti const vr(arr, arr + s);

            requireEqual(v4, vr);
        }

        SECTION("Non-const")
        {
            vec4i v4(arr, arr + s);
            vecti const vr(arr, arr + s);

            requireEqual(v4, vr);
        }
    }

    SECTION("std::string")
    {
        std::string const arr[] = {"0", "1", "2"};
        std::size_t const s = num_elems(arr);

        SECTION("Const")
        {
            vec4s const v4(arr, arr + s);
            vects const vr(arr, arr + s);

            requireEqual(v4, vr);
        }

        SECTION("Non-const")
        {
            vec4s v4(arr, arr + s);
            vects const vr(arr, arr + s);

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("At", "[opt][at]")
{
    SECTION("int")
    {
        SECTION("Const")
        {
            SECTION("Empty")
            {
                vec4i const v4;

                REQUIRE_THROWS_AS(v4.at(0), std::out_of_range);
            }

            SECTION("Non-empty")
            {
                int const arr[] = {0, 1, 2};
                std::size_t const s = num_elems(arr);
                vec4i const v4(arr, arr + s);
                vecti const vr(arr, arr + s);

                requireEqual(v4, vr);

                REQUIRE_THROWS_AS(v4.at(s), std::out_of_range);
            }
        }

        SECTION("Non-const")
        {
            SECTION("Empty")
            {
                vec4i v4;

                REQUIRE_THROWS_AS(v4.at(0), std::out_of_range);
            }

            SECTION("Non-empty")
            {
                int const arr[] = {0, 1, 2};
                std::size_t const s = num_elems(arr);
                vec4i const v4(arr, arr + s);
                vecti const vr(arr, arr + s);

                requireEqual(v4, vr);

                REQUIRE_THROWS_AS(v4.at(s), std::out_of_range);
            }
        }
    }

    SECTION("std::string")
    {
        SECTION("Const")
        {
            SECTION("Empty")
            {
                vec4s const v4;

                REQUIRE_THROWS_AS(v4.at(0), std::out_of_range);
            }

            SECTION("Non-empty")
            {
                std::string const arr[] = {"0", "1", "2"};
                std::size_t const s = num_elems(arr);
                vec4s const v4(arr, arr + s);
                vects const vr(arr, arr + s);

                requireEqual(v4, vr);

                REQUIRE_THROWS_AS(v4.at(s), std::out_of_range);
            }
        }

        SECTION("Non-const")
        {
            SECTION("Empty")
            {
                vec4s v4;

                REQUIRE_THROWS_AS(v4.at(0), std::out_of_range);
            }

            SECTION("Non-empty")
            {
                std::string const arr[] = {"0", "1", "2"};
                std::size_t const s = num_elems(arr);
                vec4s const v4(arr, arr + s);
                vects const vr(arr, arr + s);

                requireEqual(v4, vr);

                REQUIRE_THROWS_AS(v4.at(s), std::out_of_range);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Front", "[opt][front]")
{
    SECTION("int")
    {
        int const f = 7;
        int const b = 11;
        int const arr[2] = {f, b};

        SECTION("Const")
        {
            vec4i const v4(arr, arr + 2);

            REQUIRE(v4.front() == f);
        }

        SECTION("Non-const")
        {
            vec4i v4(arr, arr + 2);

            REQUIRE(v4.front() == f);
        }
    }

    SECTION("std::string")
    {
        std::string const f = "7";
        std::string const b = "11";
        std::string const arr[2] = {f, b};

        SECTION("Const")
        {
            vec4s const v4(arr, arr + 2);

            REQUIRE(v4.front() == f);
        }

        SECTION("Non-const")
        {
            vec4s v4(arr, arr + 2);

            REQUIRE(v4.front() == f);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Back", "[opt][back]")
{
    SECTION("int")
    {
        int const f = 7;
        int const b = 11;
        int const arr[2] = {f, b};

        SECTION("Const")
        {
            vec4i const v4(arr, arr + 2);

            REQUIRE(v4.back() == b);
        }

        SECTION("Non-const")
        {
            vec4i v4(arr, arr + 2);

            REQUIRE(v4.back() == b);
        }
    }

    SECTION("std::string")
    {
        std::string const f = "7";
        std::string const b = "11";
        std::string const arr[2] = {f, b};

        SECTION("Const")
        {
            vec4s const v4(arr, arr + 2);

            REQUIRE(v4.back() == b);
        }

        SECTION("Non-const")
        {
            vec4s v4(arr, arr + 2);

            REQUIRE(v4.back() == b);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Range assign", "[opt][assign][range]")
{
    SECTION("int")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

        SECTION("Empty")
        {
            vec4i v4;
            vecti vr;

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

            vec4i v4(ss, v);
            vecti vr(ss, v);

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

    SECTION("std::string")
    {
        std::string const arr[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

        SECTION("Empty")
        {
            vec4s v4;
            vects vr;

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
            std::string const v = "7";
            std::size_t const ss = 5;

            vec4s v4(ss, v);
            vects vr(ss, v);

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
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Fill assign", "[opt][assign][fill]")
{
    SECTION("int")
    {
        int const v = 7;

        SECTION("Empty")
        {
            vec4i v4;
            vecti vr;

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

            vec4i v4(ss, vv);
            vecti vr(ss, vv);

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

    SECTION("std::string")
    {
        std::string const v = "7";

        SECTION("Empty")
        {
            vec4s v4;
            vects vr;

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
            std::string const vv = "11";
            std::size_t const ss = 5;

            vec4s v4(ss, vv);
            vects vr(ss, vv);

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
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Push back", "[opt][push back]")
{
    SECTION("int")
    {
        vec4i v4;
        vecti vr;

        for (int i = 1; i < 5; ++i)
        {
            v4.push_back(i);
            vr.push_back(i);
        }

        REQUIRE(v4.capacity() >= v4.size());

        requireEqual(v4, vr);
    }

    SECTION("std::string")
    {
        vec4s v4;
        vects vr;

        for (int i = 1; i < 5; ++i)
        {
            std::ostringstream ostr;
            ostr << i;

            v4.push_back(ostr.str());
            vr.push_back(ostr.str());
        }

        REQUIRE(v4.capacity() >= v4.size());

        requireEqual(v4, vr);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Pop back", "[opt][pop back]")
{
    SECTION("int")
    {
        int const arr[] = {0, 1, 2, 3};
        std::size_t const s = num_elems(arr);

        vec4i v4(arr, arr + s);
        vecti vr(arr, arr + s);

        while (!v4.empty())
        {
            v4.pop_back();
            vr.pop_back();

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);
        }
    }

    SECTION("std::string")
    {
        std::string const arr[] = {"0", "1", "2", "3"};
        std::size_t const s = num_elems(arr);

        vec4s v4(arr, arr + s);
        vects vr(arr, arr + s);

        while (!v4.empty())
        {
            v4.pop_back();
            vr.pop_back();

            REQUIRE(v4.capacity() >= v4.size());

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert single", "[opt][insert][single]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            int const v1 = 7;
            int const v2 = 17;

            vec4i v4;
            vecti vr;

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

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            std::string const v1 = "7";
            std::string const v2 = "17";

            vec4s v4;
            vects vr;

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
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert fill", "[opt][insert][fill]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            int const v1 = 7;
            int const v2 = 17;

            std::size_t n = 3;

            vec4i v4;
            vecti vr;

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

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            std::string const v1 = "7";
            std::string const v2 = "17";

            std::size_t n = 3;

            vec4s v4;
            vects vr;

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
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert raange", "[opt][insert][range]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            int const v1 = 7;
            int const v2 = 17;

            std::size_t n = 3;

            vec4i v4;
            vecti vr;

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

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            std::string const v1 = "7";
            std::string const v2 = "17";

            std::size_t n = 3;

            vec4s v4;
            vects vr;

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
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Erase single", "[opt][erase][single]")
{
    SECTION("int")
    {
        int const arr[] = {0, 1, 2, 3, 4};
        std::size_t const s = num_elems(arr);

        vec4i v4(arr, arr + s);
        vecti vr(arr, arr + s);

        SECTION("Front")
        {
            vec4i::iterator i = v4.erase(v4.begin());
            (void) vr.erase(vr.begin());

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.begin());

            requireEqual(v4, vr);
        }

        SECTION("Middle")
        {
            std::size_t const o = 2;
            vec4i::iterator i = v4.erase(v4.begin() + o);
            (void) vr.erase(vr.begin() + o);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.begin() + o);

            requireEqual(v4, vr);
        }

        SECTION("Back")
        {
            std::size_t const o = 4;
            vec4i::iterator i = v4.erase(v4.begin() + o);
            (void) vr.erase(vr.begin() + o);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.end());

            requireEqual(v4, vr);
        }
    }

    SECTION("std::string")
    {
        std::string const arr[] = {"0", "1", "2", "3", "4"};
        std::size_t const s = num_elems(arr);

        vec4s v4(arr, arr + s);
        vects vr(arr, arr + s);

        SECTION("Front")
        {
            vec4s::iterator i = v4.erase(v4.begin());
            (void) vr.erase(vr.begin());

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.begin());

            requireEqual(v4, vr);
        }

        SECTION("Middle")
        {
            std::size_t const o = 2;
            vec4s::iterator i = v4.erase(v4.begin() + o);
            (void) vr.erase(vr.begin() + o);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.begin() + o);

            requireEqual(v4, vr);
        }

        SECTION("Back")
        {
            std::size_t const o = 4;
            vec4s::iterator i = v4.erase(v4.begin() + o);
            (void) vr.erase(vr.begin() + o);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.end());

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Erase range", "[opt][erase][range]")
{
    SECTION("int")
    {
        int const arr[] = {0, 1, 2, 3, 4};
        std::size_t const s = num_elems(arr);

        vec4i v4(arr, arr + s);
        vecti vr(arr, arr + s);

        SECTION("Front")
        {
            std::size_t const o = 2;
            vec4i::iterator i = v4.erase(v4.begin(), v4.begin() + o);
            (void) vr.erase(vr.begin(), vr.begin() + o);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.begin());

            requireEqual(v4, vr);
        }

        SECTION("Middle")
        {
            std::size_t const o1 = 2;
            std::size_t const o2 = 4;
            vec4i::iterator i = v4.erase(v4.begin() + o1, v4.begin() + o2);
            (void) vr.erase(vr.begin() + o1, vr.begin() + o2);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.begin() + 2);

            requireEqual(v4, vr);
        }

        SECTION("Back")
        {
            std::size_t const o = 4;
            vec4i::iterator i = v4.erase(v4.begin() + o, v4.end());
            (void) vr.erase(vr.begin() + o, vr.end());

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.end());

            requireEqual(v4, vr);
        }
    }

    SECTION("std::string")
    {
        std::string const arr[] = {"0", "1", "2", "3", "4"};
        std::size_t const s = num_elems(arr);

        vec4s v4(arr, arr + s);
        vects vr(arr, arr + s);

        SECTION("Front")
        {
            std::size_t const o = 2;
            vec4s::iterator i = v4.erase(v4.begin(), v4.begin() + o);
            (void) vr.erase(vr.begin(), vr.begin() + o);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.begin());

            requireEqual(v4, vr);
        }

        SECTION("Middle")
        {
            std::size_t const o1 = 2;
            std::size_t const o2 = 4;
            vec4s::iterator i = v4.erase(v4.begin() + o1, v4.begin() + o2);
            (void) vr.erase(vr.begin() + o1, vr.begin() + o2);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.begin() + 2);

            requireEqual(v4, vr);
        }

        SECTION("Back")
        {
            std::size_t const o = 4;
            vec4s::iterator i = v4.erase(v4.begin() + o, v4.end());
            (void) vr.erase(vr.begin() + o, vr.end());

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(i == v4.end());

            requireEqual(v4, vr);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Clear", "[opt][clear]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            vec4i v4;

            v4.clear();

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == 0);
            REQUIRE(v4.empty());
        }

        SECTION("Non-empty")
        {
            int const arr[] = {0, 1, 2, 3};

            vec4i v4(arr, arr + num_elems(arr));

            v4.clear();

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == 0);
            REQUIRE(v4.empty());
        }
    }

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            vec4s v4;

            v4.clear();

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == 0);
            REQUIRE(v4.empty());
        }

        SECTION("Non-empty")
        {
            std::string const arr[] = {"0", "1", "2", "3"};

            vec4s v4(arr, arr + num_elems(arr));

            v4.clear();

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == 0);
            REQUIRE(v4.empty());
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Empty", "[opt][empty]")
{
    SECTION("int")
    {
        SECTION("Empty")
        {
            vec4i v4;

            REQUIRE(v4.empty());
        }

        SECTION("Non-empty")
        {
            int const arr[] = {0, 1, 2, 3};

            vec4i v4(arr, arr + num_elems(arr));

            REQUIRE(!v4.empty());
        }
    }

    SECTION("std::string")
    {
        SECTION("Empty")
        {
            vec4s v4;

            REQUIRE(v4.empty());
        }

        SECTION("Non-empty")
        {
            std::string const arr[] = {"0", "1", "2", "3"};

            vec4s v4(arr, arr + num_elems(arr));

            REQUIRE(!v4.empty());
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Size", "[opt][size]")
{
    SECTION("int")
    {
        int const v = 7;

        SECTION("Zero-size")
        {
            vec4i::size_type const s = 0;
            vec4i v4(s, v);

            REQUIRE(v4.size() == s);
        }

        SECTION("One-size")
        {
            vec4i::size_type const s = 1;
            vec4i v4(s, v);

            REQUIRE(v4.size() == s);
        }

        SECTION("Sixteen-size")
        {
            vec4i::size_type const s = 16;
            vec4i v4(s, v);

            REQUIRE(v4.size() == s);
        }
    }

    SECTION("std::string")
    {
        std::string const v = "7";

        SECTION("Zero-size")
        {
            vec4s::size_type const s = 0;
            vec4s v4(s, v);

            REQUIRE(v4.size() == s);
        }

        SECTION("One-size")
        {
            vec4s::size_type const s = 1;
            vec4s v4(s, v);

            REQUIRE(v4.size() == s);
        }

        SECTION("Sixteen-size")
        {
            vec4s::size_type const s = 16;
            vec4s v4(s, v);

            REQUIRE(v4.size() == s);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Capacity", "[opt][capacity]")
{
    SECTION("int")
    {
        vec4i v4;

        SECTION("Zero")
        {
            vec4i::size_type const c = 0;

            v4.reserve(c);

            REQUIRE(v4.capacity() >= c);
        }

        SECTION("Non-zero")
        {
            vec4i::size_type const c = 7;

            v4.reserve(c);

            REQUIRE(v4.capacity() >= c);
        }
    }

    SECTION("std::string")
    {
        vec4s v4;

        SECTION("Zero")
        {
            vec4s::size_type const c = 0;

            v4.reserve(c);

            REQUIRE(v4.capacity() >= c);
        }

        SECTION("Non-zero")
        {
            vec4s::size_type const c = 7;

            v4.reserve(c);

            REQUIRE(v4.capacity() >= c);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Max size", "[opt][max size]")
{
    SECTION("int")
    {
        vec4i v4;

        REQUIRE(v4.max_size() >= 1);
    }

    SECTION("std::string")
    {
        vec4s v4;

        REQUIRE(v4.max_size() >= 1);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Get allocator", "[opt][get allocator]")
{
    SECTION("int")
    {
        vec4i v4;
        vec4i::allocator_type a = v4.get_allocator();
        (void) a;
    }

    SECTION("std::string")
    {
        vec4s v4;
        vec4s::allocator_type a = v4.get_allocator();
        (void) a;
    }
}
////////////////////////////////////////////////////////////////////////////////
