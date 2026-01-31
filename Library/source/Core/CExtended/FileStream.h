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

#ifndef JCUBECODE_CORE_EXTENDED_FILESTREAM_H
#define JCUBECODE_CORE_EXTENDED_FILESTREAM_H

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"

/*##====[ FEATURES ]====##*/

/*
 * Writes the specified CString in "Instance" into the FileStream at "DumpFile".
 * This CString escapes all escape characters AND quotes with \ in front of it.
 */
Void FileStream_WriteCStringEscaped
(
	FileStream pointer Instance,
	readonly CString Passed
);

/*
 * Returns the total size of the file in bytes.
 * This operation stores the cursor position so it's safe to use it at any
 * point of your program flow.
 */
Size FileStream_GetSize
(
	FileStream pointer Instance
);

/*
 * Reads the entire file at "Instance" into memory.
 *
 * Returns the memory address of the read memory or NULL on failure.
 */
CString FileStream_ReadFull
(
	FileStream pointer Instance
);

#endif
