/*
 * main.cpp
 *
 *  Created on: 2014.
 *      Author: jc
 */

#include <Context/Context.h>
#include <Template/FileTemplate.h>
#include <Parser/ExpressionParser.h>

#include <iostream>
#include <string>
#include <regex>

using namespace json11;

int main( int argc, char ** argv )
{
    RedZone::FileTemplate tpl( "test.tpl" );

    std::string err;

    Json json( Json::parse( R"(
      {                                               
         "items": [                                   
           { "text": "Hello World!", "active": true },
           { "text": "Foo", "active": true },         
           { "text": "Bar", "active": false }         
         ],
         "numbers": {
            "first": 5,
            "second": 11,
            "third": true
         }                                            
      }                                               
       )", err ) );

    RedZone::Context * cont( new RedZone::Context( json ) );

    tpl.render( std::cout, cont );

    RedZone::ExpressionParser parser( cont );

    return 0;
}
