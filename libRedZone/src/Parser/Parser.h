/*
 * Parser.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include <functional>
#include <map>

#include <Export.h>

#define BLOCK_START_TOKEN   "{%"
#define BLOCK_END_TOKEN     "%}"
#define VAR_START_TOKEN     "{{"
#define VAR_END_TOKEN       "}}"
#define COMMENT_START_TOKEN "{#"
#define COMMENT_END_TOKEN   "#}"

namespace RedZone {

class Fragment;
class Node;
class Reader;
class Root;

enum class ElementType {
    VarElement,
    OpenBlockFragment,
    CloseBlockFragment,
    TextFragment
};

class RZ_API Parser {
public:
    Parser();

    Root * loadFromStream( Reader * stream ) const;

    virtual ~Parser();

protected:
    Node * createNode( Fragment const * fragment ) const;

protected:
    static const std::map<
        std::string, std::function< Node * () >
        > s_nodeCreators;
};

} /* namespace RedZone */
