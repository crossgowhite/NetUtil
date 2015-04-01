#pragma once

#include "net/INetWork.h"
#include "platform/win32/NetAddressImpl.h"
#include <WinSock2.h>
#include <Windows.h>

//! NetWorkWin
/*!
NetWorkWin Implement on win32 platform.
	*	Interface for create/read/write Socket and etc
*/

static const int s_family[] = {
	PF_UNSPEC,
	PF_INET
};

static const int s_type[] = {
	SOCK_DGRAM,
	SOCK_STREAM
};


class NetWorkWin;
#define ArchNetWork NetWorkWin

class ArchSocketImpl {
public:
	SOCKET				m_socket;	//Socket ID
	int					m_refCount;	//Socket Ref
	WSAEVENT			m_event;	
	bool				m_pollWrite;
};

class NetWorkWin : public INetWork
{
public:
	NetWorkWin(){}
	virtual ~ NetWorkWin(){}

private:
	void initModule(HMODULE module);

public:
	virtual bool			init();
	virtual ArchSocket		newSocket(EADDRESSFAMILY, SocketType);
	virtual ArchNetAddress	newAnyAddr(EADDRESSFAMILY);
	virtual void			closeSocket(ArchSocket);
	virtual void			bindSocket(ArchSocket, ArchNetAddress);
	virtual void			listenOnSocket(ArchSocket);
	virtual ArchSocket		acceptSocket(ArchSocket, ArchNetAddress);
	virtual bool			connectSocket(ArchSocket, ArchNetAddress);
	virtual size_t			readSocket(ArchSocket, void*, size_t);
	virtual size_t			writeSocket(ArchSocket, const void*, size_t);
};