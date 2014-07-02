/*
 * FileTemplate.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include <fstream>

#include <Exception/IOError.h>

#include "FileTemplate.h"

namespace RedZone {

FileTemplate::FileTemplate( std::string const & filePath )
	: m_filePath( filePath ) {
    std::ifstream in( filePath );
    if( !in.good() ) {
        throw IOError( "Can not open " + m_filePath + " file." );
    }
    loadFromStream( in );
}

FileTemplate::~FileTemplate() {
}

} /* namespace RedZone */
