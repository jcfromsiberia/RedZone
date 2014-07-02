/*
 * Parser.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "Parser.h"

#include <iostream>
#include <regex>
#include <stack>
#include <utility>

#include <Exception/Exception.h>
#include <Exception/TemplateSyntaxError.h>
#include <Node/EachNode.h>
#include <Node/ElseNode.h>
#include <Node/IfNode.h>
#include <Node/Root.h>
#include <Node/TextNode.h>
#include <Node/Variable.h>

#include "Fragment.h"

namespace RedZone {

const std::map<
        std::string, std::function< Node * () >
        > Parser::s_nodeCreators {
    { R"(^if\s+.*$)",                                 []() { return new IfNode();   } },
    { R"(^else$)",                                    []() { return new ElseNode(); } },
    { R"(^each\s+[A-Za-z0-9\.]+\s+as\s+\w+$)",        []() { return new EachNode(); } },
};

Parser::Parser() {

}

namespace {
    std::string ReplaceString(std::string subject, const std::string& search,
                              const std::string& replace) {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos) {
             subject.replace(pos, search.length(), replace);
             pos += replace.length();
        }
        return subject;
    }
}

Root * Parser::loadFromStream( std::istream & stream ) const {

    std::string split_expr = "(" VAR_START_TOKEN ".*?" VAR_END_TOKEN "|"
            BLOCK_START_TOKEN ".*?" BLOCK_END_TOKEN ")";

    split_expr = ReplaceString( split_expr, "{", "\\{" );
    split_expr = ReplaceString( split_expr, "}", "\\}" );

    static const std::regex token_splitter( split_expr );

    std::vector< std::shared_ptr< Fragment > > fragments;
    std::string line;
    while( std::getline( stream, line ) ) {
        line += "\n";
        std::sregex_token_iterator iter(
                line.begin(), line.end(), token_splitter, std::vector< int >{ -1, 0 } );
        static const std::sregex_token_iterator end;
        for( ; iter != end; ++iter ) {
            if( !( *iter ).length() ) {
                continue;
            }
            fragments.push_back( std::shared_ptr< Fragment >( new Fragment( *iter ) ) );
        }
    }

    Root * root( new Root() );

    std::stack< Node * > scopeStack;
    scopeStack.push( root );

    for( auto fragment: fragments ) {
        if( !scopeStack.size() ) {
            throw Exception( "nesting issues" );
        }

        auto parentScope = scopeStack.top();
        if( fragment->type() == ElementType::CloseBlockFragment ) {
            parentScope->exitScope();
            scopeStack.pop();
            continue;
        }

        auto newNode = createNode( fragment.get() );
        parentScope->addChild( newNode );
        if( newNode->createsScope() ) {
            scopeStack.push( newNode );
            newNode->enterScope();
        }
    }
    return root;
}

Node * Parser::createNode( Fragment const * fragment ) const {
    Node * node = nullptr;
    switch( fragment->type() ) {
    case ElementType::TextFragment:
        node = new TextNode();
        break;
    case ElementType::VarElement:
        node = new Variable();
        break;
    case ElementType::OpenBlockFragment: {
            auto finder = [ fragment ]( std::pair< std::string, std::function< Node * () > > value ) {
                    return std::regex_search( fragment->clean(), std::regex( value.first ) ); };
            auto found = std::find_if( s_nodeCreators.begin(), s_nodeCreators.end(), finder );
            if( found == s_nodeCreators.end() ) {
                throw TemplateSyntaxError( fragment->clean() );
            }
            node = found->second();
        }
        break;
    default:
        throw TemplateSyntaxError( fragment->clean() );
    }
    node->processFragment( fragment );
    return node;
}

Parser::~Parser() {
}

} /* namespace RedZone */
