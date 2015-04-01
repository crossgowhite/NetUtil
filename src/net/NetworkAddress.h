#pragma once


//! NetworkAddress
/*!
NetworkAddress depend on WIN32/UNIX Platform.
*Properties:  1.	HostName
			  2.	port
			  3.	struct sockaddr info
			  struct sockaddr {
			  u_short sa_family;  -->address family
			  char    sa_data[14];  --> up to 14 bytes of direct address 
			  };
*/

#include "arch/ArchNetWork.h"

class NetworkAddress
{
public:
	NetworkAddress(void);
	NetworkAddress(const int port);
	NetworkAddress(const String &hostname,const int port);
	NetworkAddress(const NetworkAddress &);
	~NetworkAddress(void);

public:
	NetworkAddress & operator=(const NetworkAddress&);

public:
	const String getHostName() const { return m_hostname; }
	const int getPort() const { return m_port; }
	const ArchNetAddress getNetAddress() const { return m_address; }
private:
	ArchNetAddress m_address;
	String m_hostname;
	int m_port;
};

