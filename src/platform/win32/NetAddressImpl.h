#pragma once

//! NetAddressImpl
/*!
NetAddress Implement on win32 platform.
*/

#include <WinSock2.h>
#include <Windows.h>

#define _WIN32_WINNT_SA_DATA_LEN 14

#include "net/INetWork.h"

class NetAddressImpl
{
public:
	NetAddressImpl();
	NetAddressImpl(EADDRESSFAMILY);
	NetAddressImpl(struct sockaddr socka);
	NetAddressImpl(const NetAddressImpl & netaddressIpl);
	NetAddressImpl & operator=(const NetAddressImpl&);
public:
	struct sockaddr		m_addr;
};

