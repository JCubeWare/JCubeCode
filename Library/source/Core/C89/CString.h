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

#ifndef JCUBECODE_CORE_C89_CSTRING_H
#define JCUBECODE_CORE_C89_CSTRING_H

/*##====[ DESCRIPTION ]====##*/
/*
 * CStrings are a data type that's not fully a data type in itself.
 * It's a character pointer that tells us the start of the string and what 
 * tells us the end is a byte that's fully 0 (00000000).
 *
 * Hence the term NULL-terminated string. It can have any size, as we don't know
 * the size without iterating through it.
 */

/*##====[ INCLUDE ]====##*/

#include "../../Core/Core.h"
#include "Memory.h"

/*##====[ FUNCTIONS ]====##*/

/*
 * Copies all the bytes from the CString "Source" into the location of 
 * "Destination".
 *
 * Verify that "Destination" is long enough (null at the end included) to 
 * contain the entire "Source" CString, otherwise you're risking overflow.
 */
JCubeLayer CString CString_Copy
(
	CString Destination,
	readonly CString Source
)
{
	return strcpy(Destination, Source);
}

/*
 * Count limited version of CString_Copy(). Copies up to "Count" bytes from the 
 * CString "Source" into the location of "Destination".
 *
 * Confirm that "Destination" is long enough (zero byte at the end included) to
 * contain the entire "Source" CString, otherwise you're risking overflow.
 *
 * Safest way to use the function is to set the "Count" as the maximum capacity
 * "Destination" can hold.
 */
JCubeLayer CString CString_CopyCount
(
	CString Destination,
	readonly CString Source,
	Size Count
)
{
	return strncpy(Destination, Source, Count);
}

/*
 * Appends "Source" at the end of "Destination". Terminating null will be
 * overwritten by the first character of "Source"
 *
 * Confirm that the "Destination" is long enough (null at the end included) to 
 * contain the entire "Source" CString, otherwise you're risking overflow and
 * possibly a segmentation fault
 *
 * "Destination" is returned so you can chain this function into other CString
 * functions
 */
JCubeLayer CString CString_Append
(
	CString Destination,
	readonly CString Source
)
{
	return strcat(Destination, Source);
}

/*
 * Appends "Count" characters from "Source" at the end of "Destination". 
 * Terminating null will be overwritten by the first character of "Source".
 *
 * If the CString is shorter than "Count", only contents up to NULL terminator
 * are copied over.
 *
 * Ensure the "Destination" is long enough (null at the end included) to 
 * contain the entire "Source" CString, otherwise you're risking overflow and
 * possibly a segmentation fault
 *
 * "Destination" is returned so you can chain this function into other CString
 * functions
 */
JCubeLayer CString CString_AppendCount
(
	CString Destination,
	readonly CString Source,
	Size Count
)
{
	return strncat(Destination, Source, Count);
}

/*
 * Transforms the CString from "Source" into the current locale and places it in
 * "Destination".
 *
 * Doing CString_Comprare() on transformed CStrings behaves the same as using
 * CString_CompareLocale() on original CStrings.
 *
 * Ensure the "Destination" is long enough (null at the end included) to 
 * contain the entire "Source" CString, otherwise you're risking overflow and
 * possibly a segmentation fault.
 *
 * If "Count" is ​0​, then "Destination" can be empty. 
 */
JCubeLayer Size CString_LocaleTransform
(
	CString Destination,
	readonly CString Source,
	Size Count
)
{
	return strxfrm(Destination, Source, Count);
}

/*
 * Counts all the characters in CString before the NULL terminator.
 * The memory on this address may be bigger than the CString itself, so keep in
 * mind that this function counts the CURRENT - 1 used bytes.
 *
 * Ensure the passed address is not NULL to avoid undefined behavior.
 */
JCubeLayer Size CString_Length
(
	readonly CString Instance
)
{
	return strlen(Instance);
}

/*
 * Compares both CStrings lexicographically. Characters are treated as Bytes.
 * 
 * Returns 0 if the CStrings are identical.
 * If the return value is negative, last compared Byte in "Second" is greater.
 * If the return value is positive, last compared Byte in "first" is greater.
 */
JCubeLayer Integer CString_Compare
(
	readonly CString First,
	readonly CString Second
)
{
	return strcmp(First, Second);
}

/*
 * Compares at most "Count" characters from both CStrings.
 * Characters are treated as Bytes.
 * 
 * Returns 0 if the CStrings are identical.
 * If the return value is negative, last compared Byte in "Second" is greater.
 * If the return value is positive, last compared Byte in "first" is greater.
 */
JCubeLayer Integer CString_CompareCount
(
	readonly CString First,
	readonly CString Second,
	Size Count
)
{
	return strncmp(First, Second, Count);
}

/*
 * Compares both CStrings according to the current locale. (LC_COLLATE)
 * Characters are treated as Bytes.
 * 
 * Returns 0 if the CStrings are identical.
 * If the return value is negative, last compared Byte in "Second" is greater.
 * If the return value is positive, last compared Byte in "first" is greater.
 */
JCubeLayer Integer CString_CompareLocale
(
	readonly CString First,
	readonly CString Second
)
{
	return strcoll(First, Second);
}

/*
 * Traverses the CString to find the first matching character.
 *
 * Returns the address of the found substring or an Empty pointer.
 */
