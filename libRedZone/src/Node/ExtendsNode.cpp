/*
 * ExtendsNode.cpp
 *
 *      Author: jc
 */
#include "ExtendsNode.h"

#include <algorithm>
#include <functional>
#include <regex>

#include <Common.h>
#include <Exception/TemplateSyntaxError.h>
#include <IO/FileReader.h>
#include <Parser/Fragment.h>
#include <Parser/Parser.h>

#include "BlockNode.h"
#include "Root.h"

using namespace std::placeholders;

namespace RedZone {

ExtendsNode::ExtendsNode() :
   Node( true ) {
}

void ExtendsNode::render( Writer * stream, Context * context ) const {
   renderChildren( stream, context, m_nodesToRender );
}

void ExtendsNode::processFragment( Fragment const * fragment ) {
   static std::regex const splitter( R"(^extends\s+(.+)$)" );
   std::smatch match;
   if( !std::regex_match( fragment->clean(), match, splitter ) ) {
      throw TemplateSyntaxError( fragment->clean() );
   }
   std::string path = match[ 1 ];

   std::vector< std::string > const & allParserPaths = Parser::paths();
   auto found = std::find_if( allParserPaths.begin(), allParserPaths.end(),
      std::bind( &isReadableFile, std::bind(
         std::function< std::string( std::string const &, std::string const & ) >( strConcat ), _1, path ) ) );
   if( found == allParserPaths.end() ) {
      throw Exception( "Extending failed. Cannot open template file " + path );
   }
   path = *found + path;
   FileReader reader( path );  // FIXME: get rid of specific Reader creating
   static Parser parser;
   m_parentRoot.reset( parser.loadFromStream( &reader ) );
}

void ExtendsNode::exitScope( std::string const & endTag ) {
   if( endTag != "endextends" )
      throw TemplateSyntaxError( endTag );
   std::vector< std::shared_ptr< BlockNode > > blocks( childrenByName< BlockNode >( "Block" ) );
   for( std::shared_ptr< Node > node: m_parentRoot->children() ) {
      if( node->name() == "Block" ) {
         std::shared_ptr< BlockNode > blockNode = std::dynamic_pointer_cast< BlockNode >( node );
         std::string blockName = blockNode->blockName();
         auto found = std::find_if( blocks.begin(), blocks.end(),
                         std::bind( std::equal_to< std::string >(),
                            std::bind( &BlockNode::blockName, _1 ), blockName ) );
         if( found != blocks.end() ) {
            m_nodesToRender.push_back( std::dynamic_pointer_cast< Node >( *found ) );
            continue;
         }
         m_nodesToRender.push_back( node );
      }
      else {
         m_nodesToRender.push_back( node );
      }
   }
}

std::string ExtendsNode::name() const {
   return "Extends";
}

ExtendsNode::~ExtendsNode() {
}

} /* namespace RedZone */
