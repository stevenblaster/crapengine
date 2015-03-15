
/*!
 * @file audioplugin.cpp
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
#define CRAP_DL 1

#include "config/crap_platform.h"
#include "config/crap_compiler.h"

#include "componenttype.h"
#include "circle2d.h"
#include "rectangle2d.h"
#include "roundedrectangle2d.h"
#include "text2d.h"
#include "system.h"
#include "plugin.h"
#include "texture2d.h"
#include "button2d.h"
#include "filmstrip2d.h"
#include "animation2d.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( Video2DPlugin )
{
public:
	Video2DPlugin( System* system ) :
		_circle2d("Circle2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_rectangle2d("Rectangle2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_roundedRectangle2d("RoundedRectangle2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_text2d("Text2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_texture2d("Texture2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_button2d("Button2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_filmstrip2d("FilmStrip2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_animation2d("Animation2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10)
	{
	}

	~Video2DPlugin( void )
	{

	}

    virtual void init( System* system )
    {
    }

    virtual void deinit( System* system )
    {
    }

    uint32_t id( void )
    {
    	return string_hash("Video2DPlugin").hash();
    }

private:

    crap::ComponentType<Circle2D>	_circle2d;
    crap::ComponentType<Rectangle2D>	_rectangle2d;
    crap::ComponentType<RoundedRectangle2D> _roundedRectangle2d;
    crap::ComponentType<Text2D> _text2d;
    crap::ComponentType<Texture2D>  _texture2d;
    crap::ComponentType<Button2D>  _button2d;
    crap::ComponentType<FilmStrip2D>  _filmstrip2d;
    crap::ComponentType<Animation2D>  _animation2d;
};

CRAP_PLUGIN_FACTORY( Video2DPlugin )

} /* namespace crap */
