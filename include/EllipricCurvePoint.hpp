#ifndef ELLIPTIC_CURVE_POINT_HPP
#define ELLIPTIC_CURVE_POINT_HPP

#include "MathUtil.hpp"
namespace ECC
{

    template <typename T>
    class EllipticPoint{
    private:
        T x;
        T y;
        T modulo;
    public:

        EllipticPoint(T _x, T _y, T _mod) : x(_x), y(_y), modulo(_mod){}
    };

} 

#endif