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

        public:

        EllipticCurve(T _a, T _b, T _modulo) : a(_a), b(_b), modulo(_modulo), G_x(nullptr), n(nullptr){}

        EllipticCurve(T _a, T _b, T _modulo, T _G_x, T _order) : a(_a), b(_b), modulo(_modulo), G_x(_G_x), n(_order){}

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
        EllipticCurve<uint256_t> secp256k1(0,
                                           7,
                                           0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f_cppui,
                                           0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798_cppui,
                                           0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141_cppui);
    }

}
#endif