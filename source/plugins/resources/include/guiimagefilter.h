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


#ifndef PLUGINS_RESOURCES_INCLUDE_GUIIMAGEFILTER_H_
#define PLUGINS_RESOURCES_INCLUDE_GUIIMAGEFILTER_H_

#include "resourcefilter.h"

namespace crap
{
class System;
class ResourceManager;

class GuiImageFilter : public ResourceFilter
{
public:

	GuiImageFilter( ResourceManager* manager );
    virtual ~GuiImageFilter( void );

    virtual void import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system );
};

} /* namespace crap */

#endif /* PLUGINS_RESOURCES_INCLUDE_GUIIMAGEFILTER_H_ */
