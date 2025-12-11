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
#         (c) 2025-2025, JCubeWare         #
############################################
*/

/*##====[ INCLUDES ]====##*/

#include "MemoryHandler.h"

/*##====[ FUNCTIONS ]====##*/

MemoryHandler MemoryHandler_New
(
	MemoryAddress Data,
	Boolean Allocated
)
{
	MemoryHandler NewInstance = nullobject;

	if (Data)
	{
		NewInstance.Data = Data;
		NewInstance.Allocated = Allocated;
	}

	return NewInstance;
}

Void MemoryHandler_Free
(
	MemoryHandler pointer Instance
)
{
	if (Instance->Allocated)
		Memory_Free(Instance->Data);
	Memory_Set(Instance, 0, sizeof(MemoryHandler));
}

Void MemoryHandler_Set
(
	MemoryHandler pointer Instance,
	MemoryAddress Data,
	Boolean Allocated
)
{
	MemoryHandler_Free(Instance);

	if (Instance->Data)
	{
		Instance->Allocated = Allocated;
		Instance->Data = Data;
	}
}
