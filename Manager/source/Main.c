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

#include "Common.h"
#include "Options.h"

/*##====[ VARIABLES ]====##*/

CString CurrentDirectory = NULL;
Logger Print = {
	"[J][C]ube[C]ode",
	LogLevel_DEBUG,
	false,
	"t",
	true,
	true,
	true,
	true,
	nullpointer,
};

/*##====[ MAIN FUNCTION ]====##*/

Integer main
(
	Integer ArgumentCount,
	CString pointer ArgumentVector
)
{
	Outcome Status = 1;
	Arguments FunctionData = {0};
	String GlobalSettings = String_New(NULL);

	Print.Stream = stdout;
	CurrentDirectory = Storage_GetFullPath(".", NULL);

	Logger_Print(Print, LogLevel_WARN, "Running in '%s'", CurrentDirectory);

	String_SetFormatted(
		address GlobalSettings,
		"%s/%s",
		Enviroment_GetCString("HOME"),
		JCUBECODE_GLOBAL_PATH
	);

	if (not Storage_CreateDirectory(GlobalSettings.Contents))
		Logger_Print(Print, LogLevel_NORMAL, "Setting up JCubeCode on this account for the first time. Please wait.");

	if (ArgumentCount is 1)
	{
		HelpMenu(Options);
		Status = 1;
		goto exit_app;
	}

	FunctionData = Arguments_New(ArgumentCount - 2, ArgumentVector + 2, false);
	Status = CallOption(ArgumentVector[1], FunctionData, Options);

exit_app:
	Memory_Free(CurrentDirectory);
	return Status;
}
