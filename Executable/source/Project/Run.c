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

/*##====[ HELPER FUNCTIONS ]====##*/

local Outcome RunArtifact
(
	Generic pointer Data,
	WholeInteger Index
)
{
	CString TargetName = ((DictionaryEntry pointer) Data)->Key;
	DataValue pointer ArrayEntry = ((DictionaryEntry pointer) Data)->Value.Data;
	DataValue pointer CurrentData = nullpointer;
	String SystemCallBuffer = String_New(nullpointer);
	CString Artifact = nullpointer;
	CString Type = nullpointer;

	if (ArrayEntry->Type isnt DataType_Object)
		return Outcome_FAIL;

	Logger_Print(Print, LogLevel_DEBUG, "Executing Target [%u]:\n", Index + 1);

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "artifact");
	if (CurrentData->Type is DataType_String)
		Artifact = CurrentData->GetAs.String;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "type");
	if (CurrentData->Type is DataType_String)
		Type = CurrentData->GetAs.String;

	if (no CString_Matches(Type, "executable"))
	{
		Logger_Print(Print, LogLevel_WARN, "Target [%u] not executable. Skipping.", Index + 1);
		return Outcome_FAIL;
	}

	String_SetFormatted(
		address SystemCallBuffer,
		"%s/%s",
		JCUBECODE_BUILD_DIR,
		Artifact
	);

	return Program_SystemExecute(SystemCallBuffer.Contents);
}

/*##====[ FUNCTIONS ]====##*/

Outcome _project_run
(
	Arguments Arguments
)
{
	DataValue pointer Targets = Project_GetTargets();
	WholeInteger Iterator;
	WholeInteger ArgIterator;
	Short TargetsRan = 0;
	Boolean IsFound = false;

	for (ArgIterator = 0; ArgIterator < Arguments.Count; ArgIterator++)
	{
		IsFound = false;
		for (Iterator = 0; Iterator < Targets->GetAs.Object.Contents.Count; Iterator++)
		{
			if (CString_Matches(Arguments.Entry[ArgIterator], ((DictionaryEntry pointer) Targets->GetAs.Object.Contents.Entries[Iterator].Data)->Key))
			{
				RunArtifact(Targets->GetAs.Object.Contents.Entries[Iterator].Data, Iterator);
				TargetsRan++;
				IsFound = true;
			}
		}

		if (not IsFound)
			Logger_Print(Print, LogLevel_ERROR, "Target '%s' not found in project.", Arguments.Entry[ArgIterator]);
	}

	return Outcome_OK;
}