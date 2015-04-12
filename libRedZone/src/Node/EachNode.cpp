/*
 * EachNode.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "EachNode.h"

#include <iostream>
#include <regex>

#include <Common.h>
#include <Context/Context.h>
#include <Exception/TemplateSyntaxError.h>
#include <Parser/ExpressionParser.h>
#include <Parser/Fragment.h>

using namespace json11;

namespace RedZone {

EachNode::EachNode()
   : Node( true ) {
}

void EachNode::render( Writer * stream, Context * context ) const {
   ExpressionParser parser( context );
   Json container = parser.parse( m_container );
   if( !( container.is_array() || container.is_object() ) ) {
      throw Exception( container.dump() + " is not iterable" );
   }

   Json::object prototype = context->json().object_items();

   std::shared_ptr< Context > newContext( new Context( prototype ) );
   if( container.type() == Json::ARRAY ) {
      Json::array items = container.array_items();
      for( auto const & item: items ) {
         prototype[ m_vars[ 0 ] ] = item;
         newContext->setJson( Json( prototype ) );
         renderChildren( stream, newContext.get() );
      }
   } else if( container.type() == Json::OBJECT ) {
      Json::object items = container.object_items();
      for( auto const & item: items ) {
         prototype[ m_vars[ 0 ] ] = item.first;
         if( m_vars.size() > 1 ) {
            prototype[ m_vars[ 1 ] ] = item.second;
         }
         newContext->setJson( Json( prototype ) );
         renderChildren( stream, newContext.get() );
      }
   }
}

void EachNode::processFragment( Fragment const * fragment ) {
   static std::regex const splitter( R"(^for\s+(\w[a-zA-Z0-9 _,]*) \s*in\s+(.+)$)" );
   std::smatch match;
   std::string cleaned = fragment->clean();
   if( !std::regex_match( cleaned, match, splitter ) ) {
      throw TemplateSyntaxError( fragment->clean() );
   }
   std::string vars = match[ 1 ];
   static std::regex const varNameExtractor( R"(\s*,\s*)" );
   std::sregex_token_iterator varNamesIter( vars.begin(), vars.end(), varNameExtractor, -1 );
   std::vector< std::string > possibleVars;
   static std::sregex_token_iterator const end;
   std::copy( varNamesIter, end, std::back_inserter( possibleVars ) );
   if( std::find( possibleVars.begin(), possibleVars.end(), "" ) != possibleVars.end() ) {
      throw TemplateSyntaxError( vars );
   }
   m_vars = possibleVars;
   m_container = match[ 2 ];
}

void EachNode::exitScope( std::string const & endTag ) {
   if( endTag != "endfor" )
      throw TemplateSyntaxError( endTag );
}

std::string EachNode::name() const {
   return "For";
}

EachNode::~EachNode() {
}

} /* namespace RedZone */
