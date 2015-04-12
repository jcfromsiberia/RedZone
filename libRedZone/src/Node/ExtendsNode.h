/*
 * ExtendsNode.h
 *
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Root;

class RZ_API ExtendsNode : public Node {
public:
   ExtendsNode();

   virtual void render( Writer * stream, Context * context ) const;
   virtual void processFragment( Fragment const * fragment );
   virtual void exitScope( std::string const & endTag );

   virtual std::string name() const;

   virtual ~ExtendsNode();

protected:
   std::string m_path;
   std::vector< std::shared_ptr< Node > > m_nodesToRender;
   std::shared_ptr< Root > m_parentRoot;
};

} /* namespace RedZone */
