#include "catch/catch.hpp"

#include "vector_short_opt.h"

#include <stdexcept>


template<typename T>
struct vec4
{
    typedef opt::vector_short_opt<T, 4> type;
};

template<typename T>
bool requireEqual(vec4<T> const v4, std::vector<T> const vr)
{
    REQUIRE(v4.size() == vr.size());

    vec4<T>::size_type v4i = 0;
    std::vector<T>::size_type vri = 0;

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
    SECTION("Zero-size")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 0;
        vec4<int>::type const v4(s, v);

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
        {
            REQUIRE(v4[i] == v);
        }
    }

    SECTION("One-size")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 1;
        vec4<int>::type const v4(s, v);

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
        {
            REQUIRE(v4[i] == v);
        }
    }

    SECTION("Sixteen-size")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 16;
        vec4<int>::type const v4(s, v);

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
        {
            REQUIRE(v4[i] == v);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Range ctor", "[opt][ctor][range]")
{
    SECTION("Zero-range")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 0;
        vec4<int>::type const v4(arr, arr + s);

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
        {
            REQUIRE(v4[i] == arr[i]);
        }
    }

    SECTION("One-range")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 1;
        vec4<int>::type const v4(arr, arr + s);

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
        {
            REQUIRE(v4[i] == arr[i]);
        }
    }

    SECTION("Sixteen-range")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 16;
        vec4<int>::type const v4(arr, arr + s);

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
        {
            REQUIRE(v4[i] == arr[i]);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Copy ctor", "[opt][ctor][copy]")
{
    SECTION("Zero-range")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 0;
        vec4<int>::type const ov4(arr, arr + s);

        vec4<int>::type const cv4(ov4);

        REQUIRE(cv4.capacity() >= cv4.size());

        REQUIRE(cv4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < cv4.size(); ++i)
        {
            REQUIRE(cv4[i] == ov4[i]);
        }
    }

    SECTION("One-range")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 1;
        vec4<int>::type const ov4(arr, arr + s);

        vec4<int>::type const cv4(ov4);

        REQUIRE(cv4.capacity() >= cv4.size());

        REQUIRE(cv4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < cv4.size(); ++i)
        {
            REQUIRE(cv4[i] == ov4[i]);
        }
    }

    SECTION("Sixteen-range")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 16;
        vec4<int>::type const ov4(arr, arr + s);

        vec4<int>::type const cv4(ov4);

        REQUIRE(cv4.capacity() >= cv4.size());

        REQUIRE(cv4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < cv4.size(); ++i)
        {
            REQUIRE(cv4[i] == ov4[i]);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Copy assignment operator", "[opt][operator][copy][assignment]")
{
    SECTION("Zero-size")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 0;
        vec4<int>::type const ov4(arr, arr + s);
        vec4<int>::type const dv4(arr + 2, arr + 5);

        vec4<int>::type cv4(dv4);

        cv4 = ov4;

        REQUIRE(cv4.capacity() >= cv4.size());

        REQUIRE(cv4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < cv4.size(); ++i)
        {
            REQUIRE(cv4[i] == ov4[i]);
        }
    }

    SECTION("One-size")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 1;
        vec4<int>::type const ov4(arr, arr + s);
        vec4<int>::type const dv4(arr + 2, arr + 5);

        vec4<int>::type cv4(dv4);

        cv4 = ov4;

        REQUIRE(cv4.capacity() >= cv4.size());

        REQUIRE(cv4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < cv4.size(); ++i)
        {
            REQUIRE(cv4[i] == ov4[i]);
        }
    }

    SECTION("Sixteen-size")
    {
        int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
        vec4<int>::type::size_type const s = 16;
        vec4<int>::type const ov4(arr, arr + s);
        vec4<int>::type const dv4(arr + 2, arr + 5);

        vec4<int>::type cv4(dv4);

        cv4 = ov4;

        REQUIRE(cv4.capacity() >= cv4.size());

        REQUIRE(cv4.size() == s);
        for (vec4<int>::type::size_type i = 0; i < cv4.size(); ++i)
        {
            REQUIRE(cv4[i] == ov4[i]);
        }
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
        SECTION("Const")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 1;
            vec4<int>::type const v4(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.begin() != v4.end());
            REQUIRE(*v4.begin() == v);
        }

        SECTION("Non-const")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 1;
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
        SECTION("Const")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 1;
            vec4<int>::type const v4(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.end() != v4.begin());
            REQUIRE(*(v4.end() - 1) == v);
        }

        SECTION("Non-const")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 1;
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
        SECTION("To zero")
        {
            vec4<int>::type v4;
            vec4<int>::type::size_type const r = 0;

            v4.resize(r);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == r);
        }

        SECTION("To non-zero")
        {
            vec4<int>::type v4;
            vec4<int>::type::size_type const r = 17;

            v4.resize(r);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == r);
        }
    }

    SECTION("Non-empty")
    {
        SECTION("To zero")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 3;
            vec4<int>::type v4(s, v);
            vec4<int>::type::size_type const r = 0;

            v4.resize(r);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == r);
        }

        SECTION("To non-zero")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 3;
            vec4<int>::type v4(s, v);
            vec4<int>::type::size_type const r = 17;

            v4.resize(r);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == r);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Reserve", "[opt][reserve]")
{
    SECTION("Empty")
    {
        SECTION("To zero")
        {
            vec4<int>::type v4;
            vec4<int>::type::size_type const r = 0;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == 0);
        }

        SECTION("To non-zero")
        {
            vec4<int>::type v4;
            vec4<int>::type::size_type const r = 7;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == 0);
        }
    }

    SECTION("Non-empty")
    {
        SECTION("To zero")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 4;
            vec4<int>::type v4(s, v);
            vec4<int>::type::size_type const r = 0;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == s);
        }

        SECTION("To same")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 4;
            vec4<int>::type v4(s, v);
            vec4<int>::type::size_type const r = s;

            v4.reserve(r);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.capacity() >= r);
            REQUIRE(v4.size() == s);
        }

        SECTION("To more")
        {
            int const v = 7;
            vec4<int>::type::size_type const s = 4;
            vec4<int>::type v4(s, v);
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
    SECTION("Const")
    {
        int const arr[3] = {0, 1, 2};
        vec4<int>::type const v4(arr, arr + 3);

        for (vec4<int>::type::size_type i = 0; i < 3; ++i)
        {
            REQUIRE(v4[i] == arr[i]);
        }
    }

    SECTION("Non-const")
    {
        int const arr[3] = {0, 1, 2};
        vec4<int>::type v4(arr, arr + 3);

        for (vec4<int>::type::size_type i = 0; i < 3; ++i)
        {
            REQUIRE(v4[i] == arr[i]);
        }
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
            int const arr[3] = {0, 1, 2};
            vec4<int>::type const v4(arr, arr + 3);

            vec4<int>::type::size_type i = 0;

            for (; i < 3; ++i)
            {
                REQUIRE(v4[i] == arr[i]);
            }

            REQUIRE_THROWS_AS(v4.at(i), std::out_of_range);
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
            int const arr[3] = {0, 1, 2};
            vec4<int>::type v4(arr, arr + 3);

            vec4<int>::type::size_type i = 0;

            for (; i < 3; ++i)
            {
                REQUIRE(v4[i] == arr[i]);
            }

            REQUIRE_THROWS_AS(v4.at(i), std::out_of_range);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Front", "[opt][front]")
{
    SECTION("Const")
    {
        int const f = 7;
        int const b = 11;
        int const arr[2] = {f, b};
        vec4<int>::type const v4(arr, arr + 2);

        REQUIRE(v4.front() == f);
    }

    SECTION("Non-const")
    {
        int const f = 7;
        int const b = 11;
        int const arr[2] = {f, b};
        vec4<int>::type v4(arr, arr + 2);

        REQUIRE(v4.front() == f);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Back", "[opt][back]")
{
    SECTION("Const")
    {
        int const f = 7;
        int const b = 11;
        int const arr[2] = {f, b};
        vec4<int>::type const v4(arr, arr + 2);

        REQUIRE(v4.back() == b);
    }

    SECTION("Non-const")
    {
        int const f = 7;
        int const b = 11;
        int const arr[2] = {f, b};
        vec4<int>::type v4(arr, arr + 2);

        REQUIRE(v4.back() == b);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Range assign", "[opt][assign][range]")
{
    SECTION("Empty")
    {
        SECTION("Zero-range")
        {
            vec4<int>::type v4;

            int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
            vec4<int>::type::size_type const s = 0;

            v4.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == s);
            for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
            {
                REQUIRE(v4[i] == arr[i]);
            }
        }

        SECTION("One-range")
        {
            vec4<int>::type v4;

            int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
            vec4<int>::type::size_type const s = 1;

            v4.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == s);
            for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
            {
                REQUIRE(v4[i] == arr[i]);
            }
        }

        SECTION("Sixteen-range")
        {
            vec4<int>::type v4;

            int const arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14, 15};
            vec4<int>::type::size_type const s = 16;

            v4.assign(arr, arr + s);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == s);
            for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
            {
                REQUIRE(v4[i] == arr[i]);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Fill assign", "[opt][assign][fill]")
{
    SECTION("Empty")
    {
        SECTION("Zero-size")
        {
            vec4<int>::type v4;

            int const v = 7;
            vec4<int>::type::size_type const s = 0;

            v4.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == s);
            for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
            {
                REQUIRE(v4[i] == v);
            }
        }

        SECTION("One-size")
        {
            vec4<int>::type v4;

            int const v = 7;
            vec4<int>::type::size_type const s = 1;

            v4.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == s);
            for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
            {
                REQUIRE(v4[i] == v);
            }
        }

        SECTION("Sixteen-size")
        {
            vec4<int>::type v4;

            int const v = 7;
            vec4<int>::type::size_type const s = 16;

            v4.assign(s, v);

            REQUIRE(v4.capacity() >= v4.size());

            REQUIRE(v4.size() == s);
            for (vec4<int>::type::size_type i = 0; i < v4.size(); ++i)
            {
                REQUIRE(v4[i] == v);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Push back", "[opt][push back]")
{
    int const arr[4] = {0, 1, 2, 3};

    vec4<int>::type v4;

    for (vec4<int>::type::size_type i = 0; i < 4; ++i)
    {
        v4.push_back(arr[i]);

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == i + 1);
        REQUIRE(v4[i] == arr[i]);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Pop back", "[opt][pop back]")
{
    int const arr[4] = {0, 1, 2, 3};

    vec4<int>::type v4(arr, arr + 4);

    for (vec4<int>::type::size_type i = 0; i < 4; ++i)
    {
        REQUIRE(v4.back() == arr[3 - i]);

        v4.pop_back();

        REQUIRE(v4.capacity() >= v4.size());

        REQUIRE(v4.size() == 3 - i);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert single", "[opt][insert][single]")
{
    SECTION("Empty")
    {
        SECTION("To begin")
        {
            int const v1 = 7;

            vec4<int>::type v4;

            v4.insert(v4.begin(), v1);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == 1);
            REQUIRE(v4.front() == v1);

            int const v2 = 17;

            v4.insert(v4.begin(), v2);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == 2);
            REQUIRE(v4.front() == v2);
        }

        SECTION("To end")
        {
            int const v1 = 7;

            vec4<int>::type v4;

            v4.insert(v4.end(), v1);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == 1);
            REQUIRE(v4.back() == v1);

            int const v2 = 17;

            v4.insert(v4.end(), v2);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == 2);
            REQUIRE(v4.back() == v2);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert fill", "[opt][insert][fill]")
{
    SECTION("Empty")
    {
        SECTION("To begin")
        {
            int const v1 = 7;
            vec4<int>::type::size_type n = 3;

            vec4<int>::type v4;

            v4.insert(v4.begin(), n, v1);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == n);
            REQUIRE(v4[0] == v1);
            REQUIRE(v4[1] == v1);
            REQUIRE(v4[2] == v1);

            int const v2 = 17;

            v4.insert(v4.begin(), n, v2);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == 6);
            REQUIRE(v4[0] == v2);
            REQUIRE(v4[1] == v2);
            REQUIRE(v4[2] == v2);
        }

        SECTION("To end")
        {
            int const v1 = 7;
            vec4<int>::type::size_type n = 3;

            vec4<int>::type v4;

            v4.insert(v4.end(), n, v1);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == n);
            REQUIRE(v4[0] == v1);
            REQUIRE(v4[1] == v1);
            REQUIRE(v4[2] == v1);

            int const v2 = 17;

            v4.insert(v4.end(), n, v2);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == 6);
            REQUIRE(v4[3] == v2);
            REQUIRE(v4[4] == v2);
            REQUIRE(v4[5] == v2);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Insert raange", "[opt][insert][range]")
{
    SECTION("Empty")
    {
        SECTION("To begin")
        {
            int const v1 = 7;
            vec4<int>::type::size_type n = 3;

            vec4<int>::type v4;

            v4.insert(v4.begin(), n, v1);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == n);
            REQUIRE(v4[0] == v1);
            REQUIRE(v4[1] == v1);
            REQUIRE(v4[2] == v1);

            int const v2 = 17;

            v4.insert(v4.begin(), n, v2);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == 6);
            REQUIRE(v4[0] == v2);
            REQUIRE(v4[1] == v2);
            REQUIRE(v4[2] == v2);
        }

        SECTION("To end")
        {
            int const v1 = 7;
            vec4<int>::type::size_type n = 3;

            vec4<int>::type v4;

            v4.insert(v4.end(), n, v1);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == n);
            REQUIRE(v4[0] == v1);
            REQUIRE(v4[1] == v1);
            REQUIRE(v4[2] == v1);

            int const v2 = 17;

            v4.insert(v4.end(), n, v2);

            REQUIRE(v4.capacity() >= v4.size());
            REQUIRE(v4.size() == 6);
            REQUIRE(v4[3] == v2);
            REQUIRE(v4[4] == v2);
            REQUIRE(v4[5] == v2);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Erase single", "[opt][erase][single]")
{
    SECTION("Front")
    {
        int const arr[5] = {0, 1, 2, 3, 4};
        vec4<int>::type::size_type const s = 5;
        vec4<int>::type v4(arr, arr + s);

        vec4<int>::type::iterator i = v4.erase(v4.begin());

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.begin());
        REQUIRE(*i == 1);
    }

    SECTION("Middle")
    {
        int const arr[5] = {0, 1, 2, 3, 4};
        vec4<int>::type::size_type const s = 5;
        vec4<int>::type v4(arr, arr + s);

        vec4<int>::type::iterator i = v4.erase(v4.begin() + 2);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.begin() + 2);
        REQUIRE(*i == 3);
    }

    SECTION("Back")
    {
        int const arr[5] = {0, 1, 2, 3, 4};
        vec4<int>::type::size_type const s = 5;
        vec4<int>::type v4(arr, arr + s);

        vec4<int>::type::iterator i = v4.erase(v4.begin() + 4);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.end());
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Erase range", "[opt][erase][range]")
{
    SECTION("Front")
    {
        int const arr[5] = {0, 1, 2, 3, 4};
        vec4<int>::type::size_type const s = 5;
        vec4<int>::type v4(arr, arr + s);

        vec4<int>::type::iterator i = v4.erase(v4.begin(), v4.begin() + 2);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.begin());
        REQUIRE(*i == 2);
    }

    SECTION("Middle")
    {
        int const arr[5] = {0, 1, 2, 3, 4};
        vec4<int>::type::size_type const s = 5;
        vec4<int>::type v4(arr, arr + s);

        vec4<int>::type::iterator i = v4.erase(v4.begin() + 2, v4.begin() + 4);

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.begin() + 2);
        REQUIRE(*i == 4);
    }

    SECTION("Back")
    {
        int const arr[5] = {0, 1, 2, 3, 4};
        vec4<int>::type::size_type const s = 5;
        vec4<int>::type v4(arr, arr + s);

        vec4<int>::type::iterator i = v4.erase(v4.begin() + 4, v4.end());

        REQUIRE(v4.capacity() >= v4.size());
        REQUIRE(i == v4.end());
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Swap", "[opt][swap]")
{
    int const arr_a[4] = {2, 3, 5, 7};
    int const arr_b[7] = {11, 13, 17, 19, 23, 29, 31};

    vec4<int>::type v4_a(arr_a, arr_a + 4);
    vec4<int>::type v4_b(arr_b, arr_b + 7);

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
        int const arr[4] = {0, 1, 2, 3};

        vec4<int>::type v4(arr, arr + 4);

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
        int const arr[4] = {0, 1, 2, 3};

        vec4<int>::type v4(arr, arr + 4);

        REQUIRE(!v4.empty());
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Size", "[opt][size]")
{
    SECTION("Zero-size")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 0;
        vec4<int>::type v4(s, v);

        REQUIRE(v4.size() == s);
    }

    SECTION("One-size")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 1;
        vec4<int>::type v4(s, v);

        REQUIRE(v4.size() == s);
    }

    SECTION("Sixteen-size")
    {
        int const v = 7;
        vec4<int>::type::size_type const s = 16;
        vec4<int>::type v4(s, v);

        REQUIRE(v4.size() == s);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Capacity", "[opt][capacity]")
{
    SECTION("Zero")
    {
        vec4<int>::type v4;
        vec4<int>::type::size_type const c = 0;

        v4.reserve(c);

        REQUIRE(v4.capacity() >= c);
    }

    SECTION("Non-zero")
    {
        vec4<int>::type v4;
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
