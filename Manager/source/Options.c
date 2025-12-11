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

#include "Options.h"

/*##====[ VARIABLES ]====##*/

JCubeCode_Option Options[] = {
	JCUBECODE_OPTION_LIST(JCUBECODE_OPTION_STRUCT)
	{NULL}
};

JCubeCode_Option ProjectOptions[] = {
	JCUBECODE_PROJECT_LIST(JCUBECODE_OPTION_STRUCT)
	{NULL}
};

JCubeCode_Option UtilsOptions[] = {
	JCUBECODE_UTILS_LIST(JCUBECODE_OPTION_STRUCT)
	{NULL}
};

JCubeCode_Option ScriptsOptions[] = {
	JCUBECODE_SCRIPTS_LIST(JCUBECODE_OPTION_STRUCT)
	{NULL}
};

JCubeCode_Option SettingsOptions[] = {
	JCUBECODE_SETTINGS_LIST(JCUBECODE_OPTION_STRUCT)
	{NULL}
};

/*##====[ HELP MENU ]====##*/

Outcome CallOption
(
	CString Path,
	Arguments Arguments,
	JCubeCode_Option pointer OptionList
)
{
	Looper Iterator = 0;

	while (OptionList[Iterator].Name isnt NULL)
	{
		if (CString_Matches(Path, OptionList[Iterator].Name))
			return OptionList[Iterator].DoFunction(Arguments);
		Iterator++;
	}

	return Outcome_UNKNOWN_OPTION;
}

Void HelpMenu
(
	JCubeCode_Option pointer Listed
)
{
	Looper Iterator = 0;
	
	PrintFormatted(
		JCUBECODE_HELPMENU,
		JCubeCode.Version.Major,
		JCubeCode.Version.Minor,
		JCubeCode.Version.Patch,
		JCubeCode.Build.Date,
		JCubeCode.Build.Time
	);
	while (Listed[Iterator].Name isnt NULL)
	{
		PrintFormatted(
			"%-12s | %s\n",
			Listed[Iterator].Name,
			Listed[Iterator].Description
		);
		Iterator++;
	}
}

/*##====[ JCC MAIN OPTIONS ]====##*/

JCUBECODE_FUNCTION_SUBMENU(__project, ProjectOptions)
JCUBECODE_FUNCTION_SUBMENU(__utils, UtilsOptions)
JCUBECODE_FUNCTION_SUBMENU(__script, ScriptsOptions)
JCUBECODE_FUNCTION_SUBMENU(__settings, SettingsOptions)

Outcome _utils_net(Arguments Arguments) {
  (Void) Arguments;
  return Outcome_OK;
}

JCUBECODE_SCRIPTS_LIST(JCUBECODE_OPTION_DUMMY)
JCUBECODE_SETTINGS_LIST(JCUBECODE_OPTION_DUMMY)