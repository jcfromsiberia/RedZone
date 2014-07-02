/*
 * main.cpp
 *
 *  Created on: 2014.
 *      Author: jc
 */

#include <Context/Context.h>
#include <Template/FileTemplate.h>

#include <iostream>
#include <string>
#include <regex>

using namespace json11;

int main( int argc, char ** argv )
{
    RedZone::FileTemplate tpl( "/tmp/test.tpl" );

    RedZone::Context cont( Json::object { { "vars", Json::array { "2", "OLOLOLOLOLO", "FUUUu" } } } );

    tpl.render( std::cout, &cont );

    return 0;
}
