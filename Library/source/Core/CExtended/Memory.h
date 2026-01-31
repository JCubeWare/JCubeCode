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

#ifndef JCUBECODE_CORE_EXTENDED_MEMORY_H
#define JCUBECODE_CORE_EXTENDED_MEMORY_H

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../C89/C89.h"

/*##====[ FEATURES ]====##*/

/*
 * Creates a new member of this type and returns the address.
 * Wrapper over Memory_ClearAllocate() that assumes you only want one member
 * of type "DATA_TYPE"
 */
#define Memory_New(DATA_TYPE) Memory_ClearAllocate(1, sizeof(DATA_TYPE))

/*
 * Sets the memory occupied by "VARIABLE" to be all zeroes.
 * Best used for cleaning buffers.
 * Wrapper over Memory_Set() that assumes you want all zero bytes.
 */
#define Memory_Clear(VARIABLE) Memory_Set(VARIABLE, 0, sizeof(VARIABLE));

#endif
