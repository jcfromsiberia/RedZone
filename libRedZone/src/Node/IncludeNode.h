/*
 * IncludeNode.h
 *
 *      Author: jc
 */

#pragma once

#include <string>
#include <vector>

#include "Node.h"

namespace RedZone {

class Root;

class RZ_API IncludeNode : public Node {
public:
   IncludeNode();

   virtual void render( Writer * stream, Context * context ) const;

   virtual void processFragment( Fragment const * fragment );

   static void addPath( std::string path );
   static std::vector< std::string > const & paths();

   virtual ~IncludeNode();

protected:
   static std::vector< std::string > s_paths;
   std::string m_includeExpr;
};

} /* namespace RedZone */
