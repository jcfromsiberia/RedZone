/*
 * Template.cpp
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#include <algorithm>
#include <functional>

#include <IO/StringWriter.h>
#include <Node/Root.h>
#include <Parser/Parser.h>

#include "Template.h"

using namespace std::placeholders;

namespace RedZone {

Template::Template() {
}

void Template::renderToStream( Writer * stream, Context * context ) const {
   m_root->render( stream, context );
}

std::string Template::render( Context * context ) const {
   std::string result;
   StringWriter stringWriter( result );
   renderToStream( &stringWriter, context );
   return result;
}

void Template::loadFromStream( Reader * stream ) {
   Parser parser;
   m_root.reset( parser.loadFromStream( stream ) );
}

Template::~Template() {
}

} /* namespace RedZone */
