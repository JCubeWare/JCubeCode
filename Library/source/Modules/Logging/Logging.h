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

#ifndef JCUBECODE_MODULES_LOGGING_H
#define JCUBECODE_MODULES_LOGGING_H

/*#pragma message("[J][C]ube[Code]>> TODO: Finish 'Logging' module.")*/

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "Levels.h"

/*##====[ DATA TYPES ]====##*/

typestruct(Logger,
	CString Name;
	LogLevel Level;

	CString Format;
	CString TimeFormat;

	Boolean UseSpecialCharacters;
	Boolean ShowName;
	Boolean ShowTime;
	Boolean ShowLevel;

	FileStream pointer Stream;
);

/*##====[ FUNCTIONS ]====##*/

/*
 * Print variadic arguments according to format in "Format" with level
 * "LogLevel" into the Logger at "Instance".
 *
 * If "LogLevel" is smaller than the one of "Instance", function does nothing.
 */
Outcome Logger_Print
(
	Logger Instance,
	LogLevel LogLevel,
	CString Format,
	variadicarguments
);

#endif
