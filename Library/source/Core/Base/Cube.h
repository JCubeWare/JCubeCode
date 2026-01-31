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

#ifndef JCUBECODE_CORE_BASE_CUBE_H
#define JCUBECODE_CORE_BASE_CUBE_H

/*##====[ DESCRIPTION ]====##*/
/*
 * The Cube API for verifying certain things within your application, such as
 * version and build time.
 */
/*##====[ INCLUDES ]====##*/

#include "Types.h"

/*##====[ DATA TYPES ]====##*/

/*
 * Holds the version data.
 *
 * Major means JCubeCode underwent heavy changes that impact your existing code.
 * Minor is for if JCubeCode had updates, such as new modules.
 * Patch is reserved for bugfixes and very light changes.
 */
typestruct(JCubeVersion,
	readonly WholeInteger Major;
	readonly WholeInteger Minor;
	readonly WholeInteger Patch;
);

/*
 * Holds the date and time for when this specific build was compiled.
 */
typestruct(JCubeBuild,
	readonly CString Date;
	readonly CString Time;
);

/*
 * Main JCube structure.
 *
 * This one contains the JCube's name, description, JCubeVersion and JCubeBuild
 * structures.
 */
typestruct(JCube,
	readonly CString Name;
	readonly CString Description;
	readonly JCubeVersion Version;
	readonly JCubeBuild Build;
);

#endif
