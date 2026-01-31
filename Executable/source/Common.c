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

#include "Common.h"

/*##====[ FUNCTIONS ]====##*/

Boolean DoUserConfirm
(
	CString Text
)
{
	Character YesNo;

	Logger_Print(Print, LogLevel_WARN, Text);
	PrintFormatted("[Yes (Y/y) or No (N/n)] >> ");
	YesNo = ScanCharacter();
	if (not logic(YesNo is 'Y' or YesNo is 'y'))
	{
		Logger_Print(Print, LogLevel_ERROR, "Cancelled by user.");
		return false;
	}

	return true;
}
