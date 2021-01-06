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
            Elliptic curve:  y^2 == x^3 + a*x+b (mod p)
        */

        private:
        T modulo;
        T a;
        T b;
        ECC::EllipticPoint<T> G;
        T n;
        T h;

        public:

        EllipticCurve(T _a, T _b, T _modulo) : a(_a), b(_b), modulo(_modulo), G(nullptr), n(nullptr), h(nullptr){}

        EllipticCurve(T _a, T _b, T _modulo, T _G_x, T _G_y, T _order, T _h)
        {
            this->a = _a;
            this->b = _b;
            this->modulo = _modulo;

            T ab_check = Util::Math<T>::mod(4*boost::multiprecision::powm(_a,3, _modulo)+27*boost::multiprecision::powm(b,2,_modulo), _modulo);

            if (ab_check == 0)
            {
                std::cout << "Bad a b parameters - it's singular curve" << std::endl;
                throw "Incorrect point G: Point not on curve";
            }

            this->n=_order;
            this->h=_h; 
            ECC::EllipticPoint<T> point(_G_x, _G_y, _modulo, _a);
            T left = boost::multiprecision::powm(point.getY(),2,_modulo);
            T right = Util::Math<T>::mod(boost::multiprecision::powm(point.getX(), 3, _modulo) + Util::Math<T>::mod(_a*point.getX(), _modulo)+Util::Math<T>::mod(_b, _modulo), _modulo);
            if (left==right){
                this->G = point;
            } else {
                std::cout << "Incorrect point G: Point not on curve" << std::endl;
                throw "Incorrect point G: Point not on curve";
            }
        }

        void setOrder(T order)
        {
            this->n = order;
        }

        ECC::EllipticPoint<T> getGeneratorPoint()
        {
            return this->G;
        }

        T getQ()
        {
            return this->n;
        }

        bool CheckPoint(ECC::EllipticPoint<T> point){
            if (point.is_in_infinity()){
                return true;
            }
            T left = boost::multiprecision::powm(point.getY(),2,this->modulo);
            T right = boost::multiprecision::powm(point.getX(), 3, this->modulo) + Util::Math<T>::mod(this->a*point.getX(), this->modulo)+Util::Math<T>::mod(this->b, this->modulo);
            return (left == right);
        }

        bool CheckPoint(T x, T y){
            ECC::EllipticPoint<T> point(x,y,this->modulo, this->a);
            T left = boost::multiprecision::powm(point.getY(),2,this->modulo);
            T right = boost::multiprecision::powm(point.getX(), 3, this->modulo) + Util::Math<T>::mod(this->a*point.getX(), this->modulo)+Util::Math<T>::mod(this->b, this->modulo);
            return (left == right);
        }


        std::string ToString(){
            std::stringstream ss;       
            ss << "y == x^3 + " << this->a << "*x + " << this->b << " (mod " << this->modulo << ")";
            return ss.str(); 
        }

        std::pair< ECC::EllipticPoint<T> , ECC::EllipticPoint<T> > producePoint(T x)
        {
            T y = boost::multiprecision::powm(x, 3, this->modulo) + Util::Math<T>::mod(this->a*x, this->modulo)+Util::Math<T>::mod(this->b, this->modulo);
            
            std::pair<T,T> res_points = Util::Math<T>::getYfromX(y, this->modulo);
            if (res_points.first == 0 && res_points.second == 0)
            {
                return std::pair< ECC::EllipticPoint<T> , ECC::EllipticPoint<T> >( ECC::EllipticPoint<T>(true), ECC::EllipticPoint<T>(true) );
            } else {
                return std::pair< ECC::EllipticPoint<T> , ECC::EllipticPoint<T> >( ECC::EllipticPoint<T>(x, res_points.first, this->modulo, this->a), ECC::EllipticPoint<T>(x, res_points.second, this->modulo, this->a) );
            }
        }

        
    };

    namespace StandartCurves
    {
        //Bitcoin Curve, J(E)=0
        EllipticCurve<int1024_t> secp256k1(
        /*a*/      0,
        /*b*/      7,
        /*mod*/    0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f_cppui,
        /*G(x,y)*/ 0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798_cppui, 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8_cppui,
        /*n*/      0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141_cppui,
        /*h*/      1
        );
                                            
        //J(E)!=0
        EllipticCurve<int1024_t> gost3410_p256(
            7,
            0x5FBFF498AA938CE739B8E022FBAFEF40563F6E6A3472FC2A514C0CE9DAE23B7E_cppui,
            0x8000000000000000000000000000000000000000000000000000000000000431_cppui,
            2,0x8E2A8A0E65147D4BD6316030E16D19C85C97F0A9CA267122B96ABBCEA7E8FC8_cppui,
            0x8000000000000000000000000000000150FE8A1892976154C59CFC193ACCF5B3_cppui,
            1
        );
    }

}
#endif