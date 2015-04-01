#include "platform/win32/NetWorkWin.h"
#include "arch/Arch.h"

static SOCKET (PASCAL FAR *accept_winsock)(SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen);
static int (PASCAL FAR *bind_winsock)(SOCKET s, const struct sockaddr FAR *addr, int namelen);
static int (PASCAL FAR *close_winsock)(SOCKET s);
static int (PASCAL FAR *connect_winsock)(SOCKET s, const struct sockaddr FAR *name, int namelen);
static int (PASCAL FAR *gethostname_winsock)(char FAR * name, int namelen);
static int (PASCAL FAR *getsockerror_winsock)(void);
static int (PASCAL FAR *getsockopt_winsock)(SOCKET s, int level, int optname, void FAR * optval, int FAR *optlen);
static u_short (PASCAL FAR *htons_winsock)(u_short v);
static char FAR * (PASCAL FAR *inet_ntoa_winsock)(struct in_addr in);
static unsigned long (PASCAL FAR *inet_addr_winsock)(const char FAR * cp);
static int (PASCAL FAR *ioctl_winsock)(SOCKET s, int cmd, void FAR * data);
static int (PASCAL FAR *listen_winsock)(SOCKET s, int backlog);
static u_short (PASCAL FAR *ntohs_winsock)(u_short v);
static int (PASCAL FAR *recv_winsock)(SOCKET s, void FAR * buf, int len, int flags);
static int (PASCAL FAR *select_winsock)(int nfds, fd_set FAR *readfds, fd_set FAR *writefds, fd_set FAR *exceptfds, const struct timeval FAR *timeout);
static int (PASCAL FAR *send_winsock)(SOCKET s, const void FAR * buf, int len, int flags);
static int (PASCAL FAR *setsockopt_winsock)(SOCKET s, int level, int optname, const void FAR * optval, int optlen);
static int (PASCAL FAR *shutdown_winsock)(SOCKET s, int how);
static SOCKET (PASCAL FAR *socket_winsock)(int af, int type, int protocol);
static struct hostent FAR * (PASCAL FAR *gethostbyaddr_winsock)(const char FAR * addr, int len, int type);
static struct hostent FAR * (PASCAL FAR *gethostbyname_winsock)(const char FAR * name);
static int (PASCAL FAR *WSACleanup_winsock)(void);
static int (PASCAL FAR *WSAFDIsSet_winsock)(SOCKET, fd_set FAR * fdset);
static WSAEVENT (PASCAL FAR *WSACreateEvent_winsock)(void);
static BOOL (PASCAL FAR *WSACloseEvent_winsock)(WSAEVENT);
static BOOL (PASCAL FAR *WSASetEvent_winsock)(WSAEVENT);
static BOOL (PASCAL FAR *WSAResetEvent_winsock)(WSAEVENT);
static int (PASCAL FAR *WSAEventSelect_winsock)(SOCKET, WSAEVENT, long);
static DWORD (PASCAL FAR *WSAWaitForMultipleEvents_winsock)(DWORD, const WSAEVENT FAR*, BOOL, DWORD, BOOL);
static int (PASCAL FAR *WSAEnumNetworkEvents_winsock)(SOCKET, WSAEVENT, LPWSANETWORKEVENTS);


#define setfunc(var, name, type, module) var = (type)netGetProcAddress(module, name)

static FARPROC	netGetProcAddress(HMODULE module, LPCSTR name)
{
	FARPROC func = ::GetProcAddress(module, name);
	if (!func) {
		ARCH->writeConsole(kERROR,"Cannot Get Func Ptr");
	}
	return func;
}


bool NetWorkWin::init()
{
	initModule((HMODULE)LoadLibrary(L"ws2_32.dll"));
	return true;
}


