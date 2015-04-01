#pragma once

#include "net/ISocket.h"
#include "io/IStream.h"


//! Data stream socket interface
/*!
This interface defines the methods common to all network sockets that
represent a full-duplex data stream.
*/

class IDataSocket :	public ISocket, public IStream
{
public:

	IDataSocket(void);
	
	virtual ~IDataSocket(void){}

	// ISocket Overrides
	virtual void bind(const NetworkAddress & ) = 0;
	virtual void close() = 0;
	// End ISocket Overrides

	// IStream overrides
	virtual UInt32		read(void* buffer, UInt32 n) = 0;
	virtual void		write(const void* buffer, UInt32 n) = 0;
	virtual void		flush() = 0;
	virtual void		shutdownInput() = 0;
	virtual void		shutdownOutput() = 0;
	virtual bool		isReady() const = 0;
	virtual UInt32		getSize() const = 0;
	// End IStream overrides

	//!@ Connect socket
	/*!
	Attempt to connect to a remote endpoint.  This returns immediately
	and sends a connected event when successful or a connection failed
	event when it fails.  The stream acts as if shutdown for input and
	output until the stream connects.
	*/
	virtual void connect(const NetworkAddress &) = 0;
};

