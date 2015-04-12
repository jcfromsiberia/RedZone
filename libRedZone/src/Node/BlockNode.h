/*
 * BlockNode.h
 *
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class RZ_API BlockNode : public Node {
public:
   BlockNode();

   virtual void render( Writer * stream, Context * context ) const;
   virtual void processFragment( Fragment const * fragment );
   virtual void exitScope( std::string const & endTag );

   virtual std::string name() const;
   std::string blockName() const;

   virtual ~BlockNode();

protected:
   std::string m_blockName;
};

} /* namespace RedZone */
