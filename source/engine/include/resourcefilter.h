/*!
 * @file resourcefilter.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 25, 2014
 */
#pragma once

#ifndef ENGINE_INCLUDE_RESOURCEFILTER_H_
#define ENGINE_INCLUDE_RESOURCEFILTER_H_

#include "container/intrusivelist.h"
#include "strings.h"
#include "file.h"

namespace crap
{

class ResourceFilter;

extern intrusive_list<ResourceFilter> ResourceFilterList;

class ResourceFilter
{
public:

    CRAP_INLINE
	ResourceFilter( string_hash name ) : _node( this, &ResourceFilterList ), _id(name.hash()) {}

    virtual ~ResourceFilter( void ) {}

    virtual void import( pointer_t<void> memory, uint32_t memSize ) = 0;

    CRAP_INLINE
	bool operator==( const string_hash& name )
    {
        return _id == name.hash();
    }

protected:
    intrusive_node<ResourceFilter>  _node;
    uint32_t						_id;

};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_RESOURCEFILTER_H_ */
