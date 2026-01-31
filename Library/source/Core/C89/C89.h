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

#ifndef JCUBECODE_CORE_C89_H
#define JCUBECODE_CORE_C89_H

/*##====[ JCUBELAYER ]====##*/
/*
 * This is a wrapper around the entire C89 standard.
 * Every single function has been wrapped and if your specific device does not
 * support one, you may provide your own implementation or discard it.
 * 
 * Doing this makes your code 100% portable across any device.
 */

/*##====[ INCLUDES ]====##*/

#include "Character.h"
#include "CString.h"
#include "Error.h"
#include "FileStream.h"
#include "Math.h"
#include "Memory.h"
#include "ProgramFlow.h"
#include "StandardIO.h"
#include "Time.h"
#include "Utilities.h"
#include "Variadic.h"

#endif
