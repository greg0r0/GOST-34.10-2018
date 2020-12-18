#ifndef UTIL_HPP
#define UTIL_HPP

namespace Util {

    template <typename T>
    class Math {
    public:
        class AffinePoint
        {
            public:
                T x;
                T y;
                T z;
            
                AffinePoint(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
        };



        static T gcd(T a, T b){
            while (b != 0)
            {
                T r = a % b;
                a = b;
                b = r;
            }

            return a;
        }

    };
}

#endif