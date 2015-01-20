/*!
 * @file transformation2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 16, 2015
 */


#ifndef PLUGINS_COMPONENTS_INCLUDE_TRANSFORMATION2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_TRANSFORMATION2D_H_

#include "attributes.h"
#include "component.h"

/**
 * @namespace crap
 */
namespace crap
{

class Transformation2D : public Component
{
public:
	Transformation2D( void );
	virtual ~Transformation2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	float32_t* getposX( void ) { return &_data.pos_x; }
	static void setposX( Transformation2D* instance, const string64& data )
	{ instance->_data.pos_x = crap::convert<string64, float32_t>(data); }

	float32_t* getposY( void ) { return &_data.pos_y; }
	static void setposY( Transformation2D* instance, const string64& data )
	{ instance->_data.pos_y = crap::convert<string64, float32_t>(data); }

	float32_t* getrotation( void ) { return &_data.rotation; }
	static void setrotation( Transformation2D* instance, const string64& data )
	{ instance->_data.rotation = crap::convert<string64, float32_t>(data); }

	float32_t* getscale( void ) { return &_data.scale; }
	static void setscale( Transformation2D* instance, const string64& data )
	{ instance->_data.scale = crap::convert<string64, float32_t>(data); }

	Transformation2Ddata* getData( void );

private:
	Transformation2Ddata	_data;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_TRANSFORMATION2D_H_ */
