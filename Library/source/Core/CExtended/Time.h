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

#ifndef JCUBECODE_CORE_EXTENDED_TIME_H
#define JCUBECODE_CORE_EXTENDED_TIME_H

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"

/*##====[ FEATURES ]====##*/

/*
 * Attempts to sleep (block this thread) for "Milliseconds" time.
 * Schedulers may delay the code for longer than this value, so use only to
 * limit rate and save energy.
 */
JCubeLayer Integer Time_Sleep
(
	Integer Milliseconds
)
{
#if defined(OS_LINUX)
	struct timespec WantedTime = {0, Milliseconds * 1000};
	return nanosleep(address WantedTime, nullpointer);
#elif defined(OS_WINDOWS_)
	Sleep(Milliseconds);
	return 0;
#else
#error "Time_Sleep() has no implementation for this platform."
#endif	
}

#endif
