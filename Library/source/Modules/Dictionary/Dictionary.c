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

#include "Dictionary.h"

/*##====[ HELPER FUNCTIONS ]====##*/

local Outcome Dictionary_FreeEach
(
	Generic pointer Entry,
	WholeInteger Index
)
{
	DictionaryEntry pointer CurrentEntry = Entry;
	ignore Index;

	MemoryHandler_Free(address CurrentEntry->Value);
	return Outcome_OK;
}

/*##====[ FUNCTIONS ]====##*/

Dictionary Dictionary_New
(
	DictionaryInitial InitialState
)
{
	Dictionary NewInstance = nullobject;

	if (InitialState)
	{
		Looper Iterator = 0;
		while (InitialState[Iterator].Key isnt nullpointer)
		{
			if (Dictionary_Set(
				address NewInstance,
				InitialState[Iterator].Key,
				InitialState[Iterator].Value.Data,
				true
			))
				break;
			Iterator++;
		}
	}

	return NewInstance;
}

Void Dictionary_Free
(
	Dictionary pointer Instance
)
{
	Dictionary_ForEach(Instance, Dictionary_FreeEach);
	Dynamic_Free(address Instance->Contents);
}

Boolean Dictionary_IsEmpty
(
	Dictionary pointer Instance
)
{
	return Dynamic_IsEmpty(address Instance->Contents);
}

Size Dictionary_Count
(
	Dictionary pointer Instance
)
{
	return Instance->Contents.Count;
}

Outcome Dictionary_Set
(
	Dictionary pointer Instance,
	CString Key,
	Generic pointer Value,
	Boolean TransferOwnership
)
{
	DictionaryEntry pointer NewEntry = Memory_New(DictionaryEntry);
	DictionaryEntry pointer EntryExists = nullpointer;
	Size EntryLocation;

	if (no NewEntry)
		return Outcome_ERROR_MEMORY_ALLOCATION;

	if (Value and Key)
	{
		NewEntry->Hash = Hash_DJB2(Key);
		NewEntry->Key = Key;
		NewEntry->Value.Data = Value;
		NewEntry->Value.Allocated = TransferOwnership;
		
		EntryExists = Dictionary_GetEntry(Instance, Key);
		if (no EntryExists)
			return Dynamic_Add(
				address Instance->Contents,
				NewEntry,
				true
			);
		else
		{
			EntryLocation = Dynamic_GetEntryIndex(address Instance->Contents, EntryExists);
			return Dynamic_Set(
				address Instance->Contents,
				NewEntry,
				true,
				EntryLocation
			);
		}
	}

	return Outcome_OK;
}

DictionaryEntry pointer Dictionary_GetEntry
(
	Dictionary pointer Instance,
	CString Key
)
{
	Size Iterator;
	Size Hash;
	DictionaryEntry pointer CurrentEntry = nullpointer;

	if (no Instance or no Key)
		return nullpointer;

	Hash = Hash_DJB2(Key);

	for (Iterator = 0; Iterator < Instance->Contents.Count; Iterator++)
	{
		CurrentEntry = Instance->Contents.Entries[Iterator].Data;

		if (CurrentEntry->Hash isnt Hash)
			continue;
		if (not CString_Matches(CurrentEntry->Key, Key))
			continue;

		return CurrentEntry;
	}

	return nullpointer;
}

Generic pointer Dictionary_Get
(
	Dictionary pointer Instance,
	CString Key
)
{
	DictionaryEntry pointer CurrentEntry = Dictionary_GetEntry(Instance, Key);

	if (no CurrentEntry)
		return nullpointer;
	return CurrentEntry->Value.Data;
}

Outcome Dictionary_ForEach
(
	Dictionary pointer Instance,
	Outcome FunctionPointer(ForEach, (MemoryAddress Entry, WholeInteger Index))
)
{
	return Dynamic_ForEach(address Instance->Contents, ForEach);
}
