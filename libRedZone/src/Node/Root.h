/*
 * Root.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class RZ_API Root : public Node {
public:
    Root();

    virtual void render( std::ostream & stream, Context * context ) const;

    virtual ~Root();
};

} /* namespace RedZone */
