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

#pragma once

#ifndef JCUBECODE_CLI_OPTIONS_H
#define JCUBECODE_CLI_OPTIONS_H

/*##====[ JCUBECODE ]====##*/

#include "Common.h"

/*##====[ HELP MENU ]====##*/

#define JCUBECODE_HELPMENU \
	"\n##====[ [J][C]ube[C]ode ]====##\n" \
	"Version: %d.%d.%d (Built %s %s)\n\n" \
	"Coding layer/library used by JCubeWare based on C90.\n" \
	"Short name for libraries/packages is 'Cube'.\n\n" \
	"##====[ OPTIONS ]====##\n"

/*##====[ MACRO ACTIONS ]====##*/

#define JCUBECODE_FUNCTION_SUBMENU(NAME, OPTIONS_LIST) \
Outcome NAME (Arguments Data) \
{ \
	Outcome Status = Outcome_OK; \
	if (Data.Count <= 0){HelpMenu(OPTIONS_LIST); return Status;} \
	else { \
	Arguments PassedData = Arguments_New(Data.Count-1,Data.Entry+1,false); \
	Status = CallOption(Data.Entry[0],PassedData,OPTIONS_LIST);}\
	return Status; \
	}

#define JCUBECODE_FUNCTION_NAME(PREFIX, NAME) PREFIX##_##NAME

#define JCUBECODE_OPTION_DUMMY(PREFIX, NAME, DESCRIPTION) \
	Outcome JCUBECODE_FUNCTION_NAME(PREFIX, NAME) (Arguments Arguments){ignore Arguments; return Outcome_OK; }

#define JCUBECODE_OPTION_FUNCTION(PREFIX, NAME, DESCRIPTION) \
	Outcome JCUBECODE_FUNCTION_NAME(PREFIX, NAME) (Arguments Arguments);

#define JCUBECODE_OPTION_STRUCT(PREFIX, NAME, DESCRIPTION) \
	{#NAME, DESCRIPTION, JCUBECODE_FUNCTION_NAME(PREFIX, NAME)},

#define NONE

/*##====[ MACRO LISTS ]====##*/

#define JCUBECODE_OPTION_LIST(OPTION_ACTION) \
	OPTION_ACTION(_, project, "Project related commands (Building, running)") \
	OPTION_ACTION(_, utils, "Utilities for common tasks") \
	OPTION_ACTION(_, script, "Scripting tools") \
	OPTION_ACTION(_, shell, "Open the [J][C]ube[C]ode shell") \
	OPTION_ACTION(_, settings, "Global settings for [J][C]ube[C]ode")

#define JCUBECODE_PROJECT_LIST(OPTION_ACTION) \
	OPTION_ACTION(_project, refresh, "Scans the entire system for libs and Cubes.") \
	OPTION_ACTION(_project, install, "Install a Cube globally.") \
	OPTION_ACTION(_project, uninstall, "Uninstall a Cube globally.") \
	OPTION_ACTION(_project, init, "Initialize a project in the current directory.") \
	OPTION_ACTION(_project, uninit, "Remove JCubeCode data from a project") \
	OPTION_ACTION(_project, build, "Build the current project.") \
	OPTION_ACTION(_project, run, "Run the built artifacts.") \
	OPTION_ACTION(_project, clean, "Clean the project's temporary build files.")

#define JCUBECODE_UTILS_LIST(OPTION_ACTION) \
	OPTION_ACTION(_utils, directory, "Directory commands") \
	OPTION_ACTION(_utils, file, "File commands") \
	OPTION_ACTION(_utils, hash, "Hashing commands") \
	OPTION_ACTION(_utils, jcdata, "JCData functions") \
	OPTION_ACTION(_utils, system, "System enviroment commands") \
	OPTION_ACTION(_utils, net, "Network related commands")

#define JCUBECODE_SCRIPTS_LIST(OPTION_ACTION) \
	OPTION_ACTION(_scripts, execute, "Run script")

#define JCUBECODE_SETTINGS_LIST(OPTION_ACTION) \
	OPTION_ACTION(_settings, list, "List all current settings")

/*##====[ FUNCTIONS ]====##*/

Void HelpMenu
(
	JCubeCode_Option pointer Listed
);

Outcome CallOption
(
	CString Path,
	Arguments Arguments,
	JCubeCode_Option pointer OptionList
);

/*##====[ OPTION FUNCTIONS ]====##*/

JCUBECODE_OPTION_LIST(JCUBECODE_OPTION_FUNCTION)
JCUBECODE_PROJECT_LIST(JCUBECODE_OPTION_FUNCTION)
JCUBECODE_UTILS_LIST(JCUBECODE_OPTION_FUNCTION)
JCUBECODE_SCRIPTS_LIST(JCUBECODE_OPTION_FUNCTION)
JCUBECODE_SETTINGS_LIST(JCUBECODE_OPTION_FUNCTION)

#endif
