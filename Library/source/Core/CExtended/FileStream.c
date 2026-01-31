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

#include "Storage.h"
#include "../C89/C89.h"

/*##====[ FEATURES ]====##*/

Void FileStream_WriteCStringEscaped
(
	FileStream pointer Instance,
	readonly CString Passed
)
{
	CString Iterator = Passed;

	while (valueat Iterator isnt '\0')
	{
		switch (valueat Iterator)
		{
			case '\\':
			case '\n':
			case '\t':
			case '\r':
			case '\b':
			case '\f':
			case '\v':
			case '\a':
			case '\"':
				FileStream_WriteCharacter('\\', Instance);
		}
		FileStream_WriteCharacter(valueat Iterator, Instance);
		Iterator++;
	}
}

Size FileStream_GetSize
(
	FileStream pointer Instance
)
{
	Size FileSize = 0;
	
	if (Instance isnt nullpointer)
	{
		Size Cursor = FileStream_GetPosition(Instance);

		FileStream_SetPosition(Instance, 0L, SEEK_END);
		FileSize = FileStream_GetPosition(Instance);
		FileStream_SetPosition(Instance, Cursor, SEEK_SET);
	}

	return FileSize;
}

CString FileStream_ReadFull
(
	FileStream pointer Instance
)
{
	CString Allocation = nullpointer;

	if (Instance isnt nullpointer)
	{
		Size ReadResult;
		Size TotalSize = FileStream_GetSize(Instance);
		
		Allocation = Memory_ClearAllocate(TotalSize, sizeof(Character));
		if (no Allocation)
			return nullpointer;

		ReadResult = FileStream_Read(
			Allocation,
			sizeof(Character),
			TotalSize,
			Instance
		);
		if (ReadResult isnt TotalSize)
		{
			Memory_Free(Allocation);
			return nullpointer;
		}
	}

	return Allocation;
}
