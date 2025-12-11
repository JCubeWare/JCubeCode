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
/*#pragma message("[J][C]ube[Code]>> TODO: Finish 'Dictionary' type.")*/

#ifndef JCUBECODE_MODULES_DICTIONARY_H
#define JCUBECODE_MODULES_DICTIONARY_H

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../Dynamic/Dynamic.h"

/*##====[ DATA TYPES ]====##*/

typestruct(DictionaryEntry,
	Size Hash;
	CString Key;
	MemoryHandler Value;
);

typestruct(Dictionary,
	Dynamic Contents;
);

typedef DictionaryEntry DictionaryInitial[];

/*##====[ FUNCTIONS ]====##*/

/*
 * Creates a new Dictionary object.
 * This instance now holds a Dynamic list of DictionaryEntry members.
 * 
 * The instance copies all members from "InitialState" so if "InitialState" is
 * empty, instance will also be empty.
 */
Dictionary Dictionary_New
(
	DictionaryInitial InitialState
);

/*
 * Frees the Dictionary object "Instance" is pointing to.
 * Slowly iterates and frees all the entries as well, preparing it for reuse.
 */
Void Dictionary_Free
(
	Dictionary pointer Instance
);

/*
 * Returns the amount of entries in Dictionary located at "Instance".
 * Under the hood, it's Dynamic.Count
 */
Size Dictionary_Count
(
	Dictionary pointer Instance
);

/*
 * Returns true if Chain at "Instance" is empty, false otherwise.
 */
Boolean Dictionary_IsEmpty
(
	Dictionary pointer Instance
);

/*
 * Sets the DictionaryEntry with key value of "Key" to "Value"
 * Also tells if "TransferOwnership" applies (is allocated).
 *
 * Original entry is freed if the Dictionary at "Instance" has ownership.
 * If an entry doesn't exist, it's added at the end.
 */
Outcome Dictionary_Set
(
	Dictionary pointer Instance,
	CString Key,
	Generic pointer Value,
	Boolean TransferOwnership
);

/*
 * Returns the memory address of data located in Dictionary at "Instance"
 * inside the entry that can be identified with "Key".
 *
 * On error or no data, NULL is returned instead.
 */
Generic pointer Dictionary_Get
(
	Dictionary pointer Instance,
	CString Key
);

/*
 * Returns the memory address of entry located in Dictionary at "Instance"
 * that can be identified with "Key".
 *
 * On error or no data, NULL is returned instead.
 */
DictionaryEntry pointer Dictionary_GetEntry
(
	Dictionary pointer Instance,
	CString Key
);

/*
 * On each DictionaryEntry in Dictionary at "Instance", do "ForEach()".
 * If "ForEach()" returns a non-OK outcome, this function returns it as well.
 */
Outcome Dictionary_ForEach
(
	Dictionary pointer Instance,
	Outcome FunctionPointer(ForEach, (MemoryAddress Entry, WholeInteger Index))
);

#endif
