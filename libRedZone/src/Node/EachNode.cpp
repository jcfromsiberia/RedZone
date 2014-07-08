/*
 * EachNode.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "EachNode.h"

#include <regex>
#include <iostream>

#include <Context/Context.h>
#include <Exception/TemplateSyntaxError.h>
#include <Parser/ExpressionParser.h>
#include <Parser/Fragment.h>

using namespace json11;

namespace RedZone {

EachNode::EachNode()
   : Node( true ) {
}

void EachNode::render( std::ostream & stream, Context * context ) const {
   ExpressionParser parser( context );
   Json container = parser.parse( m_container );
   if( !container.is_array() ) {
      throw Exception( container.dump() + " is not iterable" );
   }
   Json::array items = container.array_items();

   Json::object prototype = context->json().object_items();

   std::shared_ptr< Context > newContext( new Context( prototype ) );

   for( auto item: items ) {
      prototype[ m_var ] = item;
      newContext->setJson( Json( prototype ) );
      renderChildren( stream, newContext.get() );
   }
}

void EachNode::processFragment( Fragment const * fragment ) {
   static std::regex const splitter( R"(^for\s+(\w+)\s+in\s+(.+)$)" );
   std::smatch match;
   if( !std::regex_match( fragment->clean(), match, splitter ) ) {
      throw TemplateSyntaxError( fragment->clean() );
   }
   m_var = match[ 1 ];
   m_container = match[ 2 ];
}

EachNode::~EachNode() {
}

} /* namespace RedZone */
