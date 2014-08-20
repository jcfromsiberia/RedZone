/*
 * Root.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include <string>

#include "Node.h"

namespace RedZone {

class Writer;

class RZ_API Root : public Node {
public:
    Root( std::string id );

    virtual void render( Writer * stream, Context * context ) const;

    virtual std::string name() const;

    inline std::string id() const { return m_id; }

    virtual ~Root();

protected:
    std::string m_id;
};

} /* namespace RedZone */
