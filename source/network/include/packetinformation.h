/*!
 * @file packetlayer.h
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

#ifndef NETWORK_INCLUDE_PACKETINFORMATION_H_
#define NETWORK_INCLUDE_PACKETINFORMATION_H_

#include "utilities.h"
#include "sockets.h"

#define CRAP_MAX_PACKET_SIZE (sizeof(crap::ConnectionHeader) + sizeof(crap::ReliabilityHeader) + 4*16)

namespace crap
{

struct ConnectionHeader
{
    uint32_t user_id		:32;
    uint32_t checksum 		:16; //checksum of the header
    uint32_t size 			: 8; //complete size of packet in 32 bit parts
    uint32_t data_flag 		: 1;
    uint32_t sync_flag 		: 1;
    uint32_t resync_flag	: 1;
    uint32_t login_flag 	: 1;
    uint32_t logoff_flag 	: 1;
    uint32_t reserved_flag1 : 1;
    uint32_t reserved_flag2 : 1;
    uint32_t reserved_flag3 : 1;
};

struct ConnectionInformation
{
	ipv4_t		user_ip;
	uint32_t 	user_time;
	port_t		user_port;
};

struct ReliabilityHeader
{
    uint32_t checksum				:32;	// checksum of whole packet
    uint32_t message_id 			: 8;
    uint32_t number_total 			: 8;
    uint32_t number_current 		: 8;
    uint32_t sequence_flag 			: 1;
    uint32_t acknowledge_flag 		: 1;
    uint32_t fire_and_forget_flag 	: 1;
    uint32_t reserved1_flag 		: 1;
    uint32_t reserved2_flag 		: 1;
    uint32_t reserved3_flag 		: 1;
    uint32_t reserved4_flag 		: 1;
    uint32_t reserved5_flag 		: 1;
};

struct ReliabilityOutgoing
{
	uint32_t user_id;
	uint32_t age;
	uint32_t size;
	uint8_t data[CRAP_MAX_PACKET_SIZE];
};

struct ReliabilityIncoming
{
	uint32_t user_id;
	uint32_t age;
    uint32_t number;
    uint32_t last_size;
    ReliabilityHeader info[255];
	uint8_t data[ (CRAP_MAX_PACKET_SIZE-sizeof(ConnectionHeader)-sizeof(ReliabilityHeader)) * 255 ];
};

struct NetworkCommandData
{
	uint32_t userID;
	uint32_t commandID;
	bool	fireAndForget;
	uint8_t data[ (CRAP_MAX_PACKET_SIZE-sizeof(ConnectionHeader)-sizeof(ReliabilityHeader)-sizeof(uint32_t)) * 255 ];
};

} /* namespace crap */

#endif /* NETWORK_INCLUDE_PACKETINFORMATION_H_ */
