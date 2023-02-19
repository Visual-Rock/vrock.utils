#include "vrock/utils/ByteArray.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace vrock::utils
{

    ByteArray::ByteArray( ) : length( 0 ), data( nullptr )
    {
    }

    ByteArray::ByteArray( size_t len ) : length( len )
    {
        reserve( len );
    }

    ByteArray::ByteArray( const std::string &str )
    {
        reserve( str.length( ) );
        std::memcpy( data, &str[ 0 ], str.length( ) );
    }

    ByteArray::ByteArray( size_t len, uint8_t *d ) : length( len ), data( d )
    {
    }

    ByteArray::~ByteArray( )
    {
        free( data );
    }

    auto ByteArray::reserve( size_t len ) -> void
    {
        length = len;
        data = (uint8_t *)std::malloc( sizeof( uint8_t ) * len );
        std::memset( data, 0, len );
    }

    auto ByteArray::append( const std::shared_ptr<ByteArray> &data ) -> void
    {
        auto *n = (uint8_t *)std::malloc( sizeof( uint8_t ) * ( length + data->length ) );
        std::memcpy( n, this->data, length );
        std::memcpy( n + length, data->data, length );
        std::free( this->data );
        length = length + data->length;
        this->data = n;
    }

    auto ByteArray::subarr( size_t start, size_t len ) const -> std::shared_ptr<ByteArray>
    {
        if ( len == -1UL )
            len = length - start;
        if ( start + len > length )
            throw std::out_of_range( "failed to create sub array! byte array not long enough." );
        auto subarr = std::make_shared<ByteArray>( len );
        std::memcpy( subarr->data, data + start, len );
        return subarr;
    }

    auto ByteArray::get( size_t pos ) const -> uint8_t
    {
        if ( pos > length - 1 )
            throw std::out_of_range( "out of bounds" );
        return data[ pos ];
    }

    auto ByteArray::set( size_t pos, uint8_t val ) const -> void
    {
        if ( pos > length - 1 )
            throw std::out_of_range( "out of bounds" );
        data[ pos ] = val;
    }

    auto ByteArray::to_string( ) const -> std::string
    {
        if ( length == 0 )
            return "";
        return { (char *)data, length };
    }

    auto ByteArray::to_hex_string( ) const -> std::string
    {
        if ( length == 0 )
            return "";
        std::stringstream str;
        for ( size_t i = 0; i < length; i++ )
            str << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (int)data[ i ];
        return str.str( );
    }

    auto ByteArray::from_string( const std::string &str ) -> std::shared_ptr<ByteArray>
    {
        return std::make_shared<ByteArray>( str );
    }

    auto ByteArray::from_hex_string( const std::string &str ) -> std::shared_ptr<ByteArray>
    {
        std::string s = str + ( ( str.length( ) % 2 == 1 ) ? "0" : "" ); // Append zero if needed
        auto data = std::make_shared<ByteArray>( s.length( ) / 2 );

        for ( size_t i = 0; i < data->length; ++i )
            data->set( i, std::stoul( s.substr( i * 2, 2 ), nullptr, 16 ) );

        return data;
    }

    uint8_t &ByteArray::operator[]( size_t i ) // NOLINT
    {
        return this->data[ i ];
    }
    const uint8_t &ByteArray::operator[]( size_t i ) const
    {
        return this->data[ i ];
    }
} // namespace vrock::utils
