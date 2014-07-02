/*
 * Template.h
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include <Export.h>

namespace RedZone {

class Context;
class Root;

class RZ_API Template {
public:
	virtual ~Template();

	void render( std::ostream & stream, Context * context ) const;

protected:
	Template();
	void loadFromStream( std::istream & stream );

protected:
	std::shared_ptr< Root const > m_root;

};

} /* namespace RedZone */