JCubeLayer CString CString_FindFirst
(
	readonly CString Instance,
	Integer Wanted
)
{
	return strchr(Instance, Wanted);
}

/*
 * Traverses the CString backwards to find the last matching character.
 *
 * Returns the address of the found substring or an Empty pointer.
 */
JCubeLayer CString CString_FindLast
(
	readonly CString First,
	Character Wanted
)
{
	return strrchr(First, Wanted);
}

/*
 * Returns the amount of characters found in "Instance" that are also found in
 * "Matcher". Eseentialy, counts how many characters until the next character
 * does not belong to "Matcher"
 *
 * The address of the first mismatch is at Instance + return value.
 */
JCubeLayer Size CString_CountMatching
(
	readonly CString Instance,
	readonly CString Matcher
)
{
	return strspn(Instance, Matcher);
}

/*
 * Returns the amount of characters found in "Instance" that are NOT found in
 * "Matcher". Eseentialy, counts how many characters until the next character
 * belongs to "Matcher"
 *
 * The address of the first mismatch is at Instance + return value.
 */
JCubeLayer Size CString_CountDifferent
(
	readonly CString Instance,
	readonly CString Matcher
)
{
	return strcspn(Instance, Matcher);
}

/*
 * Traverses "Instance" to locate at least one of the characters in "Matcher"
 *
 * Returns the memory address of the first character from "Matcher" that appears
 * in "Instance". If none are found, returns NULL.
 */
JCubeLayer CString CString_LocateFirstMatch
(
	readonly CString Instance,
	readonly CString Matcher
)
{
	return strpbrk(Instance, Matcher);
}

/*
 * Traverses "Instance" to find the first occurence of a substring.
 *
 * Returns the memory address of the first character from "Substring" that appears
 * in Instance. If none are found, returns NULL.
 */
JCubeLayer CString CString_LocateSubstring
(
	readonly CString Instance,
	readonly CString Substring
)
{
	return strstr(Instance, Substring);
}

/*
 * Tokenizes a CString by adding a NULL terminator at every first Character of
 * "Delimiter" in "Instance".
 *
 * If "Instance" is Empty after the first "Instance" was provided, iteration is
 * continued. You first provide the CString and then repeat with Empty until no
 * tokens are found.
 *
 * If a token is not found, this function return NULL.
 *
 * WARNING: This function modifies the original CString and uses a Persistent
 * variable to keep track of where it left off so do not use it with Threads.
 */
JCubeLayer CString CString_Tokenize
(
	readonly CString Instance,
	readonly CString Delimiter
)
{
	return strtok(Instance, Delimiter);
}

/*
 * Returns the Integer created by converting base-10 digits from the CString.
 * Sign character (+ or -) is also accounted for.
 *
 * Stops at the first non-digit character and returns the partial result.
 * If conversion fails altogether, 0 is returned.
 */
JCubeLayer Integer CString_GetAsInteger
(
	readonly CString Instance
)
{
	return atoi(Instance);
}

/*
 * Returns the Long created by converting base-10 digits from the CString.
 * Sign character (+ or -) is also accounted for.
 *
 * Stops at the first non-digit character and returns the partial result.
 * If conversion fails altogether, 0 is returned.
 */
JCubeLayer Long CString_GetAsLong
(
	readonly CString Instance
)
{
	return atol(Instance);
}

/*
 * Returns the Double created from the CString.
 *
 * Sign character (+ or -) is also accounted for.
 * The decimal point is determined by the current C locale.
 * If e or E is followed by digits, it's counted as an exponent
 * Stops at the first non-digit character and returns the partial result.
 * If conversion fails altogether, 0.0 is returned.
 */
JCubeLayer Double CString_GetAsDouble
(
	readonly CString Instance
)
{
	return atof(Instance);
}

/*
 * Returns the Double created from the CString and places the point where the
 * converting stopped at in "StoppedAt".
 *
 * Sign character (+ or -) is also accounted for.
 * The decimal point is determined by the current C locale.
 * If e or E is followed by digits, it's counted as an exponent
 * Stops at the first non-digit character and returns the partial result.
 * If conversion fails altogether, 0.0 is returned.
 */
JCubeLayer Double CString_GetAsDoublePrecise
(
	readonly CString Instance,
	CString pointer StoppedAt
)
{
	return strtod(Instance, StoppedAt);
}

/*
 * Returns the Long created from the CString and places the point where the
 * converting stopped at in "StoppedAt".
 *
 * Base is the number base, such as decimal(10), hexadecimal(16) and binary(2)
 * Sign character (+ or -) is also accounted for.
 * If conversion fails altogether, 0.0 is returned.
 */
JCubeLayer Long Convert_GetAsLongPrecise
(
	readonly CString Instance,
	CString pointer StoppedAt,
	Integer Base
)
{
	return strtol(Instance, StoppedAt, Base);
}

/*
 * Returns the Whole Long created from the CString and places the point where
 * the converting stopped at in "StoppedAt".
 *
 * Base is the number base, such as decimal(10), hexadecimal(16) and binary(2)
 * Sign character (+ or -) is also accounted for.
 * If conversion fails altogether, 0.0 is returned.
 */
JCubeLayer WholeLong Convert_GetAsWholeLongPrecise
(
	readonly CString Instance,
	CString pointer StoppedAt,
	Integer Base
)
{
	return strtoul(Instance, StoppedAt, Base);
}

#endif
