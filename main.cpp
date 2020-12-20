#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include "./include/EllipricCurve.hpp"

using namespace boost::multiprecision;
using namespace boost::multiprecision::literals;

template <typename T>
static inline int adhoc_log2(T i) {
    int n = 0;
    while(i /= 2) ++n;
    return n;
}

int main(){
    //ECC::EllipticCurve<int512_t> cr(0,7,2707);
    //ECC::EllipticPoint<int512_t> P(741,583,2707,0);
    // std::cout << cr.producePoint(741).first.ToString() << std::endl;
    // std::cout << cr.producePoint(741).second.ToString() << std::endl;
    // std::cout << cr.CheckPoint(cr.producePoint(741).first) << std::endl;
    // std::cout << cr.CheckPoint(cr.producePoint(741).second) << std::endl;
    
    ECC::EllipticCurve<int1024_t> cr = ECC::StandartCurves::gost3410_p256;
    uint1024_t k(0x77105C9B20BCD3122823C8CF6FCC7B956DE33814E95B7FE64FED924594DCEAB3_cppui);

    auto d = k* cr.getGeneratorPoint();
    std::cout << d.ToString() <<std::endl;
    // auto i = Util::Math<uint1024_t>::getBits(k); 
    // for (auto b : i)
    // {
    //     std::cout << b;
    // }
    return 0;
}


