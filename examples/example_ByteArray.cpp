#include <iostream>
#include <memory>

#include "vrock/utils/ByteArray.hpp"

auto print( const std::shared_ptr<vrock::utils::ByteArray> &data )
{
    std::cout << std::string( (char *)data->data, data->length ) << std::endl;
}

int main( )
{
    auto ba = vrock::utils::ByteArray::from_string( "1234" );
    std::cout << ba->to_string( ) << std::endl;

    auto pba = std::make_shared<vrock::utils::ByteArray>( 4 );
    pba->data[ 0 ] = '1';
    pba->data[ 1 ] = '2';
    pba->data[ 2 ] = '3';
    pba->data[ 3 ] = '4';
    std::cout << pba->to_string( ) << std::endl;

    auto hex = vrock::utils::ByteArray::from_hex_string( "31323334" );
    std::cout << hex->to_string( ) << std::endl;
    ba->append(pba);
    std::cout << ba->to_string() << std::endl;
    std::cout << hex->subarr( 2, 2 )->to_string( ) << std::endl;
    return 0;
}
