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

#include "Arguments.h"

/*##====[ FUNCTIONS ]====##*/

Arguments Arguments_New
(
	Integer Count,
	ArrayAny(CString) Entry,
	Boolean IsDynamic
)
{
	Arguments NewInstance = {
		Count,
		Entry,
		IsDynamic
	};
	return NewInstance;
}

Void Arguments_Free
(
	Arguments pointer Instance
)
{
	if (not Instance->IsDynamic)
		return;
	{
		Looper Index;
		for (Index = 0; Index < Instance->Count; Index++)
			Memory_Free(Instance->Entry[Index]);
	}

	Memory_Free(Instance->Entry);
}

Outcome Arguments_ConvertCString
(
	Arguments pointer Instance,
	CString Source,
	CString Delimiter
)
{
	Size SourceIndex = 0;
	Size SourceSize = 0;
	Size DelimiterSize = 0;
	Size NewEntrySize = 0;
	Size TokenStart = 0;
	Generic pointer Reallocate = nullpointer;

	if (no Source or no Delimiter)
		return Outcome_ERROR_EMPTY_STRING;

	SourceSize = CString_Length(Source);
	DelimiterSize = CString_Length(Delimiter);

	Arguments_Free(Instance);
	Instance->IsDynamic = true;

	for (SourceIndex = 0; SourceIndex <= SourceSize; SourceIndex++)
	{		
		if
		(
			no CString_CompareCount(
				Source + SourceIndex,
				Delimiter,
				DelimiterSize
			)
			or SourceIndex is SourceSize
		)
		{
			Reallocate = Memory_Reallocate(Instance->Entry, 
				(Instance->Count + 1) * sizeof(CString)
			);
			if (no Reallocate)
				goto array_realloc_fail;

			Instance->Entry = Reallocate;
			NewEntrySize = SourceIndex - TokenStart;
			
			Instance->Entry[Instance->Count] = Memory_ClearAllocate(
				(NewEntrySize + 1),
				sizeof(Character)
			);
			if (not Instance->Entry[Instance->Count])
				goto array_entry_fail;

			CString_CopyCount(
				Instance->Entry[Instance->Count],
				address Source[TokenStart],
				NewEntrySize
			);

			SourceIndex += (DelimiterSize - 1);
			TokenStart = (SourceIndex + 1);

			Instance->Count++;
		}
	}

	return Outcome_OK;

array_entry_fail:
array_realloc_fail:
	Arguments_Free(Instance);
	return Outcome_ERROR_MEMORY_ALLOCATION;
}

CString Arguments_GetCString
(
	Arguments pointer Instance,
	CString Separator
)
{
	Looper Iterator;
	Size SeparatorSize = 0;
	Size TotalSize = 0;
	Size CurrentSize = 0;
	CString NewInstance = nullpointer;
	CString CurrentPosition = nullpointer;

	if (Separator)
		SeparatorSize = CString_Length(Separator);

	for (Iterator = 0; Iterator < Instance->Count; Iterator++)
	{
		TotalSize += CString_Length(Instance->Entry[Iterator]);
		TotalSize += SeparatorSize;
	}

	NewInstance = Memory_ClearAllocate(TotalSize + 1, sizeof(Character));
	if (no NewInstance)
		return nullpointer;

	CurrentPosition = NewInstance;
	for (Iterator = 0; Iterator < Instance->Count; Iterator++)
	{
		CurrentSize = CString_Length(Instance->Entry[Iterator]);
		CString_Copy(CurrentPosition, Instance->Entry[Iterator]);
		CurrentPosition += CurrentSize;
		CString_Copy(CurrentPosition, Separator);
		CurrentPosition += SeparatorSize;
	}

	return NewInstance;
}
