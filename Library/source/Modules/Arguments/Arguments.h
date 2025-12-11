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

#ifndef JCUBECODE_MODULES_ARGUMENTS_H
#define JCUBECODE_MODULES_ARGUMENTS_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Very simple data type to replace having separate variables for the count and
 * the entry point.
 *
 * Essentially, this data type is just a list of memory pointers (CString Array)
 * and a count variable that keeps the amount of them.
 *
 * I am keeping it as Arguments until I decide on a more suitable name.
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../Strings/Strings.h"

/*##====[ STRUCTURES ]====##*/

typestruct(Arguments,
	WholeInteger Count;
	ArrayAny(CString) Entry;
	Boolean IsDynamic;
);

/*##====[ FUNCTIONS ]====##*/

/*
 * Creates a new Arguments object.
 * This instance now holds a "Count" members long list of CStrings starting at
 * "Entry".
 *
 * If "Allocated" is true, this object now also holds ownership of the memory
 * and on it being freed, frees the members too.
 *
 * If "Allocated" is false, then this is practically just a modular way to have
 * a reference.
 */
Arguments Arguments_New
(
	Integer Count,
	ArrayAny(CString) Entry,
	Boolean Allocated
);

/*
 * Frees the Arguments object "Instance" is pointing to.
 * If "Allocated" is true, also frees all the members before freeing itself.
 */
Void Arguments_Free
(
	Arguments pointer Instance
);

/*
 * Parses "Source" into tokens separated by "Delimiter" and places them into
 * Arguments variable at "Instance". Previous arguments at "Instance" are 
 * freed beforehand.
 *
 * NOTE: This function automatically sets the "Allocated" to true as the tokens
 * are allocated.
 */
Outcome Arguments_ConvertCString
(
	Arguments pointer Instance,
	CString Source,
	CString Delimiter
);

/*
 * Gets the content of "Instance" as a CString made up of tokens separated by
 * "Separator".
 *
 * If "Separator" is NULL or 0 bytes long, tokens are separated by nothing.
 * Returns NULL on error or if "Instance" has 0 members.
 */
CString Arguments_GetCString
(
	Arguments pointer Instance,
	CString Separator
);

#endif
