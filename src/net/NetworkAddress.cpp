#include "net/NetworkAddress.h"
#include "arch/Arch.h"

NetworkAddress::NetworkAddress(void):
m_hostname(NULL),m_port(0),m_address(NULL)
{
}

NetworkAddress::NetworkAddress(const int port):
m_hostname(NULL),m_port(port),m_address(NULL)
{
	m_address = ARCH->newAnyAddr(INET);
}


NetworkAddress::NetworkAddress(const String & hostname,const int port):
m_hostname(hostname),m_port(port),m_address(NULL)
{
	m_address = ARCH->newAnyAddr(INET);
}

NetworkAddress::NetworkAddress(const NetworkAddress & networkaddress)
{
	*this = networkaddress;
}


NetworkAddress & NetworkAddress::operator=(const NetworkAddress & networkaddress)
{
	if(this == &networkaddress)
		return *this;

	delete m_address;

	m_address = ARCH->newAnyAddr(INET);
	m_address = networkaddress.getNetAddress();
	m_hostname = networkaddress.getHostName();
	m_port = networkaddress.getPort();

}


NetworkAddress::~NetworkAddress(void)
{
	if(m_address != NULL)
		delete m_address;
}
