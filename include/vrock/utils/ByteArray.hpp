#pragma once

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <string>

namespace vrock::utils {
    class ByteArray {
    public:
        ByteArray();
        ByteArray(size_t len);
        ByteArray(const std::string& str);
        ByteArray(size_t len, uint8_t* d);
        ~ByteArray();

        void reserve(size_t len);

        uint8_t get(size_t pos);
        void set(size_t pos, uint8_t val);

        std::string to_string();

        static std::shared_ptr<ByteArray> from_string(const std::string& str);
    public:
        size_t length;
        uint8_t* data;
    };
}