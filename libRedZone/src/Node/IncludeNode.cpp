/*
 * IncludeNode.cpp
 *
 *      Author: jc
 */
#include "IncludeNode.h"

#include <algorithm>
#include <functional>
#include <memory>
#include <regex>

#include <Common.h>
#include <Exception/Exception.h>
#include <Exception/TemplateSyntaxError.h>
#include <IO/FileReader.h>
#include <Parser/ExpressionParser.h>
#include <Parser/Fragment.h>
#include <Parser/Parser.h>

#include "Root.h"

using namespace json11;
using namespace std::placeholders;

namespace RedZone {

IncludeNode::IncludeNode()
   : Node( false ) {

}

// Yeah... Render-time parsing.
void IncludeNode::render( Writer * stream, Context * context ) const {
   ExpressionParser exprParser( context );
   Json paths = exprParser.parse( m_includeExpr );
   std::vector< std::string > const & allParserPaths = Parser::paths();
   std::string const wrongArgumentError =
      "Include expression \"" + m_includeExpr + "\" must be single string or array of strings.";
   auto rootCreator = [ & ]( std::string path ) -> std::shared_ptr< Root > {
      auto found = std::find_if( allParserPaths.begin(), allParserPaths.end(),
         std::bind( &isReadableFile, std::bind(
            std::function< std::string( std::string const &, std::string const & ) >( strConcat ), _1, path ) ) );
      if( found == allParserPaths.end() ) {
         throw Exception(  "Include failed. Cannot open template file " + path );
      }
      path = *found + path;
      FileReader reader( path );  // FIXME: get rid of specific Reader creating
      static Parser parser;
      return std::shared_ptr< Root >( parser.loadFromStream( &reader ) );
   };
   std::vector< std::shared_ptr< Root > > roots;
   if( paths.is_string() ) {
      roots.push_back( rootCreator( paths.string_value() ) );
   } else if( paths.is_array() ) {
      Json::array const & allPaths = paths.array_items();
      if( std::any_of( allPaths.begin(), allPaths.end(),
             std::bind( std::equal_to< bool >(), std::bind( &Json::is_string, _1 ), false ) ) ) {
         throw Exception( wrongArgumentError ); // Some elements in array do not have string type
      }
      std::transform( allPaths.begin(), allPaths.end(), std::back_inserter( roots ),
         std::bind( rootCreator, std::bind( &Json::string_value, _1 ) ) );
   } else {
      throw Exception( wrongArgumentError );
   }
   std::for_each( roots.begin(), roots.end(), std::bind( &Root::render, _1, stream, context ) );
}

void IncludeNode::processFragment( Fragment const * fragment ) {
   static std::regex splitter( R"(^include\s+(.+))" );
   std::smatch match;
   std::string cleaned = fragment->clean();
   if( !std::regex_match( cleaned, match, splitter ) ) {
         throw TemplateSyntaxError( fragment->clean() );
   }
   m_includeExpr = match[ 1 ];
}

std::string IncludeNode::name() const {
   return "Include";
}

IncludeNode::~IncludeNode() {
}

} /* namespace RedZone */
