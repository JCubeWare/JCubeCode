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

#ifndef JCUBECODE_CORE_EXTENDED_CSTRING_H
#define JCUBECODE_CORE_EXTENDED_CSTRING_H

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../C89/C89.h"

/*##====[ FEATURES ]====##*/

/*
 * Returns true if "First" and "Second" match. Otherwise, returns false.
 */
Boolean CString_Matches
(
	readonly CString First,
	readonly CString Second
);

/*
 * Returns a memory address of the newly created CString that contains "Source"
 * If "Source" is NULL or a memory failure happens, NULL is returned.
 */
CString CString_Set
(
	CString Source
);

/*
 * Returns a memory address of the newly created CString formatted with "Format"
 * and variadic arguments. Returns nullpointer on failure.
 */
CString CString_SetFormatted
(
	CString Format,
	variadicarguments
);

#endif
