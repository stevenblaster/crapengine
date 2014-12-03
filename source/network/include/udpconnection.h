/*!
 * @file connection.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 2, 2014
 */
#pragma once

#ifndef NETWORK_INCLUDE_UDPCONNECTION_H_
#define NETWORK_INCLUDE_UDPCONNECTION_H_

#include "arraymap.h"
#include "sockets.h"
#include "packetlayer.h"

namespace crap
{

class UdpConnection
{
public:

	bool receive( void );

	bool compareChecksum( ConnectionHeader* CRAP_RESTRICT header ) const;

private:

	bool handleLogin( ConnectionHeader* CRAP_RESTRICT header, ConnectionInformation& info );

	array_map<uint32_t, ConnectionInformation> _connections;

	socket_t _socket;
	uint16_t _port;
	uint32_t _packet_size;
};

}

#endif /* NETWORK_INCLUDE_UDPCONNECTION_H_ */
