/*
 * Variable.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "Variable.h"

#include <Common.h>
#include <IO/Writer.h>
#include <Parser/ExpressionParser.h>
#include <Parser/Fragment.h>

using namespace json11;

namespace RedZone {

Variable::Variable()
   : Node() {

}

void Variable::render( Writer * stream, Context * context ) const {
   ExpressionParser parser( context );
   Json result = parser.parse( m_expression );
   switch( result.type() ) {
      case Json::NUL:
         stream->write( "null" );
         break;
      case Json::NUMBER:
         stream->write( dbl2str( result.number_value() ) );
         break;
      case Json::STRING:
         stream->write( result.string_value() );
         break;
      case Json::BOOL:
         stream->write( result.bool_value() ? "true" : "false" );
         break;
      case Json::ARRAY:
      case Json::OBJECT:
         stream->write( result.dump() );
         break;
   }
}

void Variable::processFragment( Fragment const * fragment ) {
   m_expression = fragment->clean();
}

Variable::~Variable() {
}

} /* namespace RedZone */
