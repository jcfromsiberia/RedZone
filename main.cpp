/*
 * main.cpp
 *
 *  Created on: 2014.
 *      Author: jc
 */

#include <Context/Context.h>
#include <Template/FileTemplate.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace json11;

int main( int argc, char ** argv )
{
    RedZone::FileTemplate tpl( "test.tpl" );

    std::ifstream jsonIn( "test.json" );
    if( !jsonIn.good() ) {
       return 1;
    }

    std::string err;

    Json json( Json::parse(
       std::string(
          std::istreambuf_iterator< char >( jsonIn ),
          std::istreambuf_iterator< char >() ),
          err ) );

    if( err.length() ) {
       std::cerr << err << std::endl;
       return 1;
    }

    RedZone::Context * cont( new RedZone::Context( json ) );

    std::cout << tpl.render( cont ) << std::endl;

    return 0;
}
