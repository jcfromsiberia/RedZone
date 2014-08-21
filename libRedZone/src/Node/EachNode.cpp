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
   if( !( container.is_array() || container.is_object() || container.is_string() ) ) {
      throw Exception( container.dump() + " is not iterable" );
   }
   Json::array items = container.array_items();

   Json::object prototype = context->json().object_items();

   std::shared_ptr< Context > newContext( new Context( prototype ) );

   for( auto item: items ) {
      if( m_vars.size() > 1 ) {
         if( item.is_array() ) {
            auto itemItems = item.array_items();
            auto itemsIter = itemItems.begin();
            std::for_each( m_vars.begin(), m_vars.end(), [ & ]( std::string varName ) {
               if( itemsIter != itemItems.end() ) {
                  prototype[ varName ] = * itemsIter ++;
               }
               else {
                  prototype[ varName ] = Json();
               }
            } );
         } else if( item.is_object() ) {

         } else if( item.is_string() ) {

         } else {
            throw Exception( "Can not extract values from " + item.dump() );
         }
      }
      else {
          prototype[ m_vars[ 0 ] ] = item;
      }
      newContext->setJson( Json( prototype ) );
      renderChildren( stream, newContext.get() );
   }
}

void EachNode::processFragment( Fragment const * fragment ) {
   static std::regex const splitter( R"(^for\s+(\w[a-zA-Z0-9 _,]*) \s*in\s+(.+)$)" );
   std::smatch match;
   if( !std::regex_match( fragment->clean(), match, splitter ) ) {
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
