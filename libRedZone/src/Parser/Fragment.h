/*
 * Fragment.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <string>

#include "Parser.h"

namespace RedZone {

class Fragment {
public:
    Fragment( std::string const & rawText );

    std::string cleanFragment() const;

    ElementType type() const;

    std::string raw() const;
    std::string clean() const;

    virtual ~Fragment();

protected:
    std::string m_rawText;
    std::string m_cleanText;
};

} /* namespace RedZone */
