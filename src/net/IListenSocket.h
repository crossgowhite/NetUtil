#pragma once

#include "net/ISocket.h"

//! Listen socket interface
/*!
This interface inherit from ISocket, use for the listen & bind socket
*/

class IDataSocket;

class IListenSocket : public ISocket
{
public:
	IListenSocket(void){}
	virtual ~IListenSocket(void){}

public:

	// ISocket Overrides

	//!@ bind socket to networkAdress
	virtual void bind(const NetworkAddress & ) = 0;

	//!@ close socket
	virtual void close() = 0;

	// End ISocket Overrides

	/*!@
	Accept a connection, returning a socket representing the full-duplex
	data stream.  Returns NULL if no socket is waiting to be accepted.
	This is only valid after a call to \c bind().
	*/
	virtual IDataSocket * accept() = 0;

	//! Delete connection socket
	/*!@
	This is used when the socket was created but not adopted by a client
	proxy.
	*/
	virtual void deleteSocket(void *) = 0;
};

