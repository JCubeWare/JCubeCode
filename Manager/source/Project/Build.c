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

local Outcome HandleTarget
(
	Generic pointer Data,
	WholeInteger Index
)
{
	CString ArgumentsVector[JCUBECODE_MAX_ARGUMENTS]; 
	Size Iterator = 0;
	Size Position = 0;
	DataValue pointer ArrayEntry = Data;
	DataValue pointer CurrentData = nullpointer;
	MemoryHandler pointer ArrayMember = nullpointer;
	CString Artifact = nullpointer;
	CString Type = nullpointer;
	CString Compiler = nullpointer;
	Dynamic Options = Dynamic_New(nullpointer);
	Dynamic Sources = Dynamic_New(nullpointer);
	Dynamic Dependencies = Dynamic_New(nullpointer);

	if (ArrayEntry->Type isnt DataType_Object)
		return Outcome_FAIL;

	Logger_Print(Print, LogLevel_DEBUG, "Target [%u]", Index + 1);

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "artifact");
	if (CurrentData->Type is DataType_String)
		Artifact = CurrentData->GetAs.String;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "compiler");
	if (CurrentData->Type is DataType_String)
		Compiler = CurrentData->GetAs.String;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "type");
	if (CurrentData->Type is DataType_String)
		Type = CurrentData->GetAs.String;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "options");
	if (CurrentData->Type is DataType_Array)
		Options = CurrentData->GetAs.Array;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "sources");
	if (CurrentData->Type is DataType_Array)
		Sources = CurrentData->GetAs.Array;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "dependencies");
	if (CurrentData->Type is DataType_Array)
		Dependencies = CurrentData->GetAs.Array;

	PrintFormatted("##====[ TARGET %u ]====##\n", Index + 1);
	PrintFormatted("[] Compiler: %s\n", Compiler);
	PrintFormatted("[] Artifact: %s\n", Artifact);
	PrintFormatted("[] Type: %s\n", Type);

	ArgumentsVector[Position++] = Compiler;
	ArgumentsVector[Position++] = "-o";
	ArgumentsVector[Position++] = CString_SetFormatted(JCUBECODE_BUILD_DIR "/%s", Artifact);

	if (CString_Matches(Type, "executable"))
	{

	}
	if (CString_Matches(Type, "library"))
	{
		ArgumentsVector[Position++] = "-fPIC";
		ArgumentsVector[Position++] = "-shared";
	}

	PrintFormatted("[] Options:\n");
	for (Iterator = 0; Iterator < Options.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Options, Iterator);
		CurrentData = ArrayMember->Data;
		if (CurrentData->Type is DataType_String)
		{
			PrintFormatted(" - %s\n", CurrentData->GetAs.String);
			ArgumentsVector[Position++] = CurrentData->GetAs.String;
		}	
	}

	PrintFormatted("[] Depencies:\n");
	for (Iterator = 0; Iterator < Dependencies.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Dependencies, Iterator);
		CurrentData = ArrayMember->Data;
		if (CurrentData->Type is DataType_String)
		{
			PrintFormatted(" - %s\n", CurrentData->GetAs.String);
			ArgumentsVector[Position++] = CString_SetFormatted("-l%s", CurrentData->GetAs.String);
		}
	}

	PrintFormatted("[] Sources:\n");
	for (Iterator = 0; Iterator < Sources.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Sources, Iterator);
		CurrentData = ArrayMember->Data;
		if (CurrentData->Type is DataType_String)
		{
			PrintFormatted(" - %s\n", CurrentData->GetAs.String);
			ArgumentsVector[Position++] = CurrentData->GetAs.String;
		}
	}

	ArgumentsVector[Position++] = nullpointer;
	return execvp("JCubeCompile", ArgumentsVector);
}

/*##====[ FUNCTIONS ]====##*/

Outcome _project_build
(
	Arguments Arguments
)
{
	Data Test;
	DataValue pointer Targets = nullpointer;
	FileStream pointer Settings = nullpointer;

	ignore Arguments;

	Storage_CreateDirectory(JCUBECODE_BUILD_DIR);
	Storage_CreateDirectory(JCUBECODE_OBJECTS_DIR);

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

	if (Dynamic_ForEach(address Targets->GetAs.Array, HandleTarget))
	{
		Logger_Print(Print, LogLevel_ERROR, "Weird data in 'targets'");
		return Outcome_FAIL;
	}

	return Outcome_OK;
}
