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

#ifndef JCUBECODE_MODULES_LOGGING_LEVELS_H
#define JCUBECODE_MODULES_LOGGING_LEVELS_H

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../Terminal/Terminal.h"

/*##====[ LOG LEVELS LIST ]====##*/

#define LOGLEVELS_LIST(ACTION) \
	ACTION(DEBUG, "@", LIGHT_GRAY, NONE, NORMAL) \
	ACTION(NORMAL, "OK", GREEN, NONE, NORMAL) \
	ACTION(WARN, "WARN", YELLOW, NONE, NORMAL) \
	ACTION(ERROR, "ERROR", RED, NONE, NORMAL) \
	ACTION(FATAL, "! FATAL !", DARK_RED, NONE, BOLD) \
	ACTION(FRIDAY, "? FrIdAy ?", BLUE, WHITE, BOLD)

#define LOGLEVEL_ENUM(NAME, PREFIX, FOREGROUND, BACKGROUND, DECORATION) \
	LogLevel_##NAME,

#define LOGLEVEL_STRUCT(NAME, PREFIX, FOREGROUND, BACKGROUND, DECORATION) \
	{\
		PREFIX,\
		TerminalColor_##FOREGROUND,\
		TerminalColor_##BACKGROUND,\
		TerminalFont_##DECORATION\
	},

/*##====[ DATA TYPES ]====##*/

typestruct(LogLevelList,
	CString Icon;
	TerminalColor Foreground;
	TerminalColor Background;
	TerminalFont Decoration;
);

typeenum(LogLevel,
	LOGLEVELS_LIST(LOGLEVEL_ENUM)
);

/*##====[ VARIABLES ]====##*/

/*
 * Array of all the log levels and their information,
 * such as color, text decoration and prefix.
 */
extern readonly LogLevelList LogLevels[];

#endif
