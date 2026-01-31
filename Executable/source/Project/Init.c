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

#include "Project.h"

/*##====[ FUNCTIONS ]====##*/

Outcome _project_init
(
	Arguments Arguments
)
{
	String Test = String_New(nullpointer);
	Directory Default = Directory_New(nullpointer);
	FileStream pointer Settings = nullpointer;

	ignore Arguments;

	Settings = FileStream_Open("./Project.jcdata", "r");
	if (Settings)
	{
		Logger_Print(Print, LogLevel_ERROR, "Project is already initialized.");
		FileStream_Close(Settings);
		return Outcome_OK;
	}

	if (no DoUserConfirm("Are you sure you want to initialize here?"))
		return Outcome_OK;

	String_SetFormatted(
		address Test,
		"%s/%s/%s",
		Enviroment_GetCString("HOME"),
		JCUBECODE_GLOBAL_PATH,
		"/Example"
	);
	Default = Directory_New(Test.Contents);
	if (not Default.InitDone)
		return Outcome_FAIL;
	Directory_Load(address Default);
	Directory_Copy(address Default, ".");
	Logger_Print(Print, LogLevel_NORMAL, "Setting up a project template in '%s'", CurrentDirectory);
	Directory_Free(address Default);
	return Outcome_OK;
}