/*!
 * @file guiimagefilter.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 12, 2015
 */


#ifndef PLUGINS_RESOURCES_INCLUDE_IMAGE2DFILTER_
#define PLUGINS_RESOURCES_INCLUDE_IMAGE2DFILTER_

#include "resourcefilter.h"

namespace crap
{
class System;
class ResourceManager;

class Image2DFilter : public ResourceFilter
{
public:

	Image2DFilter( ResourceManager* manager );
    virtual ~Image2DFilter( void );

    virtual void import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system );

    virtual void unload( string_hash name, System* system );
};

} /* namespace crap */

#endif /* PLUGINS_RESOURCES_INCLUDE_IMAGE2DFILTER_ */
