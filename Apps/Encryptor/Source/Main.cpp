#include <juce_cryptography/juce_cryptography.h>
#include <httplib.h>

using juce::BigInteger;
using juce::Logger;
using juce::MemoryBlock;
using juce::RSAKey;
using juce::String;

struct KeyPair
{
    RSAKey publicKey;
    RSAKey privateKey;
};

using namespace httplib;

inline bool isValidBlock(MemoryBlock& block)
{
    return juce::CharPointer_UTF8::isValidString((char*) block.getData(),
                                                 (int) block.getSize());
}

struct ReqInfo
{
    ReqInfo(const Request& req)
    {
        key = RSAKey(req.get_header_value("key"));
        text = req.get_header_value("text");
    }

    std::string encode() const
    {
        auto utf8 = text.toUTF8();
        auto* utf8Address = utf8.getAddress();
        MemoryBlock plainMemoryBlock(utf8Address, utf8.sizeInBytes());

        BigInteger sourceInteger;
        sourceInteger.loadFromMemoryBlock(plainMemoryBlock);

        if (!sourceInteger.isZero())
        {
            BigInteger encodedInteger(sourceInteger);
            key.applyToValue(encodedInteger);

            MemoryBlock encodedMemoryBlock = encodedInteger.toMemoryBlock();

            return encodedMemoryBlock.toBase64Encoding().toStdString();
        }

        return {};
    }

    inline std::string decode()
    {
        try
        {
            MemoryBlock encodedMemoryBlock;
            encodedMemoryBlock.fromBase64Encoding(text);

            BigInteger encodedInteger;
            encodedInteger.loadFromMemoryBlock(encodedMemoryBlock);

            if (!encodedInteger.isZero())
            {
                BigInteger decodedInteger(encodedInteger);
                key.applyToValue(decodedInteger);

                MemoryBlock decodedMemoryBlock = decodedInteger.toMemoryBlock();

                if (isValidBlock(decodedMemoryBlock))
                    return decodedMemoryBlock.toString().toStdString();
            }
        }
        catch (...)
        {
        }

        return {};
    }

    String text;
    RSAKey key;
};

inline KeyPair generatePair(int numBits)
{
    KeyPair pair;
    RSAKey::createKeyPair(pair.publicKey, pair.privateKey, numBits);

    return pair;
}

int main()
{
    Server svr;

    svr.Get("/encrypt",
            [](const Request& req, Response& res)
            { res.set_content(ReqInfo(req).encode(), "text/plain"); });

    svr.Get("/decrypt",
            [](const Request& req, Response& res)
            { res.set_content(ReqInfo(req).decode(), "text/plain"); });

    svr.Get("/generate",
            [](const Request& req, Response& res)
            {
                auto numBits = String(req.get_header_value("bits")).getIntValue();
                std::string result = "Error";

                if (numBits >= 8)
                {
                    auto pair = generatePair(numBits);

                    result =
                        "Private Key:\n" + pair.privateKey.toString().toStdString() + "\n";

                    result += "Public Key: \n" + pair.publicKey.toString().toStdString();
                }

                res.set_content(result, "text/plain");
            });

    svr.listen("0.0.0.0", 8080);

    return 0;
}
