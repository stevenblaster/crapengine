/*!
 * @file audiofilter.h
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


#ifndef PLUGINS_RESOURCES_INCLUDE_AUDIOFILTER_H_
#define PLUGINS_RESOURCES_INCLUDE_AUDIOFILTER_H_

#include "resourcefilter.h"

namespace crap
{

class AudioFilter : public ResourceFilter
{
public:

	AudioFilter( void );
    virtual ~AudioFilter( void );

    virtual void import( string_hash name, pointer_t<void> memory, uint32_t memSize );
};

} /* namespace crap */

#endif /* PLUGINS_RESOURCES_INCLUDE_AUDIOFILTER_H_ */