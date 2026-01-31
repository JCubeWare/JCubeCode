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

#include "Chain.h"

/*##====[ FUNCTIONS ]====##*/

ChainNode pointer ChainNode_New
(
	MemoryAddress Data
)
{
	ChainNode pointer NewInstance = Memory_New(ChainNode);
	if (no NewInstance)
		goto new_instance;

	NewInstance->Data = Data;

new_instance:
	return NewInstance;
}

Chain Chain_New
(
	MemoryAddress Data
)
{
	Chain NewInstance = nullobject;

	if (Data)
		NewInstance.Start = ChainNode_New(Data);

	return NewInstance;
}

Void Chain_Free
(
	Chain pointer Instance
)
{
	ChainNode pointer Iterator = Instance->Start;
	ChainNode pointer Next = nullpointer;

	while (Iterator)
	{
		Next = Iterator->Next;
		Memory_Free(Iterator->Data);
		Memory_Free(Iterator);
		Iterator = Next;
	}
}

Size Chain_Count
(
	Chain pointer Instance
)
{
	Size Count = 0;
	ChainNode pointer Iterator = Instance->Start;

	while (Iterator)
	{
		Iterator = Iterator->Next;
		Count++;
	}

	return Count;
}

Boolean Chain_IsEmpty
(
	Chain pointer Instance
)
{
	return logic(Instance->Start is nullpointer);
}

Outcome Chain_Append
(
	Chain pointer Instance,
	MemoryAddress Data
)
{
	ChainNode pointer Iterator = Instance->Start;
	ChainNode pointer NewEntry = nullpointer;

	if (no Iterator)
	{
		Instance->Start = ChainNode_New(Data);
		return Outcome_OK;
	}

	while (Iterator->Next) 
		Iterator = Iterator->Next;

	NewEntry = ChainNode_New(Data);
	if (no NewEntry)
		return Outcome_ERROR_MEMORY_ALLOCATION;
	
	NewEntry->Previous = Iterator;
	NewEntry->Next = nullpointer;
	Iterator->Next = NewEntry;
	return Outcome_OK;
}

Outcome Chain_ForEach
(
	Chain pointer Instance,
	Outcome FunctionPointer(ForEach, (MemoryAddress Entry, WholeInteger Index))
)
{
	Size Index = 0;
	ChainNode pointer Iterator = Instance->Start;
	ChainNode pointer Next = nullpointer;
	Outcome Result = Outcome_OK;

	while (Iterator)
	{
		Next = Iterator->Next;
		Outcome_Handle(Result, ForEach(Iterator->Data, Index), NoAction)
		Iterator = Next;
		Index++;
	}

	return Outcome_OK;
}
