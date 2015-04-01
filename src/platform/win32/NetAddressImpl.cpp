#include "platform/win32/NetAddressImpl.h"
#include "platform/win32/NetWorkWin.h"

NetAddressImpl::NetAddressImpl()
{
}

NetAddressImpl::NetAddressImpl(struct sockaddr socka)
{
	m_addr.sa_family = socka.sa_family;
	memcpy(m_addr.sa_data,socka.sa_data,_WIN32_WINNT_SA_DATA_LEN);
}

NetAddressImpl::NetAddressImpl(EADDRESSFAMILY addrFamily)
{
	struct sockaddr_in * sock = NULL;
	sock = (struct sockaddr_in *)& m_addr;
	sock->sin_family = s_family[addrFamily];
	sock->sin_port = 0;
	sock->sin_addr.s_addr  = INADDR_ANY;
}

NetAddressImpl::NetAddressImpl(const NetAddressImpl & netaddressIpl)
{
	*this = netaddressIpl;
}

NetAddressImpl & NetAddressImpl::operator = (const NetAddressImpl& netaddressIpl)
{
	if(this == &netaddressIpl)
		return *this;
	m_addr.sa_family = netaddressIpl.m_addr.sa_family;
	memcpy(m_addr.sa_data,netaddressIpl.m_addr.sa_data,_WIN32_WINNT_SA_DATA_LEN);
	return *this;
}