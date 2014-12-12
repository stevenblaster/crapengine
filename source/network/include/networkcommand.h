/*!
 * @file networkcommand.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 11, 2014
 */


#ifndef NETWORK_INCLUDE_NETWORKCOMMAND_H_
#define NETWORK_INCLUDE_NETWORKCOMMAND_H_

#include "strings.h"

namespace crap
{

class NetworkCommandQueue;

class NetworkCommand
{
public:

	NetworkCommand( string_hash commandID );

	virtual ~NetworkCommand( void );

	CRAP_INLINE
	uint32_t getID( void ) const;

	virtual uint32_t dataSize( void ) const;

	virtual void readData( pointer_t<void> pointer );
	virtual void writeData( pointer_t<void> pointer );

	virtual bool execute( uint32_t user_id, uint32_t deltatime );

	static void setCommandQueue( NetworkCommandQueue* queue );

private:
	uint32_t _id;
	static NetworkCommandQueue* _queue;
};

uint32_t NetworkCommand::getID( void ) const
{
	return _id;
}

} /* namespace crap */

#endif /* NETWORK_INCLUDE_NETWORKCOMMAND_H_ */
