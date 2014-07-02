/*
 * Exception.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <stdexcept>
#include <string>

#include <Export.h>

namespace RedZone {

class RZ_API Exception: public std::exception {
public:
    Exception( std::string const & message );
    virtual ~Exception();

    virtual const char * what() const throw();

protected:
    std::string m_message;
};

} /* namespace RedZone */
