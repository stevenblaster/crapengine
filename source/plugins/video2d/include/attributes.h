/*!
 * @file color.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 17, 2015
 */


#ifndef VIDEO_INCLUDE_ATTRIBUTES_H_
#define VIDEO_INCLUDE_ATTRIBUTES_H_

#include "convert.h"
#include "strings.h"

namespace crap
{

namespace align
{
	enum value
	{
		left			= 1<<0,
		center			= 1<<1,
		right			= 1<<2,
		top				= 1<<3,
		middle			= 1<<4,
		bottom			= 1<<5,
		baseline		= 1<<6,
		top_left		= left | top,
		top_center		= center | top,
		top_right		= right | top,
		middle_left 	= left | middle,
		middle_center	= center | middle,
		middle_right	= right | middle,
		bottom_left		= left | bottom,
		bottom_center	= center | bottom,
		bottom_right	= right | bottom
	};

	static const uint32_t IDS[] = {
			CRAP_HASH_STRING("left"),
			CRAP_HASH_STRING("center"),
			CRAP_HASH_STRING("right"),
			CRAP_HASH_STRING("top"),
			CRAP_HASH_STRING("middle"),
			CRAP_HASH_STRING("bottom"),
			CRAP_HASH_STRING("baseline"),
			CRAP_HASH_STRING("top_left"),
			CRAP_HASH_STRING("top_center"),
			CRAP_HASH_STRING("top_right"),
			CRAP_HASH_STRING("middle_left"),
			CRAP_HASH_STRING("middle_center"),
			CRAP_HASH_STRING("middle_right"),
			CRAP_HASH_STRING("bottom_left"),
			CRAP_HASH_STRING("bottom_center"),
			CRAP_HASH_STRING("bottom_right")
	};

	static const uint32_t VALUES[] = {
			top,
			center,
			right,
			top,
			middle,
			bottom,
			baseline,
			top_left,
			top_center,
			top_right,
			middle_left,
			middle_center,
			middle_right,
			bottom_left,
			bottom_center,
			bottom_right
	};
}

struct TextAlignment
{
	uint32_t value;
	CRAP_INLINE TextAlignment( uint32_t v=0 ) : value(v) {}
};

template<>
CRAP_INLINE TextAlignment convert<string64, TextAlignment>( const string64& variable )
{
    string_hash hash( variable.c_str());
    for( uint32_t i=0; i< 16; ++i )
    {
    	if( align::IDS[i] == hash.hash() )
    		return TextAlignment(align::VALUES[i]);
    }
    return TextAlignment();
}

} /* namespace crap */


#endif /* VIDEO_INCLUDE_ATTRIBUTES_H_ */
