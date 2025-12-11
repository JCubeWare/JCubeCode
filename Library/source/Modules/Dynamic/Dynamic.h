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

#ifndef JCUBECODE_MODULES_DYNAMIC_H
#define JCUBECODE_MODULES_DYNAMIC_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Dynamic is a dynamic array type that automatically handles arrays and common
 * operations on them. This is one of the core implementations of JCubeCode.
 *
 * Solves a lot of problems regarding arrays and memory management and on top 
 * of that, provides a convenient API to keep it simple, fast and easy to use.
 *
 * The growth is handled geometrically (multiplying by growth on reallocation).
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../MemoryHandler/MemoryHandler.h"

/*##====[ DEFINES ]====##*/

#define DYNAMIC_INITIAL_CAPACITY 10
#define DYNAMIC_GROWTH 2

/*##====[ DATA TYPES ]====##*/

typestruct(Dynamic,
	ArrayDynamic(MemoryHandler) Entries;
	Size Count;
	Size Capacity;
);

typedef MemoryHandler DynamicInitial[];

/*##====[ FUNCTIONS ]====##*/

/*
 * Creates a new Dynamic object.
 * This instance now holds a Dynamic list of MemoryHandler members.
 * 
 * The instance copies all members from "InitialState" so if "InitialState" is
 * empty, instance will also be empty.
 */
Dynamic Dynamic_New
(
	DynamicInitial InitialState
);

/*
 * Frees the Dynamic object "Instance" is pointing to.
 * Slowly iterates and frees all the entries as well.
 */
Void Dynamic_Free
(
	Dynamic pointer Instance
);

/*
 * Returns true if Dynamic at "Instance" is empty, false otherwise.
 */
Boolean Dynamic_IsEmpty
(
	Dynamic pointer Instance
);

/*
 * Returns the memory address of the MemoryHandler inside Dynamic at "Instance"
 * located inside index "Position"
 *
 * If the position is invalid or no data is found, NULL is returned.
 */
MemoryHandler pointer Dynamic_Get
(
	Dynamic pointer Instance,
	Size Position
);

/*
 * Sets "Data" to index "Position" for Dynamic at "Instance"
 * If "TransferOwnership" is true, that means the memory at "Data" will be freed
 * if "Instance" is freed.
 */
Outcome Dynamic_Set
(
	Dynamic pointer Instance,
	Generic pointer Data,
	Boolean TransferOwnership,
	WholeInteger Position
);

/*
 * Adds "Data" to Dynamic at "Instance".
 * The newly created MemoryHandler is added at the end of this Dynamic.
 *
 * If "DoAllocate" is true, this data will be freed on "Instance" being freed.
 */
Outcome Dynamic_Add
(
	Dynamic pointer Instance,
	Generic pointer Data,
	Boolean DoAllocate
);

/*
 * Removes whatever data is located at "Index" inside Dynamic at "Instance".
 * All entries are shifted one spot back to compensate.
 */
Outcome Dynamic_Remove
(
	Dynamic pointer Instance,
	WholeInteger Index
);

/*
 * Iterates through the Dynamic at "Instance" to find if one of the entries
 * references "MemoryLocation" and afterwards, returns the index of where it is
 * located.
 *
 * On errors or if it doesn't exist, zero is returned.
 */
Size Dynamic_GetEntryIndex
(
	Dynamic pointer Instance,
	Generic pointer MemoryLocation
);

/*
 * On each MemoryHandler in Dynamic at "Instance", do "ForEach()".
 * If "ForEach()" returns a non-OK outcome, this function returns it as well.
 */
Outcome Dynamic_ForEach
(
	Dynamic pointer Instance,
	Outcome FunctionPointer(ForEach, (MemoryAddress Entry, WholeInteger Index))
);

#endif
