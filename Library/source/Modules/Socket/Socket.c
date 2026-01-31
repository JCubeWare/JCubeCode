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

/*##====[ INCLUDES ]====##*/

#include "Socket.h"

/*##====[ FUNCTIONS ]====##*/

Boolean Socket_IsValid
(
	Pointer(Socket) Instance
)
{
#if defined(OS_LINUX)
	return logic(Instance->Handler isnt -1);
#elif defined(OS_WINDOWS_)
	return logic(Instance->Handler isnt INVALID_SOCKET);
#else
#error "Socket_IsValid() has no implementation for this platform."
#endif
}

Outcome Socket_Enable
(
	noarguments
)
{
#if defined(OS_LINUX)
	return Outcome_OK;
#elif defined(OS_WINDOWS_)
	WSADATA wsa;
	return WSAStartup(MAKEWORD(2,2), &wsa);
#else
#error "Socket_Enable() has no implementation for this platform."
#endif
}

Void Socket_Disable
(
	noarguments
)
{
#if defined(OS_LINUX)
#elif defined(OS_WINDOWS_)
	WSACleanup();
#else
#error "Socket_Disable() has no implementation for this platform."
#endif
}

Socket Socket_New
(
	Integer Domain,
	Integer Type,
	Integer Protocol
)
{
	Socket NewInstance = {
		socket(Domain, Type, Protocol),
		Domain,
		Type,
		Protocol,
		nullobject,
		0
	};
	return NewInstance;
}

Outcome Socket_StartClient
(
	Pointer(Socket) Instance,
	WholeInteger Port,
	CString NetAddress
)
{
	Integer Result;

	Instance->NetAddress.sin_family = Instance->Domain;
	Instance->NetAddress.sin_port = htons(Port);
#if defined(OS_LINUX)
	if (inet_pton(Instance->Domain, NetAddress, address Instance->NetAddress.sin_addr) <= 0)
	{
		Socket_Free(Instance);
		return Outcome_ERROR_SOCKET;
	}
#elif defined(OS_WINDOWS_)
	Instance->NetAddress.sin_addr.s_addr = inet_addr(NetAddress);
#endif

	Result = connect(
		Instance->Handler, 
		(Pointer(struct sockaddr)) address Instance->NetAddress,
		sizeof(Instance->NetAddress)
	);

#if defined(OS_LINUX)
	if (Result < 0)
#elif defined(OS_WINDOWS_)
	if (Result is SOCKET_ERROR)
#endif
	{
		Socket_Free(Instance);
		return Outcome_ERROR_SOCKET;
	}
		
	return Outcome_OK;
}

Outcome Socket_StartServer
(
	Pointer(Socket) Instance,
	WholeInteger Port,
	CString NetAddress,
	WholeInteger MaxConnections
)
{
	ignore Instance;
	ignore Port;
	ignore NetAddress;
	ignore MaxConnections;

	return Outcome_OK;
}

Void Socket_Free
(
	Pointer(Socket) Instance
)
{
#if defined(OS_LINUX)
	close(Instance->Handler);
	Instance->Handler = 0;
#elif defined(OS_WINDOWS_)
	closesocket(Instance->Handler);
	Instance->Handler = 0;
#else
#error "Socket_Free() has no implementation for this platform."
#endif
}

/* TODO: FINISH

Size Socket_Read();
Size Socket_Write();
Outcome Socket_ReadFull();
Outcome Socket_WriteFull();
Outcome Socket_ReadFile();
Outcome Socket_WriteFile();
Integer Socket_Shutdown();
Integer Socket_SetOption();

Generic Socket_GetAddressInfo();
Generic Socket_GetHostname();
Generic Socket_GetHostByName();

Integer Socket_SetFlag();

*/

