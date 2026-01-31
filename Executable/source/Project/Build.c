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

local Outcome HandleTarget
(
	Generic pointer Data,
	WholeInteger Index
)
{
	CString TargetName = ((DictionaryEntry pointer) Data)->Key;
	DataValue pointer ArrayEntry = ((DictionaryEntry pointer) Data)->Value.Data;
	CString ArgumentsVector[JCUBECODE_MAX_ARGUMENTS];
	CString ObjectArgs[JCUBECODE_MAX_ARGUMENTS];
	Looper Iterator = 0;
	Looper Position = 0;
	Size ObjectPosition = 0;
	DataValue pointer CurrentData = nullpointer;
	MemoryHandler pointer ArrayMember = nullpointer;
	CString NewDirectory = nullpointer;
	CString CurrentCString;
	Size SourceIndex = 0;
	Size ObjectIndex = 0;

	ProjectTarget Target = nullobject;

	if (ArrayEntry->Type isnt DataType_Object)
		return PrintFormatted("DataType: %d", ArrayEntry->Type);

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "artifact");
	if (CurrentData->Type is DataType_String)
		Target.Artifact = CurrentData->GetAs.String;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "compiler");
	if (CurrentData->Type is DataType_String)
		Target.Compiler = CurrentData->GetAs.String;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "type");
	if (CurrentData->Type is DataType_String)
		Target.Type = CurrentData->GetAs.String;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "options");
	if (CurrentData->Type is DataType_Array)
		Target.Options = CurrentData->GetAs.Array;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "sources");
	if (CurrentData->Type is DataType_Array)
		Target.Sources = CurrentData->GetAs.Array;

	CurrentData = Dictionary_Get(address ArrayEntry->GetAs.Object, "dependencies");
	if (CurrentData->Type is DataType_Array)
		Target.Dependencies = CurrentData->GetAs.Array;

	PrintFormatted("##====[ TARGET %u: %s ]====##\n", Index + 1, TargetName);
	PrintFormatted("[] Compiler: %s\n", Target.Compiler);
	PrintFormatted("[] Artifact: %s\n", Target.Artifact);
	PrintFormatted("[] Type: %s\n", Target.Type);

	/*
	 * Individual objects:
	 */
	ObjectArgs[ObjectPosition++] = Target.Compiler;
	ObjectArgs[ObjectPosition++] = "-c";
	SourceIndex = ObjectPosition;
	ObjectArgs[ObjectPosition++] = nullpointer;
	ObjectArgs[ObjectPosition++] = "-o";
	ObjectIndex = ObjectPosition;
	ObjectArgs[ObjectPosition++] = nullpointer;

	PrintFormatted("[] Options:\n");
	for (Iterator = 0; Iterator < Target.Options.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Target.Options, Iterator);
		CurrentData = ArrayMember->Data;
		if (CurrentData->Type is DataType_String)
		{
			PrintFormatted(" - %s\n", CurrentData->GetAs.String);
			ObjectArgs[ObjectPosition++] = CurrentData->GetAs.String;
		}	
	}

	PrintFormatted("[] Depencies:\n");
	for (Iterator = 0; Iterator < Target.Dependencies.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Target.Dependencies, Iterator);
		CurrentData = ArrayMember->Data;
		if (CurrentData->Type is DataType_String)
		{
			PrintFormatted(" - %s\n", CurrentData->GetAs.String);
			ObjectArgs[ObjectPosition++] = CString_SetFormatted("-l%s", CurrentData->GetAs.String);
		}
	}
	ObjectArgs[ObjectPosition++] = CString_SetFormatted("-l" JCUBECODE_VERSION_FULL);
	ObjectArgs[ObjectPosition++] = nullpointer;

	PrintFormatted("[] Sources:\n");
	for (Iterator = 0; Iterator < Target.Sources.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Target.Sources, Iterator);
		CurrentData = ArrayMember->Data;
		if (CurrentData->Type is DataType_String)
		{
			PrintFormatted(" - %s\n", CurrentData->GetAs.String);
			ObjectArgs[SourceIndex] = CurrentData->GetAs.String;
			ObjectArgs[ObjectIndex] = CString_SetFormatted(JCUBECODE_OBJECTS_DIR "/%s", CurrentData->GetAs.String);
			ObjectArgs[ObjectIndex][CString_Length(ObjectArgs[ObjectIndex])-1] = 'o';

			Dynamic_Add(address Target.Objects, CString_Set(ObjectArgs[ObjectIndex]), true);

			NewDirectory = CString_SetFormatted(
				JCUBECODE_OBJECTS_DIR "/%s",
				Storage_GetFilepath(
					CString_Set(CurrentData->GetAs.String)
				)
			);
			Storage_CreateDirectory(NewDirectory);

			pid_t pid = fork();
			if (no pid) {
				execvp(Target.Compiler, ObjectArgs);
				perror("execvp"); 
				_exit(127);
			}
			if (pid < 0) {
				perror("fork");
				exit(1);
			}
			while ((wait(nullpointer)) > 0);
		}
	}

	ArgumentsVector[Position++] = Target.Compiler;
	ArgumentsVector[Position++] = "-o";
	ArgumentsVector[Position++] = CString_SetFormatted(JCUBECODE_BUILD_DIR "/%s", Target.Artifact);

	if (CString_Matches(Target.Type, "library"))
	{
		ArgumentsVector[Position++] = "-fPIC";
		ArgumentsVector[Position++] = "-shared";
	}

	for (Iterator = 0; Iterator < Target.Options.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Target.Options, Iterator);
		CurrentData = ArrayMember->Data;
		if (CurrentData->Type is DataType_String)
			ArgumentsVector[Position++] = CurrentData->GetAs.String;
	}

	PrintFormatted("[] Objects:\n");
	for (Iterator = 0; Iterator < Target.Objects.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Target.Objects, Iterator);
		CurrentCString = ArrayMember->Data;

		if (CurrentCString)
		{
			PrintFormatted(" - %s\n", CurrentCString);
			ArgumentsVector[Position++] = CurrentCString;	
		}
	}

	PrintFormatted("[] Depencies:\n");
	for (Iterator = 0; Iterator < Target.Dependencies.Count; Iterator++)
	{
		ArrayMember = Dynamic_Get(address Target.Dependencies, Iterator);
		CurrentData = ArrayMember->Data;

		if (CurrentData->Type is DataType_String)
		{
			PrintFormatted(" - %s\n", CurrentData->GetAs.String);
			ArgumentsVector[Position++] = CString_SetFormatted("-l%s", CurrentData->GetAs.String);
		}
	}

	ArgumentsVector[Position++] = CString_SetFormatted("-l" JCUBECODE_VERSION_FULL);
	ArgumentsVector[Position++] = nullpointer;

	pid_t pid = fork();
	if (no pid) {
		execvp(Target.Compiler, ArgumentsVector);
		perror("execvp");
		_exit(0);
	}
	if (pid < 0) {
		perror("fork");
		exit(1);
	}
	while ((wait(nullpointer)) > 0);
	return Outcome_OK;
}

