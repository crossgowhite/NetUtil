#pragma once

#include "common/IInterface.h"
//! INetWork
/*!
INetWork Pure Virtual base class for socket action.
	*	Interface for create/read/write Socket and etc
*/

class ArchSocketImpl;
typedef ArchSocketImpl * ArchSocket;

class NetAddressImpl;
typedef NetAddressImpl * ArchNetAddress;

typedef enum 
{
	IUNKNOW = 0,
	INET = 1
}EADDRESSFAMILY;

typedef enum {
	IDGRAM,
	ISTREAM
}SocketType;

class INetWork : public IInterface
{
public:
/*	INetWork(){}*/

	virtual ~INetWork(){}

	//! Create a new socket
	virtual ArchSocket		newSocket(EADDRESSFAMILY, SocketType) = 0;

	//! Create an "any" network address
	virtual ArchNetAddress	newAnyAddr(EADDRESSFAMILY) = 0;

	//! Close One Socket
	virtual void			closeSocket(ArchSocket) = 0;

	//! Bind One Socket with NetAddress
	virtual void			bindSocket(ArchSocket, ArchNetAddress) = 0;

	//! Listen On Socket
	virtual void			listenOnSocket(ArchSocket) = 0;

	//! Accept Socket
	virtual ArchSocket		acceptSocket(ArchSocket, ArchNetAddress) = 0;

	//! Connect Socket
	virtual bool			connectSocket(ArchSocket, ArchNetAddress) = 0;

	//! Read From Socket
	virtual size_t			readSocket(ArchSocket, void*, size_t) = 0;

	//! Write to Socket
	virtual size_t			writeSocket(ArchSocket, const void*, size_t) = 0;
};


