/*!
 * @file wavefilefilter.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 27, 2014
 */
#pragma once

#ifndef PLUGINS_RESOURCES_INCLUDE_WAVEFILEFILTER_H_
#define PLUGINS_RESOURCES_INCLUDE_WAVEFILEFILTER_H_

#include "resourcefilter.h"

namespace crap
{
class System;
class ResourceManager;

class WaveFileFilter : public ResourceFilter
{
public:

	WaveFileFilter( ResourceManager* manager );
    virtual ~WaveFileFilter( void );

    virtual void import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system );

    virtual void unload( string_hash name, System* system );
};

} /* namespace crap */

#endif /* PLUGINS_RESOURCES_INCLUDE_WAVEFILEFILTER_H_ */
