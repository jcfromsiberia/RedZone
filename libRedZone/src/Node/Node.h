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
	virtual void render( Writer * stream, Context * context ) const;

	void renderChildren( Writer * stream, Context * context,
	        std::vector< std::shared_ptr< Node > > children = { } ) const;

	virtual void processFragment( Fragment const * fragment );
	void addChild( Node * child );

	bool createsScope() const;

   virtual void enterScope();
   virtual void exitScope( std::string const & endTag );

   virtual std::string name() const;

   std::vector< std::shared_ptr< Node > > const & children();

   template< class T >
   std::vector< std::shared_ptr< T > > childrenByName( std::string const & name ) {
      std::vector< std::shared_ptr< Node > > nodes;
      std::copy_if( m_children.begin(), m_children.end(), std::back_inserter( nodes ),
         std::bind( std::equal_to< std::string >(), std::bind( &Node::name, std::placeholders::_1 ), name ) );
      std::vector< std::shared_ptr< T > > result;
      typedef std::shared_ptr< T >( *DynamicPointerCast )( std::shared_ptr< Node > const & );
      DynamicPointerCast caster = std::dynamic_pointer_cast< T >;
      std::transform( nodes.begin(), nodes.end(), std::back_inserter( result ), caster );
      return result;
   }

	virtual ~Node();

protected:
	Node( bool createsScope = false );
	virtual json11::Json resolveInContext( std::string const & name, Context const * context ) const;

protected:
	std::vector< std::shared_ptr< Node > > m_children;
	bool m_createsScope;
};

} /* namespace RedZone */
