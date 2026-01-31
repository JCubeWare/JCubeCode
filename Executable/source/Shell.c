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

#include "Options.h"

/*##====[ DEFINES ]====##*/

#define JCUBECODE_SHELL_BUFFER 1024
#define JCUBECODE_SHELL_PROMPT "[ [J][C]ube[C]ode ]"

/*##====[ FUNCTIONS ]====##*/

Outcome __shell
(
	Arguments Data
)
{
	Outcome Result = Outcome_OK;
	Character ShellBuffer[JCUBECODE_SHELL_BUFFER] = {0};
	Arguments Parsed;
	Arguments ExtraData;

	ignore Data;

	while (true)
	{
		Parsed = Arguments_New(0, 0, 0);
		ExtraData = Arguments_New(0, 0, 0);

		Memory_Set(ShellBuffer, 0, JCUBECODE_SHELL_BUFFER);
		PrintFormatted(JCUBECODE_SHELL_PROMPT " >> ");
		ScanCString(ShellBuffer, JCUBECODE_SHELL_BUFFER);
		ShellBuffer[CString_Length(ShellBuffer) - 1] = '\0';

		if (ShellBuffer[0] is '\0')
			continue;

		Arguments_ConvertCString(address Parsed, ShellBuffer, " ");
		ExtraData = Arguments_New(Parsed.Count - 1, Parsed.Entry + 1, 0);

		if (CString_Matches(Parsed.Entry[0], "exit"))
			break;
		if (CString_Matches(Parsed.Entry[0], "help"))
		{
			HelpMenu(MainOptions);
			continue;
		}
		if (CString_Matches(Parsed.Entry[0], "select"))
		{
			PrintFormatted("Menu selected. TODO\n");
			continue;
		}

		Result = CallOption(Parsed.Entry[0], ExtraData, MainOptions);
		if (Result)
			PrintFormatted(
				JCUBECODE_SHELL_PROMPT " <( Error %d: %s )\n",
				Result,
				Outcome_Descriptions[Result]
			);
	}

	return Outcome_OK;
}