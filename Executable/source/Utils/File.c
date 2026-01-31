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

#include "Utils.h"

/*##====[ HELPER FUNCTIONS ]====##*/

JCUBECODE_OPTION_DUMMY(_utils_file, info, "TODO: Finish")
JCUBECODE_OPTION_DUMMY(_utils_file, create, "TODO: Finish")

Outcome _utils_file_dump
(
	Arguments Arguments
)
{
	Size Index = 0;
	Size ReadBytes;
	Outcome Result = Outcome_OK;
	String Buffer = String_New(NULL);
	File FileTest = File_New(Arguments.Entry[0], "rb");
	if (not FileTest.InitDone)
		return Outcome_ERROR_NOT_INITIALIZED;

	PrintFormatted(
		"File: %s; Location: %s\n",
		FileTest.Filename, 
		FileTest.RelativePath.Contents
	);

	while (true)
	{
		Result = File_Read(
			address FileTest,
			address Buffer,
			address ReadBytes,
			Index,
			10
		);
		if (no ReadBytes)
		{
			String_Free(address Buffer);
			break;
		}

		PrintFormatted("%s", Buffer.Contents);
		Index += ReadBytes;
	}

	PrintFormatted("\n\n##====[ EOF (%s) ]====##\n", FileTest.Filename);
	File_Free(address FileTest);
	return Result;
}

Outcome _utils_file_copy
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
		File Old = File_New(Arguments.Entry[0], "rb");
		if (not Old.InitDone)
			return Outcome_FAIL;
		Result = File_Copy(
			address Old,
			Arguments.Entry[1]
		);
		File_Free(address Old);
		return Result;
	}
}

Outcome _utils_file_delete
(
	Arguments Arguments
)
{
	Outcome Result = Outcome_OK;
	Looper Iterator;

	if (Arguments.Count is 0)
	{
		PrintFormatted("Provide at least one file to delete.\n");
		return Outcome_FAIL;
	}

	for (Iterator = 0; Iterator < Arguments.Count; Iterator++)
	{
		PrintFormatted("Action [%d]: Deleting %s\n", Iterator, Arguments.Entry[Iterator]);
		Outcome_Handle(
			Result,
			Storage_FileRemove(Arguments.Entry[Iterator]),
			NoAction
		)
	}

	return Outcome_OK;
}

Outcome _utils_file_rename
(
	Arguments Arguments
)
{
	if (Arguments.Count isnt 2)
	{
		PrintFormatted("Format: [old] [new]\n");
		return Outcome_FAIL;
	}

	return Storage_FileRename(Arguments.Entry[0], Arguments.Entry[1]);
}

/*##====[ VARIABLES ]====##*/

JCubeCode_Option UtilsFileOptions[] = {
	JCUBECODE_UTILS_FILE_LIST(JCUBECODE_OPTION_STRUCT)
	{NULL}
};

/*##====[ SUBMENU ]====##*/

JCUBECODE_FUNCTION_SUBMENU(_utils_file, UtilsFileOptions)
