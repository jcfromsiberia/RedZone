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

typedef std::string( *StrConcat )( std::string const &, std::string const & );

namespace RedZone {

std::vector< std::string > IncludeNode::s_paths { "./" };

IncludeNode::IncludeNode()
   : Node( false ) {

}

// Yeah... Render-time parsing.
void IncludeNode::render( Writer * stream, Context * context ) const {
   ExpressionParser exprParser( context );
   Json paths = exprParser.parse( m_includeExpr );
   std::string const wrongArgumentError =
      "Include expression \"" + m_includeExpr + "\" must be single string or array of strings.";
   static std::string const notFoundError =
      "Cannot find template file ";
   static StrConcat strConcat( std::operator+ );
   auto rootCreator = [ & ]( std::string path ) -> std::shared_ptr< Root > {
      decltype( s_paths )::const_iterator found = std::find_if( s_paths.begin(), s_paths.end(),
         std::bind( &isReadableFile, std::bind(
            std::function< std::string( std::string const &, std::string const & ) >( strConcat ), _1, path ) ) );
      if( found == s_paths.end() ) {
         throw Exception( notFoundError + path );
      }
      path = *found + path;
      FileReader reader( path );
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
   if( !std::regex_match( fragment->clean(), match, splitter ) ) {
         throw TemplateSyntaxError( fragment->clean() );
   }
   m_includeExpr = match[ 1 ];
}

void IncludeNode::addPath( std::string path ) {
   path = replaceString( path, "\\", "/" );
   if ( path.back() != '/' )
      path.push_back( '/' );
   s_paths.push_back( path );
}

std::vector< std::string > const & IncludeNode::paths() {
   return s_paths;
}

IncludeNode::~IncludeNode() {
}

} /* namespace RedZone */
