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

#ifndef JCUBECODE_CORE_TYPES_MEMORYHANDLER_H
#define JCUBECODE_CORE_TYPES_MEMORYHANDLER_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Pointer arithmetics are a controversial C problem that many modern languages
 * simply do not have. With great power comes great responsibility, so instead
 * of abstracting them altogether, I simply reword it to be a bit simpler.
 *
 * MemoryHandler is basically just a pointer that also holds if the data at its
 * address must be freed or not... think of it as a bit safer pointer.
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"

/*##====[ DATA TYPES ]====##*/

typestruct(MemoryHandler,
	MemoryAddress Data;
	Boolean Allocated;
);

/*##====[ FUNCTIONS ]====##*/

/*
 * Creates a new MemoryHandler.
 * Holds where "Data" is located in memory.
 * If "Allocated" is true, memory belongs to it and upon freeing it, the memory
 * is freed too.
 */
MemoryHandler MemoryHandler_New
(
	MemoryAddress Data,
	Boolean Allocated
);

/*
 * Frees the MemoryHandler at "Instance".
 * If "Allocated" is true, memory at "Data" is freed along "Instance".
 */
Void MemoryHandler_Free
(
	MemoryHandler pointer Instance
);

/*
 * Sets the pointer for MemoryHandler at "Instance" to point at "Data"
 * and "Allocated" for if this new data now belongs to this MemoryHandler.
 *
 * If MemoryHandler was handling previously, it's freed before proceeding.
 */
Void MemoryHandler_Set
(
	MemoryHandler pointer Instance,
	MemoryAddress Data,
	Boolean Allocated
);

#endif
