#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <string>
#include "./include/EllipricCurve.hpp"
#include "./include/streebog.h"
#include "./include/cpuinfo.h"

using namespace boost::multiprecision;
using namespace boost::multiprecision::literals;



int main(){
    
    unsigned char hash[512/8];
    cppcrypto::streebog f(512);
    f.init();
    auto t = "Hello friend!";//reinterpret_cast<const unsigned char *>("1bcde12341");
    f.update(reinterpret_cast<const unsigned char *>(t), strlen(t));
    f.final(hash);

    for (auto i: hash)
    {
        std::cout << std::hex << (int)i;
    }
    std::cout << std::endl;
    return 0;
}


