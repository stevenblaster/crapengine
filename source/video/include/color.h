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


#ifndef VIDEO_INCLUDE_COLOR_H_
#define VIDEO_INCLUDE_COLOR_H_

#include "convert.h"
#include "strings.h"

namespace crap
{

typedef struct s_argb
{
	union
	{
		uint32_t value;
		struct
		{
			uint32_t blue 	: 8;
			uint32_t green	: 8;
			uint32_t red	: 8;
			uint32_t alpha	: 8;
		};
	};
}
ColorARGB;

typedef struct s_rgba
{
	union
	{
		uint32_t value;
		struct
		{
			uint32_t alpha	: 8;
			uint32_t blue 	: 8;
			uint32_t green	: 8;
			uint32_t red	: 8;
		};
	};
}
ColorRGBA;

template<>
CRAP_INLINE string64 convert<ColorARGB, string64>( const ColorARGB& variable )
{
    string64 buf;
    sprintf( buf.pointer().as_char, "%u", variable.value );
    return buf;
}

template<>
CRAP_INLINE string64 convert<ColorRGBA, string64>( const ColorRGBA& variable )
{
    string64 buf;
    sprintf( buf.pointer().as_char, "%u", variable.value );
    return buf;
}

} /* namespace crap */


#endif /* VIDEO_INCLUDE_COLOR_H_ */
