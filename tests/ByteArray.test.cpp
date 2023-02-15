#include <gtest/gtest.h>

#include "vrock/utils/ByteArray.hpp"

using vrock::utils::ByteArray;

TEST( ByteArrayConstructor, BasicAssertion )
{

    {
        ByteArray arr;
        EXPECT_EQ( arr.length, 0 );
        EXPECT_EQ( arr.data, nullptr );
    }

    {
        ByteArray arr( 5 );
        EXPECT_EQ( arr.length, 5 );
        EXPECT_NE( arr.data, nullptr );
    }

    {
        ByteArray arr( "12345" );
        EXPECT_EQ( arr.length, 5 );
        EXPECT_NE( arr.data, nullptr );
        EXPECT_EQ( arr.data[ 0 ], '1' );
        EXPECT_EQ( arr.data[ 1 ], '2' );
        EXPECT_EQ( arr.data[ 2 ], '3' );
        EXPECT_EQ( arr.data[ 3 ], '4' );
        EXPECT_EQ( arr.data[ 4 ], '5' );
    }

    {
        auto *data = (uint8_t *)malloc( 5 * sizeof( uint8_t ) );
        ByteArray arr( 5, data );
        arr.data[ 0 ] = '1';
        arr.data[ 1 ] = '2';
        arr.data[ 2 ] = '3';
        arr.data[ 3 ] = '4';
        arr.data[ 4 ] = '5';
        EXPECT_EQ( arr.length, 5 );
        EXPECT_NE( arr.data, nullptr );
        EXPECT_EQ( arr.data[ 0 ], '1' );
        EXPECT_EQ( arr.data[ 1 ], '2' );
        EXPECT_EQ( arr.data[ 2 ], '3' );
        EXPECT_EQ( arr.data[ 3 ], '4' );
        EXPECT_EQ( arr.data[ 4 ], '5' );
    }
}

TEST( ByteArraySetGet, BasicAssertion )
{
    ByteArray arr( "12345" );

    EXPECT_NO_THROW( arr.set( 4, '8' ) );
    EXPECT_EQ( arr.get( 4 ), '8' );

    EXPECT_THROW( arr.set( 5, '8' ), std::out_of_range );
    EXPECT_THROW( arr.get( 5 ), std::out_of_range );
}

TEST( ByteArrayToString, BasicAssertion )
{
    ByteArray arr( "12345" );
    auto hex = ByteArray::from_hex_string( "31323334" );

    EXPECT_EQ( arr.to_string( ), "12345" );
    EXPECT_EQ( hex->to_hex_string( ), "31323334" );
}

TEST( ByteArrayFromString, BasicAssertion )
{
    auto str = ByteArray::from_string( "1234" );
    auto hex = ByteArray::from_hex_string( "31323334" );

    EXPECT_EQ( hex->to_string( ), "1234" );
    EXPECT_EQ( str->to_string( ), "1234" );
}