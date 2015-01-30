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

#include "utilities.h"
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

	CRAP_INLINE const float32_t& getposX( void ) const { return _data.position[0]; }
	static void setposX( Transformation2D* instance, const string64& data )
	{ instance->_data.position[0] = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& getposY( void ) const { return _data.position[1]; }
	static void setposY( Transformation2D* instance, const string64& data )
	{ instance->_data.position[1] = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& getrotation( void ) const { return _data.rotation; }
	static void setrotation( Transformation2D* instance, const string64& data )
	{ instance->_data.rotation = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& getscale( void ) const { return _data.scale; }
	static void setscale( Transformation2D* instance, const string64& data )
	{ instance->_data.scale = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& getdamping( void ) const { return _data.damping; }
	static void setdamping( Transformation2D* instance, const string64& data )
	{ instance->_data.damping = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& getfriction( void ) const { return _data.friction; }
	static void setfriction( Transformation2D* instance, const string64& data )
	{ instance->_data.friction = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& getrestitution( void ) const { return _data.restitution; }
	static void setrestitution( Transformation2D* instance, const string64& data )
	{ instance->_data.restitution = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& gettorque( void ) const { return _data.torque; }
	static void settorque( Transformation2D* instance, const string64& data )
	{ instance->_data.torque = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& getvelocityX( void ) const { return _data.velocity[0]; }
	static void setvelocityX( Transformation2D* instance, const string64& data )
	{ instance->_data.velocity[0] = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE const float32_t& getvelocityY( void ) const { return _data.velocity[1]; }
	static void setvelocityY( Transformation2D* instance, const string64& data )
	{ instance->_data.velocity[1] = crap::convert<string64, float32_t>(data); }

	CRAP_INLINE attributes_2d* getData( void ) { return &_data; }

private:

	attributes_2d	_data;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_TRANSFORMATION2D_H_ */
