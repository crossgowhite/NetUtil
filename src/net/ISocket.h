#pragma once

#include "common/IInterface.h"


//! Generic socket interface
/*!
This interface defines the methods common to all network sockets.
*/

class NetworkAddress;

class ISocket : public IInterface
{
public:
	ISocket(void){}
	virtual ~ISocket(void){}

public:

	//!@ bind socket to networkAdress
	virtual void bind(const NetworkAddress & ) = 0;

	//!@ close socket
	virtual void close() = 0;
};

