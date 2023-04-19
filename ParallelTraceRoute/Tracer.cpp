#include "pch.h"
#include "Tracer.h"

unsigned short checksum(unsigned short *buffer, int size){
	unsigned long cksum = 0;
	while(size > 1){
		cksum += *buffer++;
		size -= sizeof(unsigned short);
	}
	if(size){
		cksum += *(unsigned char *)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xFFFF);
	return (unsigned short)(~cksum);
}

void fillICMPRequest(ICMPHeader *head, int ttl){
	head->type = ICMP_ECHO_REQUEST;
	head->code = 0;
	head->checksum = 0;
	head->id = (unsigned short) GetCurrentProcessId();
	head->seq = ttl;
	head->checksum = checksum((unsigned short *)head, sizeof(ICMPHeader));
}
