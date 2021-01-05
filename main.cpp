//TODO: makefile ._.
//g++ main.cpp sources/cpuinfo.cpp sources/streebog.cpp sources/crypto_hash.cpp sources/gost3411-2012-sse2.c sources/gost3411-2012-sse41.c -o ECC && ./ECC /tmp/kek.txt

#include <iostream>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <ctime>
#include <cstdint>
#include <cmath>
#include <string>
#include "./include/EllipricCurve.hpp"
#include "./include/streebog.h"
#include "./include/cpuinfo.h"
#include "./include/GOST_34-10-2018.hpp"
#include <cstdlib>
using namespace boost::multiprecision;
using namespace boost::multiprecision::literals;



int main(int argc, char* argv[]){

    //Settings
    // Stage1. Get curve
    ECC::EllipticCurve<int1024_t> cr = ECC::StandartCurves::gost3410_p256;//(0,7,13,7,5,7,1);
    // Stage 2. Generate keys (lol, generate)
    int1024_t d(0x7a929ade789bb9be10ed359dd39a72c11b60961f49397eee1d19ce9891ec3b28_cppui);
    ECC::EllipticPoint<int1024_t> Q = d*cr.getGeneratorPoint();
    std::cout << "[!] priv key && pub key \n"<< d << std::endl << Q.ToString() << std::endl;
    // Signing
    // Stage 1. Read file for signing    
    std::string file = Util::readFile(argv[1]);
    // Stage 2. Get hash
    uint256_t hs = GOST_34_10_2018::StreebogUtil::getHash_256(file);
    // Stage 2.1. Compute e
    int1024_t e(0x2dfbc1b372d89a1188c09c52e0eec61fce52032ab1022e8e67ece6672b043ee5_cppui); //= Util::Math<int1024_t>::mod(hs, cr.getQ());
    if (e.is_zero())
    {
        e = 1;
    }
    std::cout << "e = "<<e << std::endl;
    //Stage 3. Generate k.

    srand(0);
    int1024_t k(0x77105c9b20bcd3122823c8cf6fcc7b956de33814e95b7fe64fed924594dceab3_cppui); //= 5;
    
    //Stage 4. Compute C=kP
    ECC::EllipticPoint<int1024_t> C = k*cr.getGeneratorPoint();
    int1024_t r = Util::Math<int1024_t>::mod(C.getX(), cr.getQ());
    int1024_t s = Util::Math<int1024_t>::mod(
        r*d+k*e,
        cr.getQ()
    );

    std::cout << "[!] Sign\n" << std::hex << r << std::endl << s << std::endl;

    //Now lets check sign :D
    //Stage 1. Check points
    if ((r < 0) || ( r > cr.getQ()))
    {
        return 1;
    }
    if ((s < 0) || ( s > cr.getQ()))
    {
        return 1;
    }
    std::cout << "r,s is ok" << std::endl;
    //Stage 2. Compute e from hs and get inverted e (as v)
    int1024_t v = Util::Math<int1024_t>::invert(e, cr.getQ());

    //Stage 3. Compute z1 && z2
    int1024_t z1 = Util::Math<int1024_t>::mod(
        s*v,
        cr.getQ()
    );
    int1024_t z2 = Util::Math<int1024_t>::mod(
        -1*r*v,
        cr.getQ()
    );
    std::cout << "[!] z1 && z2\n" << std::hex << z1 << std::endl << z2 << std::endl;
    //Stage 4. Generate elliptic point
    ECC::EllipticPoint<int1024_t> new_C = (z1*cr.getGeneratorPoint()) + (z2*Q);
    int1024_t R = Util::Math<int1024_t>::mod(new_C.getX(), cr.getQ());
    std::cout << "[!] R and r\n" << std::hex << R << std::endl << r << std::endl; 
    if (R == r)
    {
        std::cout << "Подпись верна" << std::endl;
    } else {
        std::cout << "Подпись не верна" <<std::endl;
    }

    return 0;
}
