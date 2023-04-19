// Kornel Harmati, CSCE 463, Spring 2023
#include "pch.h"
#include <iostream>

bool init() {
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		return false;
	}
	srand(time(NULL));
	return true;
}

int main()
{
	if (!init()) {
		exit(1);
	}
    std::cout << "Hello World!\n";
}
