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

#include "Utils.h"

/*##====[ HELPER FUNCTIONS ]====##*/

local Outcome Callback_ListFiles
(
	MemoryAddress Entry,
	WholeInteger Index
)
{
	File pointer Instance = Entry;
	ignore Index;

	PrintFormatted("%-5s\t%s" PATH_SEPARATOR_STRING "%s\n", 
		"FILE", 
		Instance->RelativePath.Contents, 
		Instance->Filename
	);
	return Outcome_OK;
}

local Outcome Callback_ListDirectories
(
	MemoryAddress Entry,
	WholeInteger Index
)
{
	Directory pointer Instance = Entry;
	ignore Index;

	Directory_Open(Instance);
	Directory_Close(Instance);

	PrintFormatted("%-5s\t%s\t\n", "DIR", Instance->Path.Contents);

	Dynamic_ForEach(address Instance->Directories, Callback_ListDirectories);
	Dynamic_ForEach(address Instance->Files, Callback_ListFiles);

	return Outcome_OK;
}

/*##====[ FUNCTIONS ]====##*/

Outcome _utils_directory_create
(
	Arguments Arguments
)
{
	Outcome Result = Outcome_OK;
	Looper Iterator;

	if (Arguments.Count is 0)
	{
		PrintFormatted("Enter at least one name of the directory to create.\n");
		return Outcome_FAIL;
	}

	for (Iterator = 0; Iterator < Arguments.Count; Iterator++)
	{
		PrintFormatted("Action [%d]: Creating %s\n", Iterator, Arguments.Entry[Iterator]);
		Outcome_Handle(
			Result,
			Storage_CreateDirectory(Arguments.Entry[Iterator]),
			NoAction
		)
	}

	return Outcome_OK;
}

Outcome _utils_directory_copy
(
	Arguments Arguments
)
{
	if (Arguments.Count isnt 2)
	{
		PrintFormatted("Format: [source] [destination]\n");
		return Outcome_FAIL;
	}
	else
	{
		Outcome Result = Outcome_OK;
		Directory Old = Directory_New(Arguments.Entry[0]);
		if (not Old.InitDone)
			return Outcome_FAIL;
		Directory_Load(address Old);
		Result = Directory_Copy(
			address Old,
			Arguments.Entry[1]
		);
		Directory_Free(address Old);
		return Result;
	}
}


Outcome _utils_directory_delete
(
	Arguments Arguments
)
{
	ignore Arguments;
	return Outcome_OK;
}

Outcome _utils_directory_list
(
	Arguments Arguments
)
{
	Outcome Result = Outcome_OK;
	CString Path = ".";
	Directory Current = {0};
	if (Arguments.Count > 0)
		Path = Arguments.Entry[0];
	Current = Directory_New(Path);	
	Result = Directory_Load(address Current);
	Directory_Close(address Current);
	if (Result)
		return Outcome_FAIL;

	PrintFormatted("\n##====[ DIRECTORY: %s ]====##\n\n", Path);

	Dynamic_ForEach(address Current.Directories, Callback_ListDirectories);
	Dynamic_ForEach(address Current.Files, Callback_ListFiles);

	Directory_Free(address Current);
	return Outcome_OK;
}

/*##====[ VARIABLES ]====##*/

JCubeCode_Option UtilsDirectoryOptions[] = {
	JCUBECODE_UTILS_DIRECTORY_LIST(JCUBECODE_OPTION_STRUCT)
	{NULL}
};

/*##====[ SUBMENU ]====##*/

JCUBECODE_FUNCTION_SUBMENU(_utils_directory, UtilsDirectoryOptions)
