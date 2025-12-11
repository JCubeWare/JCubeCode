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

#ifndef JCUBECODE_TYPES_STRINGS_H
#define JCUBECODE_TYPES_STRINGS_H

#ifdef JCUBECODE_TODO
#pragma message("[J][C]ube[Code] >> TODO: Finish Strings module.")
#endif

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"

/*##====[ DATA TYPES ]====##*/

typestruct(String,
	Size Length;
	CString Contents;
);

/*##====[ FUNCTIONS ]====##*/

Void String_Free
(
	String pointer Instance
);

String String_New
(
	CString Characters
);

Boolean String_IsEmpty
(
	String Instance
);

Outcome String_Initialize
(
	String pointer Instance, 
	Size Size
);

Outcome String_Set
(
	String pointer Instance, 
	CString SourceArray
);

Outcome String_SetFormatted
(
	String pointer Instance, 
	CString Format,
	variadicarguments
);

Outcome String_Copy
(
	String pointer Instance,
	String pointer SourceString
);

Outcome String_AppendCharacters
(
	String pointer Instance,
	variadicarguments
);

Outcome String_RemoveCharacters
(
	String pointer Instance, 
	Integer RemovalAmount
);

Boolean String_ValidateLength
(
	String Instance,
	Size MinimumSize,
	Size MaximumSize
);

Boolean String_Compare
(
	String FirstInstance,
	String SecondInstance
);

Outcome String_LocateSubstring
(
	String Instance,
	CString Substring,
	Size pointer FoundAtPosition
);

Outcome String_GetNumberFromString
(
	String Instance,
	Integer pointer IntegerResult,
	Float pointer FloatResult
);

Outcome String_ReplaceInString
(
	String pointer Instance,
	CString LookFor,
	CString ReplaceWith
);

#ifdef JCUBECODE_TODO
#pragma message("[J][C]ube[Code] >> Strings: Finish: ProcessPath(), IsOneOf()")

/*
 * Processes the specified path to remove leading symbols.
 */
Integer String_ProcessPath
(
	CString pointer directory
);

/*
 * Returns true if String matches at least one of the provided CStrings.
 */
Boolean String_IsOneOf
(
	String pointer Instance,
	variadicarguments
);

#endif

#endif
