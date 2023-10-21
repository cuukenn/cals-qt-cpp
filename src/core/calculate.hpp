#pragma once
#include <math.h>
#include <map>
#include <string>
using namespace std;
namespace calculate
{
    template <typename T>
    T returnSelf(T x)
    {
        return x;
    }
    template <typename T>
    T moveRight(T x)
    {
        return x / 10;
    }
    template <typename T>
    T inverse(T x)
    {
        return -1 * x;
    }
    template <typename T>
    T reciprocal(T x)
    {
        return 1 / x;
    }
    template <typename T>
    T square(T x)
    {
        return x * x;
    }
    template <typename T>
    T xsqrt(T x)
    {
        return sqrt(x);
    }
    template <typename T>
    T add(T left, T right)
    {
        return left + right;
    }
    template <typename T>
    T sub(T left, T right)
    {
        return left - right;
    }
    template <typename T>
    T mul(T left, T right)
    {
        return left * right;
    }
    template <typename T>
    T xmod(T left, T right)
    {
        if (right == 0)
        {
            return 0;
        }
#ifdef CALS_CONTEXT_TYPE_FLOAT
        return modf(left, &right);
#else
        return left % right;
#endif
    }
    template <typename T>
    T div(T left, T right)
    {
        if (right == 0)
        {
            return 0;
        }
        return left / right;
    }
}
