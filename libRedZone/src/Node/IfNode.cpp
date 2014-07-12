/*
 * IfNode.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "IfNode.h"

#include <algorithm>
#include <iterator>
#include <regex>
#include <set>
#include <typeinfo>

#include <Context/Context.h>
#include <Context/json11.hpp>
#include <Exception/TemplateSyntaxError.h>
#include <Parser/ExpressionParser.h>
#include <Parser/Fragment.h>

using namespace json11;

namespace RedZone {

IfNode::IfNode()
    : Node( true ) {

}

void IfNode::render( Writer * stream, Context * context ) const {
   ExpressionParser parser( context );
   if( parser.parse( m_expression ).bool_value() ) {
      renderChildren( stream, context, m_ifNodes );
   } else {
      renderChildren( stream, context, m_elseNodes );
   }
}

void IfNode::exitScope( std::string const & endTag ) {
   if( endTag != "endif" )
      throw TemplateSyntaxError( endTag );
   std::vector< std::shared_ptr< Node > > * current = &m_ifNodes;
   for( auto child: m_children ) {
      if( child->name() == "Else" ) {
         current = &m_elseNodes;
         continue;
      }
      current->push_back( child );
   }
}

void IfNode::processFragment( Fragment const * fragment ) {
    std::string clean = fragment->clean();
    m_expression.clear();
    m_ifNodes.clear();
    m_elseNodes.clear();
    std::copy( clean.begin() + 3, clean.end(), std::back_inserter( m_expression ) );
}

std::string IfNode::name() const {
   return "If";
}

IfNode::~IfNode() {
}

} /* namespace RedZone */
