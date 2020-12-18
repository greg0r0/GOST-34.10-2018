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

        /*
            c++ operation% is shitty ._. (for Z/Zp)
        */
        static T mod(T a, T p){
            T res = a % p;
            return (res<0)?res+p:res;
        }
        
        /*
            compute y == a^x (mod p)
            return y
        */
        static T pow_finite(T a, T x, T p){
            T aa = (a>=0? ( a>=p ? a - p : a) :a + p);
            T res = (T)pow(aa,x) % p;
            return p>0 ? res : res + p;
        }

        static T gcd(T a, T b){
            while (b != 0)
            {
                T r = a % b;
                a = b;
                b = r;
            }

            return a;
        }

        /*
            au+bv=gcd(a,b)
            res.x = gcd(a,b), res.y = u, res.z = v 
        */
        static AffinePoint extended_gcd(int a, int b){
            AffinePoint U(a, 1, 0);
            AffinePoint V(b, 0, 1);
            while (V.x != 0){
                int q = U.x / V.x;
                AffinePoint Tmp(U.x % V.x,  U.y - q * V.y, U.z - q*V.z);
                U = V;
                V = Tmp;
            }
            return U;
        }

        /*
        solve n * n^-1 == 1 (mod modulus)
        return n^-1
        */
        static T invert(T n, T modulus){
            AffinePoint res = extended_gcd(n, modulus);
            if (res.y < 0)
                res.y += modulus;
            return res.y;
        }

    };
}

#endif