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


    ECC::EllipticCurve<int2048_t> cr = ECC::StandartCurves::gost3410_p256;

    // Signing
    // Stage 1. Read file for signing    
    std::string data = Util::readFile(argv[1]);
    
    auto keys = GOST_34_10_2018::Algorithms::genKeys(cr, 256);
    GOST_34_10_2018::Types::Sign<int2048_t> sign = GOST_34_10_2018::Algorithms::createSign(data, keys.second, cr, 256);
    if (GOST_34_10_2018::Algorithms::checkSign(data, sign, keys.first, cr, 256))
    {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ne ok" << std::endl;
    }
    return 0;
}
