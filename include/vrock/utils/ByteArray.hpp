#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>

#include "vrockutils_conf.h"

namespace vrock::utils
{
    /// Utility class for storing unsigned 8 bit integers.
    ///
    /// This class allows the user to store bytes.
    /// It has utility functions that allow to create binary data from hex strings or normal strings as well as
    /// converting the binary data stored to a string.
    class VROCKUTILS_API ByteArray
    {
    public:
        /// initializes the data with a length of zero
        ByteArray( );
        /// allocates memory for len bytes
        explicit ByteArray( size_t len );
        /// converts the string to binary data and stores it in data
        explicit ByteArray( const std::string &str );
        /// stores all given values
        ByteArray( size_t len, uint8_t *d );
        ~ByteArray( );

        /// allocates memory for len bytes
        auto reserve( size_t len ) -> void;

        /// appends the given ByteArray to this ByteArrays data
        auto append( const std::shared_ptr<ByteArray> &data ) -> void;

        /// @brief creates a sub array based on this array
        /// @param start start position
        /// @param len length of the created sub array. defaults to the length - start
        /// @return sub array
        auto subarr( size_t start, size_t len = -1 ) const -> std::shared_ptr<ByteArray>;

        /// @param pos position of the byte
        /// @return byte at the given position
        auto get( size_t pos ) const -> uint8_t;

        /// @param pos position of the byte to set
        /// @param val the new value of the byte
        auto set( size_t pos, uint8_t val ) const -> void;

        /// converts the binary data to an std::string
        auto to_string( ) const -> std::string;

        /// converts the binary data to an std::string in hex format
        auto to_hex_string( ) const -> std::string;

        /// @param str string that should be converted to binary data
        /// @return shared pointer to the binary data of the given string
        static auto from_string( const std::string &str ) -> std::shared_ptr<ByteArray>;
        /// @param str hex string that should be converted to binary data. the data should be in pairs of characters
        /// between 0-9 and a-f/A-F and should not contain any whitespaces or other characters.
        /// @return shared pointer to the binary data of the given string
        static auto from_hex_string( const std::string &str ) -> std::shared_ptr<ByteArray>;

    public:
        /// length of the stored data
        size_t length = 0;
        /// pointer to the first element of the stored data
        uint8_t *data = nullptr;

        uint8_t &operator[]( size_t i );
        const uint8_t &operator[]( size_t i ) const;
    };
} // namespace vrock::utils