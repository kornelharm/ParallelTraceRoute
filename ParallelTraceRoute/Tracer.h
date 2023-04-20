// Kornel Harmati, CSCE 463, Spring 2023
#pragma once
#include "pch.h"

#define IP_HDR_SIZE		20		// RFC 791
#define ICMP_HDR_SIZE	8		// RFC 792
#define MAX_SIZE		65200	// max ICMP payload from program
#define MAX_ICMP_SIZE	(MAX_SIZE + ICMP_HDR_SIZE)	// max size of IP datagram
#define MAX_REPLY_SIZE	(IP_HDR_SIZE + ICMP_HDR_SIZE + MAX_ICMP_SIZE)	// max size of ICMP reply

#define ICMP_ECHO_REPLY		0
#define ICMP_DEST_UNREACH	3
#define ICMP_TTL_EXPIRED	11
#define ICMP_ECHO_REQUEST	8

#pragma pack(push, 1)
class IPHeader {
public:
	u_char	h_len : 4;		// Length of header in DWORDs
	u_char	version : 4;	// IP version
	u_char	h_len : 4;		// Type of service
	u_short	len;			// Type of packet
	u_short	ident;			// Unique identifier
	u_short	flags;			// Flags & fragment Offset
	u_char	ttl;			// Time to live
	u_char	proto;			// Protocol # (TCP=6, UDP=17...)
	u_short	checksum;
	unsigned long	srcIP;
	unsigned long	destIP;
};

class ICMPHeader{
public:
	u_char	type;			// ICMP packet type
	u_char	code;			// Subcode
	u_short	checksum;		// ICMP checksum
	u_short	id;				// ID from application
	u_short	seq;			// Sequence number from application
};
#pragma pack(pop)

// Returns the checksum on the specified buffer
u_short checksum(u_short *buffer, int size);

// Fills a buffer with the necessary information to make an ICMP echo request
void fillICMPRequest(ICMPHeader *head, int ttl);

// Sends an echo request to a host described by socket
int sendProbe(SOCKET socket, int ttl);

// Updates results with new TraceHop from assigned IP, returns 0 on success or >0 for failure
int receiveProbe(SOCKET socket, in_addr fromIP, std::map<in_addr, TraceHop> *results, double timeout);

// Defines the parameters of a specific hop
class TraceHop {
public:
	in_addr IP;
	double RTT;
	std::string name;
};

class Route {
public:
	in_addr destination;
	std::list<TraceHop> hops;
	bool success;

	int hops(); // Returns number of hops
};

class Tracer
{
private:
	SOCKET socket;
	bool performDNS;
public:
	Route performTrace(in_addr ip);
};

