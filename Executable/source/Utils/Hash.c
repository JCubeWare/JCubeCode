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

#include "Utils.h"

/*##====[ HELPER FUNCTIONS ]====##*/

Outcome _utils_hash
(
	Arguments Arguments
)
{
	Looper Iterator;

	if (Arguments.Count is 0)
	{
		PrintFormatted("Provide at least one CString to hash.\n");
		return Outcome_FAIL;
	}

	for (Iterator = 0; Iterator < Arguments.Count; Iterator++)
		PrintFormatted("%lu\n", Hash_DJB2(Arguments.Entry[Iterator]));

	return Outcome_OK;
}
