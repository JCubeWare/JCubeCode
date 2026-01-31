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

#pragma once

#ifndef JCUBECODE_CORE_C89_ERROR_H
#define JCUBECODE_CORE_C89_ERROR_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Error handling functions.
 */

/*##====[ INCLUDE ]====##*/

#include "../../Core/Core.h"

/*##====[ DEFINES ]====##*/

/*
 * Error code variable that many C89 functions set the value of.
 */
#define ErrorCode errno

/*##====[ FUNCTIONS ]====##*/

/*
 * Return a CString that describes the error code provided in "ErrorCode".
 */
JCubeLayer CString Error_GetCString
(
	Integer ErrorReference
)
{
	return strerror(ErrorReference);
}

/*
 * Print both the prefix in "Prefix" and a representation of ErrorCode (errno)
 * onto the stdout.
 */
JCubeLayer Void Error_PrintPrefixed
(
	CString Prefix
)
{
	perror(Prefix);
}

#endif
