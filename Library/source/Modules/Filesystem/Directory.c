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

#include "Directory.h"

/*##====[ CALLBACKS ]====##*/

local Outcome Directory_AddNewFile
(
	Directory pointer Instance,
	CString Path,
	CString Mode
)
{
	File pointer NewFile = Memory_New(File);
	valueat NewFile = File_New(Path, Mode);

	if (not NewFile->InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;

	if (Dynamic_Add(address Instance->Files, NewFile, true))
		return Outcome_ERROR_MEMORY_ALLOCATION;

	return Outcome_OK;
}

local Outcome Directory_AddNewDirectory
(
	Directory pointer Instance,
	CString Path
)
{
	Directory pointer NewDirectory = Memory_New(Directory);
	valueat NewDirectory = Directory_New(Path);

	if (not NewDirectory->InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;
	if (Dynamic_Add(address Instance->Directories, NewDirectory, true))
		return Outcome_ERROR_MEMORY_ALLOCATION;

	return Outcome_OK;
}

/*##====[ CALLBACKS ]====##*/

local Outcome Callback_FreeFile
(
	Generic pointer Entry,
	WholeInteger Index
)
{
	ignore Index;

	File pointer CurrentFile = (File pointer) Entry;
	File_Free(CurrentFile);
	return Outcome_OK;
}

local Outcome Callback_FreeDirectory
(
	Generic pointer Entry,
	WholeInteger Index
)
{
	ignore Index;

	Directory pointer CurrentDirectory = Entry;
	Directory_Free(CurrentDirectory);
	return Outcome_OK;
}

/*##====[ FUNCTIONS ]====##*/

Directory Directory_New
(
	CString Path
)
{
	Directory NewInstance = nullobject;
	if (no Path)
		goto new_object;

	NewInstance.Path = String_New(Path);
	NewInstance.Directories = Dynamic_New(NULL);
	NewInstance.Files = Dynamic_New(NULL);
	NewInstance.Name = CString_FindLast(NewInstance.Path.Contents, PATH_SEPARATOR) + 1;

	if (String_IsEmpty(NewInstance.Path))
		return NewInstance;

	NewInstance.InitDone = true;
new_object:
	return NewInstance;
}

Void Directory_Free
(
	Directory pointer Instance
)
{
	if (not Instance->InitDone)
		return;

	Directory_Close(Instance);
	String_Free(address Instance->Path);
	Dynamic_ForEach(address Instance->Files, Callback_FreeFile);
	Dynamic_ForEach(address Instance->Directories, Callback_FreeDirectory);
	Dynamic_Free(address Instance->Files);
	Dynamic_Free(address Instance->Directories);
}

Outcome Directory_Copy
(
	Directory pointer Instance,
	CString CopyDirectory
)
{
	Size Iterator;
	File pointer CurrentEntry;
	Directory pointer CurrentDirectory;
	String CurrentPath = String_New(NULL);

	Storage_CreateDirectory(CopyDirectory);

	if (not Instance->InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;

	for (Iterator = 0; Iterator < Instance->Files.Count; Iterator++)
	{
		CurrentEntry = Instance->Files.Entries[Iterator].Data;
		String_SetFormatted(address CurrentPath, "%s/%s", CopyDirectory, CurrentEntry->Filename);
		File_Copy(CurrentEntry, CurrentPath.Contents);
		String_Free(address CurrentPath);
	}

	for (Iterator = 0; Iterator < Instance->Directories.Count; Iterator++)
	{
		CurrentDirectory = Instance->Directories.Entries[Iterator].Data;
		String_SetFormatted(address CurrentPath, "%s/%s", CopyDirectory, CurrentDirectory->Name);
		Directory_Open(CurrentDirectory);
		Directory_Copy(CurrentDirectory, CurrentPath.Contents);
		String_Free(address CurrentPath);
	}

	return Outcome_OK;
}

/*
 * TODO: FIX THIS MESS. What the hell am I even looking at, past Matej?!?!?
 */

Outcome Directory_Load
(
	Directory pointer Instance
)
{
#if defined(OS_LINUX)
	struct stat StatBuffer;
	DirectoryEntry pointer CurrentEntry;
#elif defined(OS_WINDOWS_32) || defined(OS_WINDOWS_64)
	WIN32_FIND_DATAA StatBuffer;
	String WinSearch;
#endif
	Outcome Result = Outcome_OK;
	String FullPath = String_New(NULL);
	String IsReadOnly = String_New("r");
	CString Format;
	CString Filename;
	
	if (not Instance->InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;
	if (Instance->IsOpen)
		return Outcome_OK;

#if defined(OS_LINUX)
	Instance->Stream = opendir(Instance->Path.Contents);
	if (no Instance->Stream)
	{
		Result = Outcome_ERROR_FILESTREAM;
		goto error_setup;
	}

	while ((CurrentEntry = readdir(Instance->Stream)) != NULL)
	{
		Filename = CurrentEntry->d_name;

#elif defined(OS_WINDOWS_32) || defined(OS_WINDOWS_64)
	WinSearch = String_New(NULL);
	String_AppendCharacters(address WinSearch, Instance->Path.Contents, "\\*", NULL);
	if (String_IsEmpty(WinSearch))
	{
		Result = Outcome_ERROR_MEMORY_ALLOCATION;
		goto error_setup;
	}	

	Instance->Stream = FindFirstFile(WinSearch.Contents, &StatBuffer);
	if (Instance->Stream is INVALID_HANDLE_VALUE)
	{
		String_Free(address WinSearch);
		Result = Outcome_ERROR_FILESTREAM;
		goto error_setup;
	}
	String_Free(address WinSearch);

	do
	{
		Filename = StatBuffer.cFileName;
#endif

		if
		(
			CString_Matches(Filename, ".")
			or
			CString_Matches(Filename, "..")
		)
			continue;

		if (Instance->Path.Contents[Instance->Path.Length - 1] is PATH_SEPARATOR)
			Format = "%s%s";
		else
			Format = "%s" PATH_SEPARATOR_STRING "%s";

		if (String_SetFormatted(address FullPath, Format, Instance->Path.Contents, Filename))
		/*if (String_SetFormatted(address FullPath, Format, Filename))*/
		{
			Result = Outcome_ERROR_PRINTF;
			goto error_setup;
		}

#if defined(OS_LINUX)

		if
		(
			CString_LocateSubstring(FullPath.Contents, "/sys")
			or
			CString_LocateSubstring(FullPath.Contents, "/proc")
		)
			continue;

		if (stat(FullPath.Contents, &StatBuffer))
		{
			Result = Outcome_ERROR_FILESTREAM;
			goto error_iteration;
			continue;
		}	

		if (S_ISDIR(StatBuffer.st_mode))
#elif defined(OS_WINDOWS_32) || defined(OS_WINDOWS_64)
		if (no StatBuffer.dwFileAttributes)
			goto error_iteration;

		if (StatBuffer.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
#endif
			Directory_AddNewDirectory(Instance, FullPath.Contents);
		else
			Directory_AddNewFile(Instance, FullPath.Contents, "r");
	}
#if defined(OS_WINDOWS_32) || defined(OS_WINDOWS_64)
	while (FindNextFile(Instance->Stream, &StatBuffer));
#endif

	Instance->IsOpen = true;

#if defined(OS_LINUX)
	closedir(Instance->Stream);
#elif defined(OS_WINDOWS_32) or defined(OS_WINDOWS_64)
	FindClose(Instance->Stream);
#endif

error_iteration:
	String_Free(address FullPath);
error_setup:
	String_Free(address IsReadOnly);
	return Result;
}
