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

#ifndef JCUBECODE_CORE_BASE_TARGET_H
#define JCUBECODE_CORE_BASE_TARGET_H

/*##====[ DESCRIPTION ]====##*/
/*
 * The purpose of this file is to keep track of all the platform specific
 * includes and define our own for easier track of what OS and architecture we
 * are on currently.
 */

#if defined(__linux__)
	#define OS_LINUX
	#define OS_UNIX
#elif defined(__unix__)
	#define OS_UNIX
#elif defined(__FreeBSD__)
    #define OS_FREEBSD
#elif defined(_WIN64) && defined(_WIN32)
	#define OS_WINDOWS_64
	#define OS_WINDOWS_
#elif defined(_WIN32)
	#define OS_WINDOWS_32
	#define OS_WINDOWS_
#elif defined(_WIN16)
	#define OS_WINDOWS_16
	#define OS_WINDOWS_
#elif defined(OS_MACOS)
	#define OS_MACINTOSH
#elif defined(_JCUBEOS)
	#define OS_JCUBEOS
#else
	#error "Unknown target OS. Please use a supported enviroment."
#endif

/*
 * TODO: Finish the target macros and add functions for use.
 */

#ifdef OS_LINUX
	#define _GNU_SOURCE
	#define LIB_C
	#define API_POSIX
	#define PATH_SEPARATOR '/'
	#define PATH_SEPARATOR_STRING "/"
	#define OS "Linux"
#endif

#ifdef OS_WINDOWS_
	#define LIB_C
	#define API_WINDOWS
	#define PATH_SEPARATOR '\\'
	#define PATH_SEPARATOR_STRING "\\"
	#define OS "Windows"
#endif

#endif
