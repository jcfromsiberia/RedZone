/*
 * Variable.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <Export.h>

#include "Node.h"

namespace RedZone {

class Fragment;

class RZ_API Variable: public Node {
public:
    Variable();

    virtual void render( Writer * stream, Context * context ) const;

    virtual void processFragment( Fragment const * fragment );
    virtual ~Variable();

protected:
    std::string m_expression;
};

} /* namespace RedZone */
