/*
 * TextNode.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */
#include "TextNode.h"

#include <Parser/Fragment.h>

namespace RedZone {

TextNode::TextNode()
    : Node() {

}

void TextNode::render( std::ostream & stream, Context * context ) const {
    (void)context;
    stream << m_text;
}

void TextNode::processFragment( Fragment const * fragment ) {
    m_text = fragment->raw();
}

TextNode::~TextNode() {
}

} /* namespace RedZone */
