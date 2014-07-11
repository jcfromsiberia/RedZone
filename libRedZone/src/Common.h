/*
 * Common.h
 *
 *      Author: jc
 */

#pragma once

#include <string>

namespace RedZone {

// Taken from here http://stackoverflow.com/a/15167203/2080453
std::string dbl2str( double d );

std::string replaceString( std::string subject, const std::string & search, const std::string & replace );

void trimString( std::string & str );

bool isReadableFile( std::string const & filePath );

} /* namespace RedZone */
