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
#include <Node/ElseNode.h>
#include <Parser/Fragment.h>

using namespace json11;

namespace RedZone {

const std::map< std::string, IfNode::Comparer > IfNode::m_comparers {
    { "<",  &Json::operator <  },
    { ">",  &Json::operator >  },
    { "<=", &Json::operator <= },
    { ">=", &Json::operator >= },
    { "==", &Json::operator == },
    { "!=", &Json::operator != }
};

IfNode::IfNode()
    : Node( true ) {

}

Json IfNode::operandToJson( std::string const & operand, Context const * context ) const {
   // trying to convert the operands to JSON
   std::string err;
   Json json( Json::parse( operand.c_str(), err ) );
   if( !err.length() ) {
      return json;
   }
   json = resolveInContext( operand, context ); // throws an exception if variable is invalid
   return json;

}

void IfNode::render( std::ostream & stream, Context * context ) const {
   bool execIfBranch = false;
   if( m_comparer ) {
      Json op1 = operandToJson( m_operands[0], context ),
           op2 = operandToJson( m_operands[1], context );
      execIfBranch = ( op1.*m_comparer )( op2 );
   } else {
      Json op = operandToJson( m_operands[0], context );
      execIfBranch = op.bool_value();
   }
   if( execIfBranch ) {
      renderChildren( stream, context, m_ifNodes );
   } else {
      renderChildren( stream, context, m_elseNodes );
   }
}

void IfNode::exitScope() {
   std::vector< std::shared_ptr< Node > > * current = &m_ifNodes;
   for( auto child: m_children ) {
      if( typeid( *child ) == typeid( ElseNode ) ) { // TODO: get rid of this sh#t!
         current = &m_elseNodes;
         continue;
      }
      current->push_back( child );
   }
}

void IfNode::processFragment( Fragment const * fragment ) {
    static const std::regex splitter( R"(\s+)" ); // FIXME: expressions might not contain spaces
    std::string clean = fragment->clean();
    std::vector< std::string > splitted;
    std::copy( std::sregex_token_iterator( clean.begin() + 3 /* skipping "if " */, clean.end(), splitter, -1 ),
            std::sregex_token_iterator(), std::back_inserter( splitted ) );
    if( splitted.size() == 3 ) {
        auto found = m_comparers.find( splitted[1] );
        if( found == m_comparers.end() ) {
            throw TemplateSyntaxError( clean );
        }
        m_comparer = found->second;
        m_operands.push_back( splitted[0] );
        m_operands.push_back( splitted[2] ); // TODO: validate operands
    } else if( splitted.size() == 1 ) {
       m_operands.push_back( splitted[0] );
    } else {
       throw TemplateSyntaxError( clean );
    }
}

IfNode::~IfNode() {
}

} /* namespace RedZone */
