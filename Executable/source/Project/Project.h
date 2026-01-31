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

#ifndef JCUBECODE_PROJECT_H
#define JCUBECODE_PROJECT_H

/*##====[ INCLUDES ]====##*/

#include "../Common.h"
#include "Project.h"

/*##====[ DEFINES ]====##*/

#define JCUBECODE_PROJECT_FILE "./Project.jcdata"
#define JCUBECODE_TEMP_PREFIX "_."
#define JCUBECODE_BUILD_DIR JCUBECODE_TEMP_PREFIX "build"
#define JCUBECODE_OBJECTS_DIR JCUBECODE_TEMP_PREFIX "objects"

#define JCUBECODE_BUILD_ALL "all"

#define JCUBECODE_MAX_ARGUMENTS 500

/*##====[ DATA TYPES ]====##*/

typestruct(ProjectTarget,
	CString Artifact;
	CString Type;
	CString Compiler;
	Dynamic Options;
	Dynamic Sources;
	Dynamic Dependencies;
	Dynamic Objects;
);

/*##====[ FUNCTIONS ]====##*/

/*
 * Returns all build/run targets in a dictionary.
 */
DataValue pointer Project_GetTargets
(
	noarguments
);

#endif