void NetWorkWin::initModule(HMODULE module)
{
	if(!module){
		ARCH->writeConsole(kERROR,"Cannot Open ws2_32.dll");
		return;
	}

	// get startup function address
	int (PASCAL FAR *startup)(WORD, LPWSADATA);
	setfunc(startup, "WSAStartup", int(PASCAL FAR*)(WORD, LPWSADATA),module);

	// startup network library
	WORD version = MAKEWORD(2 /*major*/, 0 /*minor*/);
	WSADATA data;
	int err = startup(version, &data);
	if (data.wVersion != version) {
		ARCH->writeConsole(kERROR,"Setup ws2_32.dll fail");
		return;
	}

	setfunc(accept_winsock,"accept",SOCKET (PASCAL FAR *)(SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen),module);
	setfunc(bind_winsock,"bind", int (PASCAL FAR *)(SOCKET s, const struct sockaddr FAR *addr, int namelen),module);
	setfunc(close_winsock, "closesocket", int (PASCAL FAR *)(SOCKET s),module);
	setfunc(connect_winsock, "connect", int (PASCAL FAR *)(SOCKET s, const struct sockaddr FAR *name, int namelen),module);
	setfunc(gethostname_winsock, "gethostname", int (PASCAL FAR *)(char FAR * name, int namelen),module);
	setfunc(getsockerror_winsock, "WSAGetLastError", int (PASCAL FAR *)(void),module);
	setfunc(getsockopt_winsock, "getsockopt", int (PASCAL FAR *)(SOCKET s, int level, int optname, void FAR * optval, int FAR *optlen),module);
	setfunc(htons_winsock, "htons", u_short (PASCAL FAR *)(u_short v),module);
	setfunc(inet_ntoa_winsock, "inet_ntoa", char FAR * (PASCAL FAR *)(struct in_addr in),module);
	setfunc(inet_addr_winsock, "inet_addr", unsigned long (PASCAL FAR *)(const char FAR * cp),module);
	setfunc(ioctl_winsock, "ioctlsocket", int (PASCAL FAR *)(SOCKET s, int cmd, void FAR *),module);
	setfunc(listen_winsock, "listen", int (PASCAL FAR *)(SOCKET s, int backlog),module);
	setfunc(ntohs_winsock, "ntohs", u_short (PASCAL FAR *)(u_short v),module);
	setfunc(recv_winsock, "recv", int (PASCAL FAR *)(SOCKET s, void FAR * buf, int len, int flags),module);
	setfunc(select_winsock, "select", int (PASCAL FAR *)(int nfds, fd_set FAR *readfds, fd_set FAR *writefds, fd_set FAR *exceptfds, const struct timeval FAR *timeout),module);
	setfunc(send_winsock, "send", int (PASCAL FAR *)(SOCKET s, const void FAR * buf, int len, int flags),module);
	setfunc(setsockopt_winsock, "setsockopt", int (PASCAL FAR *)(SOCKET s, int level, int optname, const void FAR * optval, int optlen),module);
	setfunc(shutdown_winsock, "shutdown", int (PASCAL FAR *)(SOCKET s, int how),module);
	setfunc(socket_winsock, "socket", SOCKET (PASCAL FAR *)(int af, int type, int protocol),module);
	setfunc(gethostbyaddr_winsock, "gethostbyaddr", struct hostent FAR * (PASCAL FAR *)(const char FAR * addr, int len, int type),module);
	setfunc(gethostbyname_winsock, "gethostbyname", struct hostent FAR * (PASCAL FAR *)(const char FAR * name),module);
	setfunc(WSACleanup_winsock, "WSACleanup", int (PASCAL FAR *)(void),module);
	setfunc(WSAFDIsSet_winsock, "__WSAFDIsSet", int (PASCAL FAR *)(SOCKET, fd_set FAR *),module);
	setfunc(WSACreateEvent_winsock, "WSACreateEvent", WSAEVENT (PASCAL FAR *)(void),module);
	setfunc(WSACloseEvent_winsock, "WSACloseEvent", BOOL (PASCAL FAR *)(WSAEVENT),module);
	setfunc(WSASetEvent_winsock, "WSASetEvent", BOOL (PASCAL FAR *)(WSAEVENT),module);
	setfunc(WSAResetEvent_winsock, "WSAResetEvent", BOOL (PASCAL FAR *)(WSAEVENT),module);
	setfunc(WSAEventSelect_winsock, "WSAEventSelect", int (PASCAL FAR *)(SOCKET, WSAEVENT, long),module);
	setfunc(WSAWaitForMultipleEvents_winsock, "WSAWaitForMultipleEvents", DWORD (PASCAL FAR *)(DWORD, const WSAEVENT FAR*, BOOL, DWORD, BOOL),module);
	setfunc(WSAEnumNetworkEvents_winsock, "WSAEnumNetworkEvents", int (PASCAL FAR *)(SOCKET, WSAEVENT, LPWSANETWORKEVENTS),module);

}


