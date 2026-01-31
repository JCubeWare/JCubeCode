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

#include "Project.h"

/*##====[ FUNCTIONS ]====##*/

DataValue pointer Project_GetTargets
(
	noarguments
)
{
	Data Test;
	DataValue pointer Targets = nullpointer;

	if (access(JCUBECODE_PROJECT_FILE, F_OK))
	{
		Logger_Print(Print, LogLevel_WARN, "Project settings not found.");
		return nullpointer;
	}

	Test = Data_Load(JCUBECODE_PROJECT_FILE, true);
	Targets = Dictionary_Get(address Test.Entries, "targets");
	if (no Targets)
	{
		Logger_Print(Print, LogLevel_ERROR, "Targets entry not found.");
		return nullpointer;
	}
	if (Targets->Type isnt DataType_Object)
	{
		Logger_Print(Print, LogLevel_ERROR, "Targets are not valid objects.");
		return nullpointer;
	}

	return Targets;
}