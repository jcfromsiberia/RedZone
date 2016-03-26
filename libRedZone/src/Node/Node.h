/*
 * Node.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include <Context/json11.hpp>
#include <Export.h>

namespace RedZone {

class Context;
class Fragment;
class Writer;

class RZ_API Node {
public:
   using NodePtr  = std::shared_ptr< Node >;
   using NodeCPtr = std::shared_ptr< Node >;

   using Nodes    = std::vector< NodePtr >;

   virtual void render( Writer * stream, Context * context ) const;

   void renderChildren( Writer * stream, Context * context,
      Nodes children = { } ) const;

   virtual void processFragment( Fragment const * fragment );
   void addChild( Node * child );

   bool createsScope() const;

   virtual void enterScope();
   virtual void exitScope( std::string const & endTag );

   virtual std::string name() const;

   Nodes const & children();

   template< class T >
   std::vector< std::weak_ptr< T > > childrenByName( std::string const & name ) {
      using namespace std;
      Nodes nodes;
      using ResultNode = weak_ptr< T >;
      using ResultNodes = vector< ResultNode >;

      copy_if( m_children.begin(), m_children.end(), back_inserter( nodes ),
         bind( equal_to< string >(), bind( &Node::name, placeholders::_1 ), name ) );
      ResultNodes result;
      for( auto & node : nodes )
      {
         result.push_back( weak_ptr< T >( dynamic_pointer_cast< T >( node ) ) );
      }
      return result;
   }

   virtual ~Node();

protected:
   Node( bool createsScope = false );
   virtual json11::Json resolveInContext( std::string const & name, Context const * context ) const;

protected:
   Nodes m_children;
   bool m_createsScope;
};

} /* namespace RedZone */