local Void ListAllTargets
(
	DataValue pointer Targets
)
{
	Looper Iterator;

	Logger_Print(Print, LogLevel_WARN, "Select a target or 'all'. Available targets:");
	for (Iterator = 0; Iterator < Targets->GetAs.Object.Contents.Count; Iterator++)
	{
		Logger_Print(Print, LogLevel_DEBUG, " - %s", 
			((DictionaryEntry pointer) Targets->GetAs.Object.Contents.Entries[Iterator].Data)->Key);
	}
}

/*##====[ FUNCTIONS ]====##*/

Outcome _project_build
(
	Arguments Arguments
)
{
	DataValue pointer Targets = Project_GetTargets();
	WholeInteger Iterator;
	WholeInteger ArgIterator;
	Short TargetsRan = 0;
	Boolean IsFound = false;

	Storage_CreateDirectory(JCUBECODE_BUILD_DIR);
	Storage_CreateDirectory(JCUBECODE_OBJECTS_DIR);

	if (Arguments.Count is 0)
	{
		if (Targets->GetAs.Object.Contents.Count is 1)
		{
			HandleTarget(Targets->GetAs.Object.Contents.Entries[0].Data, 0);
			Logger_Print(Print, LogLevel_NORMAL, "Build complete.");
		}
		else
			ListAllTargets(Targets);
		return Outcome_OK;
	}

	if (Arguments.Count is 1 and CString_Matches(Arguments.Entry[0], JCUBECODE_BUILD_ALL))
	{
		Logger_Print(Print, LogLevel_NORMAL, "Building all targets.");

		for (Iterator = 0; Iterator < Targets->GetAs.Object.Contents.Count; Iterator++)
		{
			HandleTarget(Targets->GetAs.Object.Contents.Entries[Iterator].Data, Iterator);
			TargetsRan++;
		}
	}
	else
	{
		for (ArgIterator = 0; ArgIterator < Arguments.Count; ArgIterator++)
		{
			IsFound = false;
			for (Iterator = 0; Iterator < Targets->GetAs.Object.Contents.Count; Iterator++)
			{
				if (CString_Matches(Arguments.Entry[ArgIterator], ((DictionaryEntry pointer) Targets->GetAs.Object.Contents.Entries[Iterator].Data)->Key))
				{
					HandleTarget(Targets->GetAs.Object.Contents.Entries[Iterator].Data, TargetsRan);
					TargetsRan++;
					IsFound = true;
				}
			}

			if (not IsFound)
				Logger_Print(Print, LogLevel_ERROR, "Target '%s' not found in project.", Arguments.Entry[ArgIterator]);
		}
	}

	if (TargetsRan)
	{
		Logger_Print(Print, LogLevel_NORMAL, "Built %d specified targets.", TargetsRan);
	}
	else
	{
		Logger_Print(Print, LogLevel_ERROR, "Specified target not found");
		ListAllTargets(Targets);
		return Outcome_UNKNOWN_OPTION;
	}

	return Outcome_OK;
}
