/*
           #################################
          ###                          #####
        ###     ######################### ##
      ###     ###                   ##### ##
    ####     ########################  ## ##
  ####                          ###    ## ##
####                          ####     ## ##
################################ #     ## ##
##                     #     ##  #  ## ## ##
##                     #     ##  #  ## ## ##
##                     #     ##  #  ##### ##
##                     #     ##  # ###### ##
##                     #     ##  # #  ### ##
##                     #     ##  ###  ### ##
##                     #     ##  ##    ## ##
##########             #     ##  ##    #  ##
##       #             #     ##  ##      ###
##       #             #     ##  #      ### 
##       #             #     ##       ###   
##       ###############     ##     ####    
##                           ##   ####      
##                           ## ####        
##                           #####          
################################            

############# [J][C]ube[W]are ##############
#   Be responsible. Code for the future.   #
#         (c) 2025-2026, JCubeWare         #
############################################
*/

#pragma once

#ifndef JCUBECODE_MODULES_SOCKET_H
#define JCUBECODE_MODULES_SOCKET_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Handles socket communication in between processes or via the internet.
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../Strings/Strings.h"

/*##====[ DATA TYPES ]====##*/

#if defined(OS_LINUX)
	typedef socklen_t SocketSize;
	typedef ssize_t SocketBytes;
#elif defined(OS_WINDOWS_)
	typedef Integer SocketSize;
	typedef Integer SocketBytes;
#else
#error "Data type 'SocketSize' has no implementation for this platform."
#endif

typestruct(Socket,
	SocketHandler Handler;
	Integer Domain;
	Integer Type;
	Integer Protocol;
	struct sockaddr_in NetAddress;
	SocketSize AddressLength;
);

/*##====[ JCUBELAYER ]====##*/

/*##====[ FUNCTIONS ]====##*/

Boolean Socket_IsValid
(
	Pointer(Socket) Instance
);

Outcome Socket_Enable
(
	noarguments
);

Void Socket_Disable
(
	noarguments
);

Socket Socket_New
(
	Integer Domain,
	Integer Type,
	Integer Protocol
);

Outcome Socket_StartClient
(
	Pointer(Socket) Instance,
	WholeInteger Port,
	CString NetAddress
);

Outcome Socket_StartServer
(
	Pointer(Socket) Instance,
	WholeInteger Port,
	CString NetAddress,
	WholeInteger MaxConnections
);

/*
 * Initialize all socket operations.
 */
Outcome Socket_Enable();

/*
 * Stop all socket operations
 */
Void Socket_Disable();

/*
 * Creates a new Socket object.
 * This instance now holds a "Handler" that references the socket in the OS.
 */
Socket Socket_New
(
	Integer Domain,
	Integer Type,
	Integer Protocol
);

Void Socket_Free
(
	Pointer(Socket) Instance
);

/* TODO:
##============================================================================##
## LINUX            # WINDOWS                # VERDICT                        ##
##============================================================================##
socket()            | socket()               | Create a socket
socketpair()        |  -                     | No direct equivalent
bind()              | bind()                 | Assign local address
listen()            | listen()               | Mark socket as passive
accept()            | accept()               | Accept incoming connection
accept4()           |  -                     | Use accept() + ioctlsocket()
connect()           | connect()              | Initiate connection
shutdown()          | shutdown()             | Partial or full close
close()             | closesocket()          | Different close function
read()              |  -                     | recv() on Windows
write()             |  -                     | send() on Windows
readv()             | WSARecv()              | Scatter read
writev()            | WSASend()              | Gather write
send()              | send()                 | Send data
sendto()            | sendto()               | Send datagram
sendmsg()           | WSASendMsg()           | Message-based send
sendmmsg()          |  -                     | No batch send
recv()              | recv()                 | Receive data
recvfrom()          | recvfrom()             | Receive datagram
recvmsg()           | WSARecvMsg()           | Message-based receive
recvmmsg()          |  -                     | No batch receive
setsockopt()        | setsockopt()           | Set socket options
getsockopt()        | getsockopt()           | Get socket options
fcntl()             |  -                     | Use ioctlsocket()
ioctl()             | ioctlsocket()          | Socket control
getsockname()       | getsockname()          | Get local address
getpeername()       | getpeername()          | Get peer address
getaddrinfo()       | getaddrinfo()          | Address resolution
freeaddrinfo()      | freeaddrinfo()         | Free addrinfo
getnameinfo()       | getnameinfo()          | Reverse lookup
gethostbyname()     | gethostbyname()        | Deprecated
getservbyname()     | getservbyname()        | Legacy service lookup
select()            | select()               | I/O multiplexing
pselect()           |  -                     | No Windows equivalent
poll()              | WSAPoll()              | Poll-based multiplexing
epoll_create()      |  -                     | Will study IOCP on Windows (dammit)
epoll_ctl()         |  -                     | Will study IOCP on Windows (dammit)
epoll_wait()        |  -                     | Will study IOCP on Windows (dammit)
sendfile()          |  -                     | Zero-copy send
splice()            |  -                     | Linux-only
vmsplice()          |  -                     | Linux-only
*/

/*

JCubeLayer Integer Socket_SetNonBlocking
(
	SocketHandler Socket
)
{
	Integer Flags;

	Flags = fcntl(Socket, F_GETFL, 0);
	if (Flags is -1)
		return Outcome_ERROR_SOCKET;

	Flags |= O_NONBLOCK;
	return fcntl(Socket, F_SETFL, Flags);
}

JCubeLayer Integer Socket_SetOption
(
	SocketHandler Socket,
	Integer Level,
	Integer Name,
	Generic pointer Value,
	SocketSize Value_Size 
)
{
	Socket_IsValid(Socket);
	return setsockopt(Socket, Level, Name, Value, Value_Size);
}

JCubeLayer Unsigned16 Convert_ShortToNetShort
(
	Unsigned16 HostShort
)
{
	return htons(HostShort);
}

JCubeLayer Integer Socket_Bind
(
	SocketHandler Socket,
	MemoryAddress IPAddress,
	SocketSize IPAddress_Size
)
{
	Socket_IsValid(Socket);
	return bind(Socket, IPAddress, IPAddress_Size);
}

JCubeLayer Integer Socket_Listen
(
	SocketHandler Socket,
	Integer MaxConnections
)
{
	Socket_IsValid(Socket);
	return listen(Socket, MaxConnections);
}

JCubeLayer Integer Socket_Close
(
	SocketHandler Socket
)
{
	Socket_IsValid(Socket);
	return close(Socket);
}

JCubeLayer Integer Socket_Shutdown
(
	SocketHandler Socket,
	Integer Type
)
{
	Socket_IsValid(Socket);
	return shutdown(Socket, Type);
}

JCubeLayer Integer Socket_Accept
(
	SocketHandler Socket,
	MemoryAddress NewAddress,
	SocketSize pointer NewAddress_Size
)
{
	Socket_IsValid(Socket);
	return accept(Socket, NewAddress, NewAddress_Size);
}

JCubeLayer ssize_t Socket_Recieve
(
	SocketHandler Socket,
	MemoryAddress Buffer,
	Size MaxSize,
	Integer Flags
)
{
	Socket_IsValid(Socket);
	return recv(Socket, Buffer, MaxSize, Flags);
}

JCubeLayer ssize_t Socket_Send
(
	SocketHandler Socket,
	MemoryAddress Buffer,
	Size MaxSize,
	Integer Flags
)
{
	Socket_IsValid(Socket);
	return send(Socket, Buffer, MaxSize, Flags);
}
*/

#endif
