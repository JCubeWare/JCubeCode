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

#ifndef JCUBECODE_CORE_C89_STANDARDIO_H
#define JCUBECODE_CORE_C89_STANDARDIO_H

/*##====[ DESCRIPTION ]====##*/
/*
 * The functions here are essential for standard I/O (input/output).
 * The streams in question are most often called stdin and stdout.
 */

/*##====[ INCLUDE ]====##*/

#include "../../Core/Core.h"

/*##====[ FUNCTIONS ]====##*/

/*
 * Scans a Character from the standard input and returns it.
 *
 * Returns EOF on error or file end.
 */
JCubeLayer Integer ScanCharacter
(
	noarguments
)
{
	return getchar();
}

/*
 * Prints a character to the standard output.
 *
 * Returns EOF on error or file end.
 */
JCubeLayer Integer PrintCharacter
(
	Integer Character
)
{
	return putchar(Character);
}

/*
 * Scan up to "MaxCount" characters from stdin into "Destination".
 * Scanning stops at newline (\n).
 *
 * Returns "Destination" if successful, NULL if false.
 */
JCubeLayer CString ScanCString
(
	CString Destination,
	Size MaxCount
)
{
	/* return gets(); */
	return fgets(Destination, MaxCount, stdin);
}

/*
 * Prints "Instance" onto stdout.
 *
 * Returns a positive value on success and EOF on failure.
 */
JCubeLayer Integer PrintCString
(
	CString Instance
)
{
	return puts(Instance);
}

/*##====[ WRAPPERS ]====##*/

/*
 * Prints all the arguments into stdout via the specified format.
 *
 * Returns the amount of bytes printed.
 */
#define PrintFormatted printf

/*
 * Prints all the arguments into the CString via the specified format.
 * Make sure you have enough space for the formatted output.
 *
 * Returns the amount of bytes printed.
 */
#define CString_PrintFormatted sprintf

/*
 * Prints all the arguments into the CString via the specified format up to X
 * characters.
 *
 * Returns the amount of bytes printed.
 */
#define CString_PrintFormattedCount snprintf

/*
 * Prints all the arguments into the FileStream via the specified format.
 *
 * Returns the amount of bytes printed.
 */
#define FileStream_PrintFormatted fprintf

/*
 * Scans all the arguments from stdin via the specified format.
 *
 * Returns the amount of matched arguments.
 */
#define ScanFormatted scanf

/*
 * Scans all the arguments from the CString via the specified format.
 *
 * Returns the amount of matched arguments.
 */
#define CString_ScanFormatted sscanf

/*
 * Scans all the arguments from the FileStream via the specified format.
 *
 * Returns the amount of matched arguments.
 */
#define FileStream_ScanFormatted fscanf

#endif
