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
	unsigned char	h_len : 4;		// Length of header in DWORDs
	unsigned char	version : 4;	// IP version
	unsigned char	h_len : 4;		// Type of service
	unsigned short	len;			// Type of packet
	unsigned short	ident;			// Unique identifier
	unsigned short	flags;			// Flags & fragment Offset
	unsigned char	ttl;			// Time to live
	unsigned char	proto;			// Protocol # (TCP=6, UDP=17...)
	unsigned short	checksum;
	unsigned long	srcIP;
	unsigned long	destIP;
};

class ICMPHeader{
public:
	unsigned char	type;			// ICMP packet type
	unsigned char	code;			// Subcode
	unsigned short	checksum;		// ICMP checksum
	unsigned short	id;				// ID from application
	unsigned short	seq;			// Sequence number from application
};
#pragma pack(pop)

unsigned short checksum(unsigned short *buffer, int size);
void fillICMPRequest(ICMPHeader *head, int ttl);

class Tracer
{
private:

public:
};

