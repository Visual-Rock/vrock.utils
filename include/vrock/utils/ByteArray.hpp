#pragma once

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <string>

namespace vrock::utils 
{
    /// Utility class for storing unsigned 8 bit integers.
    ///
    /// This class allows the user to store bytes. 
    /// It has utility functions that allow to create binary data from hex strings or normal strings as well as
    /// converting the binary data stored to a string.
    class ByteArray {
    public:
        /// initializes the data with a length of zero 
        ByteArray();
        /// allocates memory for len bytes
        ByteArray(size_t len);
        /// converts the string to binary data and stores it in data
        ByteArray(const std::string& str);
        /// stores all given values
        ByteArray(size_t len, uint8_t* d);
        ~ByteArray();

        /// allocates memory for len bytes
        void reserve(size_t len);

        /// appends the given ByteArray to this ByteArrays data
        void append(std::shared_ptr<ByteArray> data);

        /// @param pos position of the byte
        /// @return byte at the given position
        uint8_t get(size_t pos);

        /// @param pos position of the byte to set
        /// @param val the new value of the byte
        void set(size_t pos, uint8_t val);

        /// converts the binary data to an std::string
        std::string to_string();

        /// converts the binary data to an std::string in hex format
        std::string to_hex_string();
        
        /// @param str string that should be converted to binary data
        /// @return shared pointer to the binary data of the given string 
        static std::shared_ptr<ByteArray> from_string(const std::string& str);
        /// @param str hex string that should be converted to binary data. the data should be in pairs of characters between 0-9 and a-f/A-F and should not contain any whitespaces or other characters.
        /// @return shared pointer to the binary data of the given string 
        static std::shared_ptr<ByteArray> from_hex_string(const std::string& str);
    public:
        /// length of the stored data 
        size_t length;
        /// pointer to the first element of the stored data
        uint8_t* data = nullptr;

        uint8_t& operator[] (size_t i);
        const uint8_t& operator[] (size_t i) const;
    };
}