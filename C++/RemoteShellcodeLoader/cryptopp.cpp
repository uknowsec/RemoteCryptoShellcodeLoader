#include "cryptopp.h"

using namespace std;

void print(const string& cipherText) {
    cout << "[";
    for (unsigned int i = 0; i < cipherText.size(); i++)
    {
        cout << int(cipherText[i]) << ", ";
    }
    cout << "]" << endl;
}

byte cryptopp::s_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
byte cryptopp::s_iv[CryptoPP::AES::DEFAULT_KEYLENGTH];

bool cryptopp::init(const string& key, const string& iv) {
    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH) {
        return false;
    }
    if (iv.size() != CryptoPP::AES::BLOCKSIZE) {
        return false;
    }

    for (int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++) {
        s_key[i] = key[i];
    }
    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++) {
        s_iv[i] = iv[i];
    }
    //memset(s_key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    //memset(s_iv, 0x00, CryptoPP::AES::BLOCKSIZE);
    return true;
}



string cryptopp::encrypt(const string& plainText)
{
    /*
    if ((plainText.length() % CryptoPP::AES::BLOCKSIZE) != 0) {
        return "";
    }
    */

    string cipherTextHex;
    try {
        string cipherText;
        CryptoPP::AES::Encryption aesEncryption(s_key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, s_iv);
        //CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( cipherText ), CryptoPP::StreamTransformationFilter::NO_PADDING);
        CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
        stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
        stfEncryptor.MessageEnd();

        //    print(cipherText);
        for (unsigned int i = 0; i < cipherText.size(); i++)
        {
            char ch[3] = { 0 };
            sprintf(ch, "%02x", static_cast<byte>(cipherText[i]));
            cipherTextHex += ch;
        }
    }
    catch (const std::exception& e) {
        cipherTextHex = "";
    }

    return cipherTextHex;
}

string cryptopp::decrypt(const string& cipherTextHex)
{
    /*
    if(cipherTextHex.empty()) {
        return string();
    }
    if ((cipherTextHex.length() % CryptoPP::AES::BLOCKSIZE) != 0) {
        return string();
    }
    */

    string cipherText;
    string decryptedText;

    unsigned int i = 0;
    while (true)
    {
        char c;
        int x;
        stringstream ss;
        ss << hex << cipherTextHex.substr(i, 2).c_str();
        ss >> x;
        c = (char)x;
        cipherText += c;
        if (i >= cipherTextHex.length() - 2)break;
        i += 2;
    }

    try {
        CryptoPP::AES::Decryption aesDecryption(s_key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, s_iv);
        //CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedText ),CryptoPP::StreamTransformationFilter::NO_PADDING);
        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
        stfDecryptor.Put(reinterpret_cast<const unsigned char*>(cipherText.c_str()), cipherText.size());

        stfDecryptor.MessageEnd();
    }
    catch (const std::exception& e) {
        decryptedText = "";
    }

    return decryptedText;
}
