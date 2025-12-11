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

/*##====[ INCLUDES ]====##*/

#include "../Options.h"

/*##====[ HELPER FUNCTIONS ]====##*/

local Outcome RunArtifact
(
	Generic pointer Data,
	WholeInteger Index
)
{
	DataValue pointer ArrayEntry = Data;
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
	Data Test;
	DataValue pointer Targets = nullpointer;
	FileStream pointer Settings = nullpointer;

	ignore Arguments;

	Test = Data_Load("./Project.jcdata", true);
	Settings = FileStream_Open("./Project.jcdata", "r");
	if (no Settings)
	{
		Logger_Print(Print, LogLevel_WARN, "Project settings not found.");
		return Outcome_FAIL;
	}
	FileStream_Close(Settings);

	Targets = Dictionary_Get(address Test.Entries, "targets");
	if (no Targets)
	{
		Logger_Print(Print, LogLevel_ERROR, "Targets entry not found.");
		return Outcome_FAIL;
	}
	if (Targets->Type isnt DataType_Array)
	{
		Logger_Print(Print, LogLevel_ERROR, "Targets not found in array.");
		return Outcome_FAIL;
	}

	if (Dynamic_ForEach(address Targets->GetAs.Array, RunArtifact))
	{
		Logger_Print(Print, LogLevel_ERROR, "Weird data in 'targets'");
		return Outcome_FAIL;
	}
	return Outcome_OK;
}