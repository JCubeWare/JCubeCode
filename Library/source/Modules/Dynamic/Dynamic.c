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

#include "Dynamic.h"

/*##====[ FUNCTIONS ]====##*/

Dynamic Dynamic_New
(
	DynamicInitial InitialState
)
{
	Dynamic NewInstance = nullobject;

	if (InitialState)
	{
		Looper Iterator = 0;
		while (InitialState[Iterator].Data isnt nullpointer)
		{
			if (Dynamic_Add(
				address NewInstance,
				InitialState[Iterator].Data,
				InitialState[Iterator].Allocated
			))
				break;
			Iterator++;
		}
	}

	return NewInstance;
}

Boolean Dynamic_IsEmpty
(
	Dynamic pointer Instance
)
{
	return (no Instance->Count or no Instance->Entries);
}

Void Dynamic_Free
(
	Dynamic pointer Instance
)
{
	if (Dynamic_IsEmpty(Instance))
		return;

	{
		Looper Iterator;
		for (Iterator = 0; Iterator < Instance->Count; Iterator++)
			MemoryHandler_Free(address Instance->Entries[Iterator]);
	}

	Memory_Free(Instance->Entries);
	Instance->Entries = nullpointer;
	Instance->Count = 0;
	Instance->Capacity = DYNAMIC_INITIAL_CAPACITY;
}

MemoryHandler pointer Dynamic_Get
(
	Dynamic pointer Instance,
	Size Position
)
{
	if (Dynamic_IsEmpty(Instance) or Position > Instance->Count)
		return NULL;	
	return address Instance->Entries[Position];
}

Outcome Dynamic_Set
(
	Dynamic pointer Instance,
	Generic pointer Data,
	Boolean TransferOwnership,
	WholeInteger Position
)
{
	if (Dynamic_IsEmpty(Instance))
		return Outcome_ERROR_EMPTY_DYNAMIC;
	if (Position > Instance->Count)
		return Outcome_ERROR_OUT_OF_BOUNDS;

	MemoryHandler_Free(address Instance->Entries[Position]);

	Instance->Entries[Position].Data = Data;
	Instance->Entries[Position].Allocated = TransferOwnership;
	return Outcome_OK;
}

Size Dynamic_GetEntryIndex
(
	Dynamic pointer Instance,
	Generic pointer MemoryLocation
)
{
	if (Dynamic_IsEmpty(Instance) or no MemoryLocation)
		return 0;

	{
		Looper Iterator;
		for (Iterator = 0; Iterator < Instance->Count; Iterator++)
		{
			if (MemoryLocation is Instance->Entries[Iterator].Data)
				return Iterator;
		}
	}

	return 0;
}

Outcome Dynamic_AddEntry
(
	Dynamic pointer Instance,
	MemoryHandler Entry
)
{
	return Dynamic_Add(Instance, Entry.Data, Entry.Allocated);
}

Outcome Dynamic_Add
(
	Dynamic pointer Instance,
	Generic pointer Data,
	Boolean TransferOwnership
)
{
	if (no Data)
		return Outcome_OK;

	if (no Instance->Entries)
	{
		if (no Instance->Capacity)
			Instance->Capacity = DYNAMIC_INITIAL_CAPACITY;
		Instance->Entries = Memory_ClearAllocate(
			Instance->Capacity,
			sizeof(MemoryHandler));
		if (no Instance->Entries)
			return Outcome_ERROR_MEMORY_ALLOCATION;
	}
	else if (Instance->Count + 1 > Instance->Capacity)
	{
		Generic pointer Reallocation = nullpointer;
		Integer DoubledCapacity = Instance->Capacity * DYNAMIC_GROWTH;
		Reallocation = Memory_Reallocate(
			Instance->Entries,
			DoubledCapacity * sizeof(MemoryHandler)
		);
		if (not Reallocation)
			return Outcome_ERROR_MEMORY_ALLOCATION;
		Instance->Entries = Reallocation;
		Instance->Capacity = DoubledCapacity;
	}

	Instance->Entries[Instance->Count].Data = Data;
	Instance->Entries[Instance->Count].Allocated = TransferOwnership;
	Instance->Count++;
	return Outcome_OK;
}

Outcome Dynamic_ForEach
(
	Dynamic pointer Instance,
	Outcome FunctionPointer(ForEach, (MemoryAddress Entry, WholeInteger Index))
)
{
	Size Iterator;
	Outcome Result;

	for (Iterator = 0; Iterator < Instance->Count; Iterator++)
	{
		Outcome_Handle(
			Result,
			ForEach(Instance->Entries[Iterator].Data, Iterator),
			NoAction
		)
	}

	return Outcome_OK;
}
