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

/*##====[ DESCRIPTION ]====##*/
/*
 * Holds the descriptions and will hold the Outcome functions later.
 */

/*##====[ INCLUDES ]====##*/

#include "Outcome.h"

/*##====[ DESCRIPTIONS ]====##*/

/*
 * Stringified descriptions of the number each Outcome represents.
 * Use the outcome as an array index to get it.
 */
CString Outcome_Descriptions[] = {
	OUTCOME_LIST(OUTCOME_STRUCT)
	"Yes, this is the amount of outcomes!"
};