ArchSocket	NetWorkWin::newSocket(EADDRESSFAMILY addrFamily, SocketType sockType)
{
	SOCKET fd = socket_winsock(s_family[addrFamily], s_type[sockType], 0);
	ArchSocket socket = new ArchSocketImpl();
	socket->m_socket        = fd;
	socket->m_refCount      = 1;
	socket->m_event         = WSACreateEvent_winsock();
	socket->m_pollWrite     = true;
	return socket;
}

ArchNetAddress	NetWorkWin::newAnyAddr(EADDRESSFAMILY addrFamily)
{
	ArchNetAddress netAddr = NULL;
	netAddr = new NetAddressImpl(addrFamily);

	if(netAddr == NULL)
		return NULL;

	return netAddr;
}


void NetWorkWin::closeSocket(ArchSocket sock)
{
	if(!sock)
		return;
	close_winsock(sock->m_socket);
	delete sock;
	sock = NULL;
}

void NetWorkWin::bindSocket(ArchSocket socket, ArchNetAddress netaddr)
{
	if(!socket || !netaddr)
		return;

	if( SOCKET_ERROR ==  bind_winsock(socket->m_socket,&netaddr->m_addr,sizeof(netaddr->m_addr)) )
		ARCH->writeConsole(kERROR,"Bind Socket Fail");
}


void NetWorkWin::listenOnSocket(ArchSocket socket)
{
	if(!socket)
		return;

	if( SOCKET_ERROR ==  listen_winsock(socket->m_socket,3) )
		ARCH->writeConsole(kERROR,"Listen Socket Fail");
}

ArchSocket	NetWorkWin::acceptSocket(ArchSocket socket, ArchNetAddress netaddr)
{
	if(!socket || !netaddr)
		return NULL;

	int len = sizeof(netaddr->m_addr);

	ArchSocket clientSocket = NULL;

	SOCKET fd = accept_winsock(socket->m_socket,&netaddr->m_addr,&len);

	if( fd != INVALID_SOCKET)
	{
		clientSocket = new ArchSocketImpl();
		clientSocket->m_socket        = fd;
		clientSocket->m_refCount      = 1;
		clientSocket->m_event         = WSACreateEvent_winsock();
		clientSocket->m_pollWrite     = true;
		return clientSocket;
	}

	ARCH->writeConsole(kERROR,"Accept Socket Fail");
	return NULL;
}

bool NetWorkWin::connectSocket(ArchSocket socket, ArchNetAddress address)
{
	if(!socket || !address)
		return false;

	if(SOCKET_ERROR == connect_winsock(socket->m_socket,&address->m_addr,sizeof(address->m_addr)))
		return false;

	return true;
}

size_t	NetWorkWin::readSocket(ArchSocket socket, void* buf, size_t len)
{
	if(!socket)
		return -1;
	return recv_winsock(socket->m_socket,buf,len,0);
}

size_t	NetWorkWin::writeSocket(ArchSocket socket, const void* buf, size_t len)
{
	if(!socket)
		return -1;
	return send_winsock(socket->m_socket,buf,len,0);
}