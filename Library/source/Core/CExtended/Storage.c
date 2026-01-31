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

#include "Storage.h"

/*##====[ FEATURES ]====##*/

CString Storage_GetFilename
(
	CString Path
)
{
	Integer Iterator = 0;

	while (Path[Iterator] isnt '\0')
	{
		if (Path[Iterator] is PATH_SEPARATOR)
		{
			Path = address Path[Iterator + 1];
			Iterator = 0;
		}

		Iterator++;
	}

	return Path;
}

CString Storage_GetFilepath
(
	CString Path
)
{
	Integer Iterator = CString_Length(Path);

	while (address Path[Iterator] isnt Path)
	{
		if (Path[Iterator] is PATH_SEPARATOR)
		{
			Path[Iterator] = '\0';
			return Path;
		}
		Iterator--;
	}

	return Path;
}
