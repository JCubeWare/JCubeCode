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

#include "File.h"

/*##====[ HELPER FUNCTIONS ]====##*/

local Size File_UpdateSize
(
	File pointer Instance
)
{
	Size Result = 0;

	if (no Instance->Stream)
		return Result;
	
	FileStream_SetPosition(Instance->Stream, 0, SEEK_END);
	Result = FileStream_GetPosition(Instance->Stream);
	FileStream_SetPosition(Instance->Stream, 0, SEEK_SET);
	return Result;
}

/*##====[ FUNCTIONS ]====##*/

File File_New
(
	CString Filename,
	CString RestrictModes
)
{
	File NewInstance = nullobject;
	if (no Filename or no RestrictModes)
		goto new_object;
	
	NewInstance.Stream = FileStream_Open(Filename, RestrictModes);
	if (no NewInstance.Stream)
		goto new_object;

	if (Filename[0] isnt '.' and Filename[1] isnt PATH_SEPARATOR)
		String_SetFormatted(address NewInstance.RelativePath, "./%s", Filename);
	else
		NewInstance.RelativePath = String_New(Filename);
	
	if (String_IsEmpty(NewInstance.RelativePath))
		goto new_object;

	NewInstance.Filename = Storage_GetFilename(NewInstance.RelativePath.Contents);
	NewInstance.Size = File_UpdateSize(address NewInstance);

	if (NewInstance.Filename isnt NewInstance.RelativePath.Contents)
		valueat (NewInstance.Filename - 1)  = '\0';

	NewInstance.RestrictModes = String_New(RestrictModes);
	if (String_IsEmpty(NewInstance.RestrictModes))
	{
		String_Free(address NewInstance.RelativePath);
		goto new_object;
	}
		
	NewInstance.InitDone = true;
new_object:
	return NewInstance;
}

Outcome File_Open
(
	File pointer Instance
)
{
	ignore Instance;
	return Outcome_OK;
}

Void File_Close
(
	File pointer Instance
)
{
	ignore Instance;
}

Void File_Free
(
	File pointer Instance
)
{
	if (not Instance->InitDone)
		return;

	FileStream_Close(Instance->Stream);
	String_Free(address Instance->RelativePath);
	String_Free(address Instance->RestrictModes);
	Instance->Filename = nullpointer;
	Instance->Size = 0;
	Instance->Stream = NULL;
	Instance->InitDone = false;
}

CString File_LoadContents
(
	FileStream pointer Current,
	Size pointer SizeResult
)
{
	Size TotalSize = 0;
	Size ReadResult;
	CString Allocation = NULL;

	FileStream_SetPosition(Current, 0L, SEEK_END);
	TotalSize = FileStream_GetPosition(Current);
	FileStream_RewindFile(Current);

	Allocation = Memory_ClearAllocate(TotalSize, sizeof(Byte));
	if (no Allocation)
		return NULL;

	ReadResult = FileStream_Read(
		Allocation,
		sizeof(Character),
		TotalSize,
		Current
	);
	if (ReadResult isnt TotalSize)
		return NULL;

	valueat SizeResult = ReadResult;
	return Allocation;
}

Outcome File_Copy
(
	File pointer Instance,
	CString NewLocation
)
{
	Outcome Result = Outcome_OK;
	FileStream pointer CopyFile = NULL;	
	Character Buffer[4096] = nullobject;
	Size CopySize;

	if (no Instance->InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;

	CopyFile = FileStream_Open(NewLocation, "wb");
	if (no CopyFile)
		return Outcome_ERROR_FILESTREAM;

	while ((CopySize = FileStream_Read(Buffer, sizeof(Character), sizeof(Buffer), Instance->Stream)) > 0)
	{
		if (FileStream_Write(Buffer, sizeof(Character), CopySize, CopyFile) != CopySize)
		{
			Result = Outcome_ERROR_FILESTREAM;
			break;
		}
	}

	FileStream_Close(CopyFile);
	return Result;
}

Outcome File_Write
(
	File pointer Instance,
	String Buffer,
	Size MaxAmount
)
{
	Size Result;

	if (not Instance->InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;

	Result = FileStream_Write(
		Buffer.Contents,
		sizeof(Character),
		MaxAmount,
		Instance->Stream
	);
	if (Result < MaxAmount)
		return Outcome_ERROR_WRITE;

	Instance->Size = File_UpdateSize(Instance);
	return Outcome_OK;
}

Outcome File_Read
(
	File pointer Instance,
	String pointer Buffer,
	Size pointer ReadAmount,
	Size StartFrom,
	Size Amount
)
{
	Size Result;
	Size FilePosition;

	if (not Instance->InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;

	FileStream_SetPosition(Instance->Stream, StartFrom, SEEK_SET);

	FilePosition = Instance->Size - StartFrom;

	if (Amount > FilePosition)
		Amount = FilePosition;

	if (String_Initialize(Buffer, Amount))
		return Outcome_ERROR_MEMORY_ALLOCATION;

	Result = FileStream_Read(
		Buffer->Contents,
		sizeof(Character),
		Amount,
		Instance->Stream
	);
	valueat ReadAmount = Result;
	return Outcome_OK;
}

Outcome File_Remove
(
	File pointer Instance
)
{
	if (not Instance->InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;
	if (Storage_FileRemove(Instance->Filename))
		return Outcome_ERROR_FILESTREAM;
	File_Free(Instance);
	return Outcome_OK;
}
