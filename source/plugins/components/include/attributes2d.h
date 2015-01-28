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


#ifndef PLUGINS_COMPONENTS_INCLUDE_ATTRIBUTES2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_ATTRIBUTES2D_H_

#include "general.h"
#include "component.h"

/**
 * @namespace crap
 */
namespace crap
{

class Attributes2D : public Component
{
public:
	Attributes2D( void );
	virtual ~Attributes2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	float32_t* getposX( void ) { return &_data.pos_x; }
	static void setposX( Attributes2D* instance, const string64& data )
	{ instance->_data.pos_x = crap::convert<string64, float32_t>(data); }

	float32_t* getposY( void ) { return &_data.pos_y; }
	static void setposY( Attributes2D* instance, const string64& data )
	{ instance->_data.pos_y = crap::convert<string64, float32_t>(data); }

	float32_t* getwidth( void ) { return &_data.width; }
	static void setwidth( Attributes2D* instance, const string64& data )
	{ instance->_data.width = crap::convert<string64, float32_t>(data); }

	float32_t* getheight( void ) { return &_data.height; }
	static void setheight( Attributes2D* instance, const string64& data )
	{ instance->_data.height = crap::convert<string64, float32_t>(data); }

	float32_t* getradius( void ) { return &_data.radius; }
	static void setradius( Attributes2D* instance, const string64& data )
	{ instance->_data.radius = crap::convert<string64, float32_t>(data); }

	float32_t* getrotation( void ) { return &_data.rotation; }
	static void setrotation( Attributes2D* instance, const string64& data )
	{ instance->_data.rotation = crap::convert<string64, float32_t>(data); }

	float32_t* getscale( void ) { return &_data.scale; }
	static void setscale( Attributes2D* instance, const string64& data )
	{ instance->_data.scale = crap::convert<string64, float32_t>(data); }

	float32_t* getvelX( void ) { return &_data.linear_velocity[0]; }
	static void setvelX( Attributes2D* instance, const string64& data )
	{ instance->_data.linear_velocity[0] = crap::convert<string64, float32_t>(data); }

	float32_t* getvelY( void ) { return &_data.linear_velocity[1]; }
	static void setvelY( Attributes2D* instance, const string64& data )
	{ instance->_data.linear_velocity[1] = crap::convert<string64, float32_t>(data); }

	float32_t* getangVel( void ) { return &_data.angular_velocity; }
	static void setangVel( Attributes2D* instance, const string64& data )
	{ instance->_data.angular_velocity = crap::convert<string64, float32_t>(data); }

	float32_t* getdamping( void ) { return &_data.linear_damping; }
	static void setdamping( Attributes2D* instance, const string64& data )
	{ instance->_data.linear_damping = crap::convert<string64, float32_t>(data); }

	float32_t* getangDamping( void ) { return &_data.angular_damping; }
	static void setangDamping( Attributes2D* instance, const string64& data )
	{ instance->_data.angular_damping = crap::convert<string64, float32_t>(data); }

	float32_t* getPath( void ) { return _data.path; }
	void setPath( const float32_t* ptr )
	{ _data.path = ptr; }

	uint32_t getPathSize( void ) { return _data.pathsize; }
	void setPathSize( const uint32_t pathSize )
	{ _data.pathsize = pathSize; }

	Attributes2Ddata* getData( void );

private:
	Attributes2Ddata	_data;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_ATTRIBUTES2D_H_ */
