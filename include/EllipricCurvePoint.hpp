#ifndef ELLIPTIC_CURVE_POINT_HPP
#define ELLIPTIC_CURVE_POINT_HPP

#include <iostream>
#include "MathUtil.hpp"
namespace ECC
{

    template <typename T>
    class EllipticPoint
    {
    private:
        T x;
        T y;
        T modulo;
        T curve_a; // just for P+P case ._.
    public:
        EllipticPoint() {}
        EllipticPoint(T _x, T _y, T _mod, T _a)
        {
            x = Util::Math<T>::mod(_x, _mod);
            y = Util::Math<T>::mod(_y, _mod);
            modulo = _mod;
            curve_a = _a;
        }

        friend bool operator==(const EllipticPoint &point1, const EllipticPoint &point2)
        {
            if (point1.modulo == point2.modulo)
            {
                if (point1.x == point2.x && point1.y == point2.y)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            throw "Illegal field parameter";
        }

        friend EllipticPoint<T> operator+(const EllipticPoint &P, const EllipticPoint &Q)
        {
            // If Q or P is point at infinity
            if (P == nullptr)
            {
                return Q;
            }
            if (Q == nullptr)
            {
                return P;
            }

            T k;
            if (P == Q)
            {
                /*
                        3*(P.x)^2 + a
                    k = -------------- (mod P.modulo)
                            2*P.y
                */

                T up = Util::Math<T>::mod(
                    3 * Util::Math<T>::pow_finite(P.x, 2, P.modulo) + P.curve_a,
                    P.modulo);
                T down = Util::Math<T>::invert(
                    Util::Math<T>::mod(2 * P.y, P.modulo),
                    P.modulo);

                k = Util::Math<T>::mod(up * down, P.modulo);
            }
            else
            {
                /*
                        P.y - Q.y
                    k = --------- (mod P.modulo)
                        P.x - Q.x
                */
                T up = Util::Math<T>::mod(
                    P.y - Q.y,
                    P.modulo);
                T down = Util::Math<T>::invert(
                    Util::Math<T>::mod(P.x - Q.x, P.modulo),
                    P.modulo);

                k = Util::Math<T>::mod(up * down, P.modulo);
            }
            //new_x = k*k -P.x -Q.x (mod P.modulo)
            T new_x = Util::Math<T>::mod(
                Util::Math<T>::pow_finite(k, 2, P.modulo) - P.x - Q.x,
                P.modulo);
            //new_y = P.modulo - (P.y + k*(new_x-P.x)) (mod modulo)
            T new_y = P.modulo - Util::Math<T>::mod(
                                     P.y + k * (new_x - P.x),
                                     P.modulo);

            std::cout << new_x << " " << new_y << std::endl;
            return ECC::EllipticPoint<T>(new_x, new_y, P.modulo, P.curve_a);
        }
    };

} // namespace ECC

#endif