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

#ifndef JCUBECODE_CORE_C89_UTILITIES_H
#define JCUBECODE_CORE_C89_UTILITIES_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Various helpful functions that don't really fit a theme altogether, but are
 * helpful as is and belong to the C89 standard.
 */

/*##====[ INCLUDE ]====##*/

#include "../../Core/Core.h"

/*##====[ FUNCTIONS ]====##*/

/*
 * Deletes the file located at "Path".
 *
 * If the file is open by other processes, the behavior depends on enviroment.
 * Windows does not allow the file to be deleted.
 * POSIX systems unlink the directory entry, but the filesystem space used
 * is not reclaimed while open and while other hard links to the file exist.
 *
 * Returns 0 on success and non-zero on failure.
 */
JCubeLayer Integer Storage_FileRemove
(
	readonly CString Path
)
{
	return remove(Path);
}

/*
 * Changes the filename at "OldPath" to "NewPath".
 * If "NewPath" already exists, the behavior depends on enviroment.
 * Windows does not allow the "NewPath" location to exist and moving across
 * different drives fails.
 * POSIX systems allow overwrite of "NewPath" and renaming causes the file to
 * move to a different location too.
 *
 * Returns 0 on success and non-zero on failure.
 */
JCubeLayer Integer Storage_FileRename
(
	readonly CString OldPath,
	readonly CString NewPath
)
{
	return rename(OldPath, NewPath);
}

/*
 * Handles the current locale. A locale includes language, regional and even
 * cultural settings and it affects multiple things, such as numbers, dates,
 * currency formats and so on. The default locale is "C"
 *
 * If "TargetLocale" is NULL, the current locale is returned.
 *
 * ## Locale categories ##
 * - LC_ALL : All locale categories at once
 * - LC_COLLATE : String comparison and sorting
 * - LC_CTYPE : Character classification
 * - LC_MONETARY : Monetary formatting
 * - LC_NUMERIC : Decimal point and number formatting
 * - LC_TIME : Time and date formatting
 */
JCubeLayer CString Locale_Handle
(
	Integer Category,
	readonly CString TargetLocale
)
{
	return setlocale(Category, TargetLocale);
}

/*
 * Sorts the array with "EntryCount" members sized "EntrySize" at "ArrayPointer"
 * in ascending order. "OnEach" holds the comparison function used on each.
 */
JCubeLayer Void Utility_QuickSort
(
	MemoryAddress ArrayPointer,
	Size EntryCount,
	Size EntrySize,
	Integer FunctionPointer(OnEach, (Pointer(readonly Generic), Pointer(readonly Generic)))
)
{
	qsort(ArrayPointer, EntryCount, EntrySize, OnEach);
}

/*
 * Performs a binary search on a sorted array to find a matching element.
 * "OnEach" holds the comparison function used on each.
 * The comparison function must return 0 to indicate matching.
 *
 * Returns the memory address of the found member or NULL if not found.
 */
JCubeLayer MemoryAddress Utility_BinarySearch
(
	readonly MemoryAddress LookedFor,
	readonly MemoryAddress ArrayPointer,
	Size EntryCount,
	Size EntrySize,
	Integer FunctionPointer(OnEach, (Pointer(readonly Generic), Pointer(readonly Generic)))
)
{
	return bsearch(LookedFor, ArrayPointer, EntryCount, EntrySize, OnEach);
}

#endif
