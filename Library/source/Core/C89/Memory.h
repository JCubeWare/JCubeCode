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

#ifndef JCUBECODE_CORE_C89_MEMORY_H
#define JCUBECODE_CORE_C89_MEMORY_H

/*##====[ DESCRIPTION ]====##*/
/*
 * This file handles all memory operations.
 * Functions here operate on raw memory, so unlike C-strings, they rely heavily
 * on knowing the prior knowledge on what sort of memory you're trying to
 * operate on.
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"

/*##====[ FUNCTIONS ]====##*/

/*
 * Allocates "Count" bytes of memory for you by the system allocator,
 * then returns the memory location of the created block.
 *
 * The ownership of this piece of memory now belongs to you, so its your
 * responsibility to free the memory once it's no longer needed.
 *
 * If allocation fails, returns NULL.
 */
JCubeLayer MemoryAddress Memory_Allocate
(
	Size Count
)
{
	return malloc(Count);
}

/*
 * Allocates "EntryCount * EntrySize" bytes of memory for you by the system allocator,
 * then returns the memory location of the created block.
 *
 * This new block of memory is also cleared so it contains only zeroed bytes.
 *
 * The ownership of this piece of memory now belongs to you, so its your
 * responsibility to free the memory once it's no longer needed.
 *
 * If allocation fails, returns NULL.
 */
JCubeLayer MemoryAddress Memory_ClearAllocate
(
	Size EntryCount,
	Size EntrySize
)
{
	return calloc(EntryCount, EntrySize);
}

/*
 * Attempts to reallocate the specified memory block to be "Count" bytes big.
 * Either the original memory address is kept and the block is resized or
 * the original memory is freed and a new block with the contents is created.
 *
 * If "Memory" is empty, then this function behaves like "Memory_Allocate(Count)"
 * This new block of memory is also cleared so it contains only zeroed bytes.
 *
 * When using this function, always do it on a temporary pointer, so you don't
 * accidentaly overwrite the variable which holds the pointer you want to resize.
 *
 * The ownership of this piece of memory now belongs to you, so its your
 * responsibility to free the memory once it's no longer needed.
 *
 * If allocation fails, returns NULL.
 *
 */
JCubeLayer MemoryAddress Memory_Reallocate
(
	MemoryAddress Memory,
	Size Bytes
)
{
	return realloc(Memory, Bytes);
}

/*
 * Free the memory the pointer you passed points to.
 *
 * If "Memory" is empty, function does absolutely nothing.
 *
 * Pass only memory you allocated or you risk undefined behavior.
 *
 * When using this function, always do it on a temporary pointer, so you don't
 * accidentaly overwrite the variable which holds the pointer you want to resize.
 *
 * The ownership of this piece of memory now belongs to you, so its your
 * responsibility to free the memory once it's no longer needed.
 *
 * If allocation fails, returns NULL.
 *
 */
JCubeLayer Void Memory_Free
(
	MemoryAddress Memory
)
{
	free(Memory);
}

/*
 * At location pointed by "Memory", set "Count" bytes to "Value"
 *
 * NOTE:
 * "Value" is passed as an int, but only the first 8 bytes are counted,
 * essentialy converting to Byte type.
 *
 * In C89 and before, default argument promotions mean that types narrower than 
 * Integer are always promoted to int when passed to a function without a 
 * proper prototype (K & R styled functions).
 */
JCubeLayer MemoryAddress Memory_Set
(
	MemoryAddress Memory,
	Integer Value,
	Size Count
)
{
	return memset(Memory, Value, Count);
}

/*
 * Copies "Count" bytes from "Source" into a mediate buffer, then writes "Count"
 * bytes into the "Destination" location, thus enabling correct overlap.
 *
 * Verify that "Count" is not bigger than the actual size of the memory to copy
 * to avoid an overflow.
 */
JCubeLayer MemoryAddress Memory_Move
(
	MemoryAddress Destination,
	readonly MemoryAddress Source,
	Size Count
)
{
	return memmove(Destination, Source, Count);
}

/*
 * At "Memory", starts iterating through first "Count" bytes.
 * If a "Value" byte is found, function returns its address, otherwise
 * an empty pointer is returned.
 *
 * NOTE:
 * "Value" is passed as an int, but only the first 8 bytes are counted,
 * essentialy converting to Byte type.
 */
JCubeLayer MemoryAddress Memory_LocateFirstByte
(
	readonly MemoryAddress Memory,
	Integer Value,
	Size Count
)
{
	return memchr(Memory, Value, Count);
}

/*
 * Creates a binary copy of "Count" bytes at "Origin" and 
 * then places them into "Destination" address.
 *
 * Verify that "Count" is not bigger than the actual size of the memory to copy
 * to avoid an overflow.
 */
JCubeLayer MemoryAddress Memory_Copy
(
	MemoryAddress Destination,
	readonly MemoryAddress Origin,
	Size Count
)
{
	return memcpy(Destination, Origin, Count);
}

/*
 * Compares "Count" bytes at "First" address and "Second" address.
 * 
 * If they match, this function returns 0.
 */
JCubeLayer Integer Memory_Compare
(
	readonly MemoryAddress First,
	readonly MemoryAddress Second,
	Size Count
)
{
	return memcmp(First, Second, Count);
}

#endif
