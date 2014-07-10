/*
 * Node.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <vector>
#include <memory>

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
