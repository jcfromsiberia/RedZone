/*
 * BlockNode.cpp
 *
 *      Author: jc
 */
#include "BlockNode.h"

#include <regex>

#include <Exception/TemplateSyntaxError.h>
#include <Parser/Fragment.h>

namespace RedZone {

BlockNode::BlockNode()
   : Node( true ) {
}

void BlockNode::render( Writer * stream, Context * context ) const {
   renderChildren( stream, context );
}

void BlockNode::processFragment( Fragment const * fragment ) {
   static std::regex const blockSplitter( R"(^block\s+(\w+)$)" );
   std::smatch match;
   std::string cleaned = fragment->clean();
   if( ! std::regex_match( cleaned, match, blockSplitter ) ) {
      throw TemplateSyntaxError( fragment->clean() );
   }
   m_blockName = match[ 1 ];
}

void BlockNode::exitScope( std::string const & endTag ) {
   if( endTag != "endblock" )
      throw TemplateSyntaxError( endTag );
}

std::string BlockNode::name() const {
   return "Block";
}

std::string BlockNode::blockName() const {
   return m_blockName;
}

BlockNode::~BlockNode() {
}

} /* namespace RedZone */
