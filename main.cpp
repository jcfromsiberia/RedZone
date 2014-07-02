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

    std::string err;

    Json json( Json::parse( R"(
      {                                               
         "items": [                                   
           { "text": "Hello World!", "active": true },
           { "text": "Foo", "active": true },         
           { "text": "Bar", "active": false }         
         ]                                            
      }                                               
       )", err ) );

    RedZone::Context cont( json );

    tpl.render( std::cout, &cont );

    return 0;
}
