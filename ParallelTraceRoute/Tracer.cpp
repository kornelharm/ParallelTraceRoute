#include "pch.h"
#include "Tracer.h"

u_short checksum(u_short *buffer, int size){
	unsigned long cksum = 0;
	while(size > 1){
		cksum += *buffer++;
		size -= sizeof(u_short);
	}
	if(size){
		cksum += *(u_char *)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xFFFF);
	return (u_short)(~cksum);
}

void fillICMPRequest(ICMPHeader *head, int ttl){
	head->type = ICMP_ECHO_REQUEST;
	head->code = 0;
	head->checksum = 0;
	head->id = (u_short) GetCurrentProcessId();
	head->seq = ttl;
	head->checksum = checksum((u_short *)head, sizeof(ICMPHeader));
}
