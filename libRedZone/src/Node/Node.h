/*
 * Node.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <Context/json11.hpp>
#include <Export.h>

namespace RedZone {

class Context;
class Fragment;

class RZ_API Node {
public:
	virtual void render( std::ostream & stream, Context * context ) const;

	void renderChildren( std::ostream & stream, Context * context,
	        std::vector< std::shared_ptr< Node > > children = { } ) const;

	virtual void processFragment( Fragment const * fragment );
	void addChild( Node * child );

	bool createsScope() const;

   virtual void enterScope();
   virtual void exitScope();

	virtual ~Node();

protected:
	Node( bool createsScope = false );
	virtual json11::Json resolveInContext( std::string const & name, Context const * context ) const;

protected:
	std::vector< std::shared_ptr< Node > > m_children;
	bool m_createsScope;
};

} /* namespace RedZone */
