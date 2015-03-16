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

#include "config/crap_compiler.h"
#include "container/intrusivelist.h"
#include "strings.h"
#include "file.h"

namespace crap
{

class System;
class ResourceManager;

//extern "C" CRAP_EXE_TO_DLL intrusive_list<ResourceFilter> ResourceFilterList;

class ResourceFilter
{
public:

	ResourceFilter( string_hash name, ResourceManager* manager );

    virtual ~ResourceFilter( void ) {}

    virtual void import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system ) = 0;

    virtual void unload( string_hash name, System* system ) = 0;

    CRAP_INLINE
	bool operator==( const string_hash& name )
    {
        return _id == name.hash();
    }

    CRAP_INLINE
	bool operator<( const ResourceFilter& other ) const { return _id < other._id; }

protected:

    intrusive_node<ResourceFilter>  _node;
    uint32_t						_id;

};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_RESOURCEFILTER_H_ */
