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

#ifndef JCUBECODE_MODULES_H
#define JCUBECODE_MODULES_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Modules are meant to replace the most common C libraries and help me to not
 * have to download million libs every single program. They are essentialy
 * structs with their own methods.
 *
 * In the future, this will be on a plugin basis, but for now it makes sense
 * to just straight up include them.
 *
 * If I decide some are too important to make them optional, they will remain
 * here.
 */

/*##====[ INCLUDES ]====##*/

#include "Arguments/Arguments.h"
#include "Chain/Chain.h"
#include "Dictionary/Dictionary.h"
#include "Dynamic/Dynamic.h"
#include "Filesystem/Directory.h"
#include "Filesystem/File.h"
#include "JCData/JCData.h"
#include "Logging/Logging.h"
#include "MemoryHandler/MemoryHandler.h"
#include "Parsing/Parsing.h"
#include "Strings/Strings.h"
#include "Terminal/Terminal.h"

#endif
