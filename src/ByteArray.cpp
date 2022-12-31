#include "vrock/utils/ByteArray.hpp"

#include <stdexcept>
#include <cstring>

namespace vrock::utils {

    ByteArray::ByteArray() : length(0), data(nullptr) { }

    ByteArray::ByteArray(size_t len) : length(len) { reserve(len); }

    ByteArray::ByteArray(const std::string& str)
    {
        reserve(str.length());
        std::memcpy(data, &str[0], str.length());
    }

    ByteArray::ByteArray(size_t len, uint8_t* d) : length(len), data(d) { }

    ByteArray::~ByteArray() { free(data); }

    void ByteArray::reserve(size_t len)
    {
        length = len;
        data = (uint8_t*)malloc(sizeof(uint8_t) * len);
    }

    uint8_t ByteArray::get(size_t pos)
    {
        if (pos > length - 1)
            throw std::out_of_range("out of bounds");
        return data[pos];
    }

    void ByteArray::set(size_t pos, uint8_t val)
    {
        if (pos > length - 1)
            throw std::out_of_range("out of bounds");
        data[pos] = val;
    }

    std::string ByteArray::to_string()
    {
        if (length == 0) return "";
        return { (char*)data, length };
    }

    std::shared_ptr<ByteArray> ByteArray::from_string(const std::string& str)
    {
        return std::make_shared<ByteArray>(str);
    }

    std::shared_ptr<ByteArray> ByteArray::from_hex_string(const std::string &str)
    {
        std::string s = str + ((str.length() % 2 == 1) ? "0" : ""); // Append zero if needed
        auto data = std::make_shared<ByteArray>(s.length() / 2);

        for (size_t i = 0; i < data->length; ++i)
            data->set(i, std::stoul(s.substr(i * 2, 2), nullptr, 16));

        return data;
    }
}