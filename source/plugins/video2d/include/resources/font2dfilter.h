/*!
 * @file font2dfilter.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 18, 2015
 */


#ifndef PLUGINS_RESOURCES_INCLUDE_FONT2DFILTER_
#define PLUGINS_RESOURCES_INCLUDE_FONT2DFILTER_

#include "resourcefilter.h"

namespace crap
{
class System;
class ResourceManager;

class Font2DFilter : public ResourceFilter
{
public:

	Font2DFilter( ResourceManager* manager );
    virtual ~Font2DFilter( void );

    virtual void import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system );

    virtual void unload( string_hash name, System* system );
};

} /* namespace crap */

#endif /* PLUGINS_RESOURCES_INCLUDE_FONT2DFILTER_ */
