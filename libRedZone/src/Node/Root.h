/*
 * Root.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Writer;

class RZ_API Root : public Node {
public:
    Root();

    virtual void render( Writer * stream, Context * context ) const;

    virtual ~Root();
};

} /* namespace RedZone */
