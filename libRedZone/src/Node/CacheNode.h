/*
 * CacheNode.h
 *
 *  Created on: 2015
 *      Author: jc
 */
#pragma once

#include "Node.h"

#include <chrono>
#include <unordered_map>

namespace RedZone {

class RZ_API CacheNode: public Node {
public:
    CacheNode();

    virtual void render( Writer * stream, Context * context ) const;
    virtual void processFragment( Fragment const * fragment );
    virtual void exitScope( std::string const & endTag );
    virtual std::string name() const;

    virtual ~CacheNode();

    typedef std::tuple< std::chrono::time_point< 
       std::chrono::system_clock>, std::string > CacheRow;

protected:
    uint64_t m_cacheTime;
    std::vector< std::string > m_vars;
    static std::unordered_map< size_t, CacheRow > s_cached;
};

} /* namespace RedZone */
