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

#ifndef JCUBECODE_MODULES_FILESYSTEM_FILE_H
#define JCUBECODE_MODULES_FILESYSTEM_FILE_H

/*
 * TODO: Decide if this file is even needed and fix it up accordingly.
 * Maybe this whole thing will be merged into the Directory file.
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../Strings/Strings.h"

/*##====[ DATA TYPES ]====##*/

typestruct(File,
	Boolean InitDone;
	Boolean IsOpen;
	FileStream pointer Stream;
	String RelativePath;
	CString Filename;
	String RestrictModes;
	Size Size;
	Size Position;
);

/*##====[ FUNCTIONS ]====##*/

File File_New
(
	CString Filename,
	CString RestrictModes
);

Void File_Free
(
	File pointer Instance
);

Outcome File_Copy
(
	File pointer Instance,
	CString NewLocation
);

Outcome File_Read
(
	File pointer Instance,
	String pointer Buffer,
	Size pointer ReadAmount,
	Size StartFrom,
	Size Amount
);

Outcome File_Write
(
	File pointer Instance,
	String Buffer,
	Size MaxAmount
);

Outcome File_Remove
(
	File pointer Instance
);

#endif
