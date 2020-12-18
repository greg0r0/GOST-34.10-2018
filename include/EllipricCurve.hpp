#ifndef ELLIPTIC_CURVE_HPP
#define ELLIPTIC_CURVE_HPP

#include "EllipricCurvePoint.hpp"
#include <string>
#include <sstream>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
using namespace boost::multiprecision::literals;

namespace ECC {

    template <typename T> // maybe class t?
    class EllipticCurve
    {
        /*
            Elliptic curve:  y == x^3 + a*x+b (mod p)
        */

        private:
        T modulo;
        T a;
        T b;
        T G_x;
        T n;
        T h;

        public:

        EllipticCurve(T _a, T _b, T _modulo) : a(_a), b(_b), modulo(_modulo), G_x(nullptr), n(nullptr), h(nullptr){}

        EllipticCurve(T _a, T _b, T _modulo, T _G_x, T _order, T _h) : a(_a), b(_b), modulo(_modulo), G_x(_G_x), n(_order), h(_h){}

        void setG_x(T x_coord){
            if (CheckPoint()){
                this->G_x = x_coord;
            } else {
                throw -1;
            }
        }

        void set_n(T order)
        {
            this->n = order;
        }

        bool CheckPoint(); //TODO: Point Class


        std::string ToString(){
            std::stringstream ss;       
            ss << "y == x^3 + " << this->a << "*x + " << this->b << " (mod " << this->modulo << ")";
            return ss.str(); 
        }
        
    };

    namespace StandartCurves
    {
        //Bitcoin Curve, J(E)=0
        EllipticCurve<uint256_t> secp256k1(0,
                                           7,
                                           0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f_cppui,
                                           0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798_cppui,
                                           0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141_cppui,
                                           1);
        //J(E)!=0
        EllipticCurve<uint256_t> secp256r1(0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc_cppui,
                                           0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b_cppui,
                                           0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff_cppui,
                                           0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296_cppui,
                                           0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551_cppui,
                                           1);
    }

}
#endif