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

#ifndef JCUBECODE_MODULES_FILESYSTEM_DIRECTORY_H
#define JCUBECODE_MODULES_FILESYSTEM_DIRECTORY_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Directory management functions. There are very few libraries for this I like
 * and this was one of the motivations for JCubeCode.
 *
 * You load the directory into the memory and can now do operations on files,
 * copy directories and what not.
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../Dynamic/Dynamic.h"
#include "File.h"

/*##====[ DATA TYPES ]====##*/

/*
 * Represents the directory loaded into the memory.
 * Can also contain subdirectories.
 */
typestruct(Directory,
	Boolean InitDone;
	Boolean IsOpen;
	DirectoryHandler Stream;
	String Path;
	CString Name;
	Dynamic Directories;
	Dynamic Files;
);

/*##====[ FUNCTIONS ]====##*/

/*
 * Creates a new Directory object.
 * 
 * On non-existent path or opening failing, InitDone is false.
 */
Directory Directory_New
(
	CString Path
);

/*
 * Frees the Directory object "Instance" is pointing to.
 * Slowly iterates and frees all the entries as well.
 */
Void Directory_Free
(
	Directory pointer Instance
);

/*
 * Loads the entire directory into object at "Instance".
 * This object now holds the reference to all the files located within.
 */
Outcome Directory_Load
(
	Directory pointer Instance
);

/*
 * Copies the directory located at "Instance" into the path in "CopyDirectory"
 */
Outcome Directory_Copy
(
	Directory pointer Instance,
	CString CopyDirectory
);

#endif
