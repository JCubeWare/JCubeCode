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

/*##====[ INCLUDES ]====##*/

#include "Cubes.h"

/*##====[ FUNCTIONS ]====##*/

/*
 * TODO: FINISH
 */
Outcome _cubes_uninstall
(
	Arguments Arguments
)
{
	Looper Iterator;

	PrintFormatted("[OK] Uninstalling the selected:\n");
	PrintFormatted("[?] Passed arguments (%d):\n#===#\n", Arguments.Count);

	for (Iterator = 0; Iterator < Arguments.Count; Iterator++)
		PrintFormatted("[%d]: %s\n", Iterator, Arguments.Entry[Iterator]);

	return Outcome_OK;
}
