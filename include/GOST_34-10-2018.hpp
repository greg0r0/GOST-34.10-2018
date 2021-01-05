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
#ifdef DEBUG
            std::cout << "[!] Hash 256bit" << std::endl;    
            std::cout.fill('0');        
            for (auto i : hash)
            {
                std::cout << std::setw(2) << std::hex << (int)i << " ";
            }
            std::cout << std::endl;
#endif

            return Util::convertArrToNumber_256( Util::convertUCtoVUC<256/8>(hash));
        }

        uint512_t getHash_512(std::string data)
        {
            unsigned char hash[512/8];
            cppcrypto::streebog f(512);
            f.init();
            auto t = data.c_str();
            f.update(reinterpret_cast<const unsigned char *>(t), strlen(t));
            f.final(hash);
#ifdef DEBUG
            std::cout << "[!] Hash 512bit" << std::endl;
            std::cout.fill('0');        
            for (auto i : hash)
            {
                std::cout << std::setw(2) << std::hex << (int)i << " ";
            }
            std::cout << std::endl;
#endif
            return Util::convertArrToNumber_512( Util::convertUCtoVUC<512/8>(hash));
        }
    }
    



    template <typename T>
    class Signer
    {
        private:
        ECC::EllipticCurve<T> curve;

        public:

    };

}

#endif