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

#ifndef JCUBECODE_CORE_C89_VARIADIC_H
#define JCUBECODE_CORE_C89_VARIADIC_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Variadic arguments (just Variadic for our purposes) are function arguments
 * that don't have a fixed definition. There can be one, there can be 50 or none
 * at all. To use them in functions, put "variadicarguments" as a final function
 * argument.
 */

/*##====[ INCLUDE ]====##*/

#include "../Base/Base.h"

/*##====[ DEFINES ]====##*/

/*
 * Start of the variadic argument list. The first variadic argument is located
 * after the last argument of the function.
 */
#define Variadic_Start(VARIADIC, LAST_FUNCTION_ARGUMENT) \
	va_start(VARIADIC, LAST_FUNCTION_ARGUMENT)

/*
 * End of the variadic argument list. Use this to properly release the variadic
 * list.
 */
#define Variadic_End(VARIADIC) va_end(VARIADIC)

/*
 * Get the variadic argument as a specific "DATA_TYPE" and advance onto the next
 * one with the next call.
 */
#define Variadic_GetNext(VARIADIC, DATA_TYPE) \
	va_arg(VARIADIC, DATA_TYPE)

/*
 * Copy the variadic arguments from "SOURCE" to "DESTINATION".
 */
#define Variadic_Copy(DESTINATION, SOURCE) va_copy(DESTINATION, SOURCE)

/*##====[ PRINTING ]====##*/

/*
 * Print all the variadic arguments into the standard output via the format.
 *
 * Returns the amount of bytes that were printed.
 */
JCubeLayer Integer Variadic_PrintFormatted
(
	readonly CString Format,
	Variadic Arguments
)
{
	return vprintf(Format, Arguments);
}

/*
 * Print all the variadic arguments into "Destination" via the format provided.
 * Be vary about the "Destination" being big enough to fit the formatted result.
 *
 * Returns the amount of bytes that were printed into the CString.
 */
JCubeLayer Integer Variadic_CString_PrintFormatted
(
	CString Destination,
	readonly CString Format,
	Variadic Arguments
)
{
	return vsprintf(Destination, Format, Arguments);
}

/*
 * Print all the variadic arguments into "Destination" via the format provided
 * up to "MaxCount" bytes. Rest will be cut off.
 *
 * Returns the amount of bytes that were printed into the CString.
 */
JCubeLayer Integer Variadic_CString_PrintFormattedCount
(
	CString Destination,
	Size MaxCount,
	readonly CString Format,
	Variadic Arguments
)
{
	return vsnprintf(Destination, MaxCount, Format, Arguments);
}

/*
 * Print all the variadic arguments into "Destination" via the format provided.
 *
 * Returns the amount of bytes that were printed into the CString.
 */
JCubeLayer Integer Variadic_FileStream_PrintFormatted
(
	FileStream pointer Destination,
	readonly CString Format,
	Variadic Arguments
)
{
	return vfprintf(Destination, Format, Arguments);
}

/*##====[ SCANNING ]====##*/

/*
 * Scan data from the standard stream and put them into the addresses which are
 * held in the variadic arguments "Arguments" according to "Format"
 *
 * Returns the amount of tokens that were retrieved from the stream.
 */
JCubeLayer Integer Variadic_ScanFormatted
(
	readonly CString Format,
	Variadic Arguments
)
{
	return vscanf(Format, Arguments);
}

/*
 * Scan data from "Source" and put them into the addresses which are
 * held in the variadic arguments "Arguments" according to "Format"
 *
 * Returns the amount of tokens that were retrieved from the CString.
 */
JCubeLayer Integer Variadic_CString_ScanFormatted
(
	readonly CString Source,
	readonly CString Format,
	Variadic Arguments
)
{
	return vsscanf(Source, Format, Arguments);
}

/*
 * Scan data from "Source" and put them into the addresses which are
 * held in the variadic arguments "Arguments" according to "Format"
 *
 * Returns the amount of tokens that were retrieved from the FileStream.
 */
JCubeLayer Integer Variadic_FileStream_ScanFormatted
(
	FileStream pointer Source,
	readonly CString Format,
	Variadic Arguments
)
{
	return vfscanf(Source, Format, Arguments);
}

#endif
