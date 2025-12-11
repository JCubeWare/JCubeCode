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

#ifndef JCUBECODE_MODULES_CHAIN_H
#define JCUBECODE_MODULES_CHAIN_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Linked lists are a super handy way to create flexible arrays. Whilst the
 * overhead can be huge, the offered flexibility outweighs it a lot.
 *
 * It's easier to imagine the linked list as a chain; the nodes connected to
 * each other by memory addresses. First member holds the address of the next.
 * Next member holds the previous member's address and the next member's too.
 *
 * Chain by itself only holds the address of the first member.
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"

/*##====[ DATA TYPES ]====##*/

typestruct(ChainNode,
	ChainNode pointer Next;
	ChainNode pointer Previous;
	MemoryAddress Data;
);

typestruct(Chain,
	ChainNode pointer Start;
);

/*##====[ FUNCTIONS ]====##*/

/*
 * Creates a new Chain object.
 * This instance now holds a "Start" memory address that points to a ChainNode
 * that holds the memory adress of data in "Data"
 */
Chain Chain_New
(
	MemoryAddress Data
);

/*
 * Frees the Chain object "Instance" is pointing to.
 * Slowly iterates and frees all the entries as well.
 */
Void Chain_Free
(
	Chain pointer Instance
);

/*
 * Returns the amount of ChainNodes in Chain located at "Instance".
 */
Size Chain_Count
(
	Chain pointer Instance
);

/*
 * Returns true if Chain at "Instance" is empty, false otherwise.
 */
Boolean Chain_IsEmpty
(
	Chain pointer Instance
);

/*
 * Appends a new ChainNode at the end of Chain at "Start" containing "Data".
 */
Outcome Chain_Append
(
	Chain pointer Start,
	MemoryAddress Data
);

/*
 * On each ChainNode in Chain at "Instance", do "ForEach()".
 * If "ForEach()" returns a non-OK outcome, this function returns it as well.
 */
Outcome Chain_ForEach
(
	Chain pointer Instance,
	Outcome FunctionPointer(ForEach, (MemoryAddress Entry, WholeInteger Index))
);

#endif
