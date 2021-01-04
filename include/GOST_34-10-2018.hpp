#ifndef GOST_34_10_2018_HPP
#define GOST_34_10_2018_HPP

#include "EllipricCurve.hpp"
#include "streebog.h"

namespace GOST_34_10_2018
{
    namespace StreebogUtil
    {
        uint256_t getHash_256(std::string data)
        {
            unsigned char hash[256/8];
            cppcrypto::streebog f(256);
            f.init();
            auto t = data.c_str();
            
            f.update(reinterpret_cast<const unsigned char *>(t), strlen(t));
            f.final(hash);
            
            for (auto i : hash)
            {
                std::cout << std::hex << (int)i << " ";
            }

            std::cout << std::endl;

            return Util::convertArrToNumber_256( Util::convertUCtoVUC<256/8>(hash));
        }

        uint512_t getHash_512(std::string data)
        {
            unsigned char hash[512/8];
            cppcrypto::streebog f(512);
            f.init();
            auto t = data.c_str();
            std::cout << data.size() << std::endl;
            f.update(reinterpret_cast<const unsigned char *>(t), strlen(t));
            f.final(hash);

            for (auto i : hash)
            {
                std::cout << std::hex << (int)i << " ";
            }

            std::cout << std::endl;

            return Util::convertArrToNumber_512( Util::convertUCtoVUC<512/8>(hash));
        }
    }
    



    template <typename T>
    class Cipher
    {
        private:
        ECC::EllipticCurve<T> curve;

        public:

    };

}

#endif