#include <iostream>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <string>
#include "./include/EllipricCurve.hpp"
#include "./include/streebog.h"
#include "./include/cpuinfo.h"
#include "./include/GOST_34-10-2018.hpp"

using namespace boost::multiprecision;
using namespace boost::multiprecision::literals;



int main(int argc, char* argv[]){

    // Stage 1. Read file for signing    
    std::ifstream fd(argv[1]);
    std::stringstream buf;
    if (fd)
    {
        buf << fd.rdbuf();
    }

    std::cout << buf.str() << std::endl;


    return 0;
}
