#ifndef CRYPTOPP_H
#define CRYPTOPP_H
#include<Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>



class cryptopp {
public:
    static bool init(const std::string& key, const std::string& iv);
    static std::string encrypt(const std::string& inputPlainText);
    static std::string decrypt(const std::string& cipherTextHex);
private:
    static byte s_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    static byte s_iv[CryptoPP::AES::DEFAULT_KEYLENGTH];
};
#endif