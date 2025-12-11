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

#ifndef JCUBECODE_CORE_EXTENDED_FILESYSTEM_H
#define JCUBECODE_CORE_EXTENDED_FILESYSTEM_H

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"

/*##====[ FEATURES ]====##*/

/*
 * Returns the filename portion of "Path".
 * If the return value and "Path" match, the Path is just the filename already.
 */
CString Storage_GetFilename
(
	CString Path
);

/*
 * Attempts to return the full path of the specified file/entry at "Path".
 * If "ResolveBuffer" is NULL, the result is allocated and returns the address.
 */
JCubeLayer CString Storage_GetFullPath
(
	readonly CString Path,
	CString ResolveBuffer
)
{
#if defined(OS_LINUX)
	return realpath(Path, ResolveBuffer);
#elif defined(OS_WINDOWS_)
	return _fullpath(ResolveBuffer, Path, PATH_MAX);
#else
#error "FileSystem_GetFullPath() has no implementation for this platform."
#endif
}

/*
 * Creates a directory at "Path"
 */
JCubeLayer Integer Storage_CreateDirectory
(
	readonly CString Path
)
{
#if defined(OS_LINUX)
	return mkdir(Path, 0755);
#elif defined(OS_WINDOWS_)
	return _mkdir(Path);
#else
#error "FileSystem_MakeDirectory() has no implementation for this platform."
#endif	
}

#endif
