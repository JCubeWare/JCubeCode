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

#include "Parsing.h"

/*##====[ HELPER FUNCTIONS ]====##*/

local Outcome Parser_AllocateNewArgument
(
	Parser pointer Instance
)
{
	if (Instance->Count is 0)
	{
		Instance->List = Memory_New(ParserArgument);
		if (no Instance->List)
			return Outcome_ERROR_MEMORY_ALLOCATION;
	}
	else
	{
		Generic pointer Reallocate = NULL;
		Reallocate = Memory_Reallocate(
			Instance->List, 
			sizeof(ParserArgument) * (Instance->Count + 1)
		);
		if (no Reallocate)
			return Outcome_ERROR_MEMORY_ALLOCATION;
		Instance->List = Reallocate;
	}
	
	return Outcome_OK;
}

local Boolean Parser_VerifySemanticArguments
(
	Integer ArgumentCount,
	ParserPolicy Policy[],
	WholeInteger PolicySize
)
{
	Integer RequiredArgumentAmount = 0;
	WholeInteger PolicyIndex;

	for (PolicyIndex = 0; PolicyIndex < PolicySize; PolicyIndex++)
	{
		if (Policy[PolicyIndex].Importance is Parser_REQUIRED)
		{
			if (Policy[PolicyIndex].Type is Parser_NONE)
				RequiredArgumentAmount++;
			else
				RequiredArgumentAmount += 2;
		}
	}

	return not ((ArgumentCount - 1) < RequiredArgumentAmount);
}

local WholeInteger Parser_GetPolicyLength
(
	ParserPolicy Policy[]
)
{
	WholeInteger Index = 0;

	while (Policy[Index].Prefix)
		Index++;
	return Index;
}

local Outcome Parser_Run
(
	Parser pointer Instance,
	Arguments Arguments,
	ParserPolicy Policy[]
)
{
	Boolean IsFound;
	WholeInteger ArgumentIndex;
	WholeInteger Index;
	WholeInteger PolicyIndex;
	WholeInteger PolicySize = Parser_GetPolicyLength(Policy);

	if (PolicySize is 0)
		return Outcome_ERROR_EMPTY_POLICY;

	Parser_Free(Instance);

	if (not Parser_VerifySemanticArguments(Arguments.Count, Policy, PolicySize))
		return Outcome_ERROR_BAD_ARGUMENT;

	for (PolicyIndex = 0; PolicyIndex < PolicySize; PolicyIndex++)
	{
		IsFound = false;

		for (ArgumentIndex = 1; ArgumentIndex < Arguments.Count; ArgumentIndex++)
		{
			if (CString_Matches(Policy[PolicyIndex].Prefix, Arguments.Entry[ArgumentIndex]))
			{
				if ((ArgumentIndex + 1) > (Arguments.Count - 1) 
					and Policy[PolicyIndex].Type isnt Parser_NONE
				)
					break;

				if (Parser_OptionExists(Instance, Policy[PolicyIndex].Prefix))
					break;

				IsFound = true;

				if (Parser_AllocateNewArgument(Instance))
					return Outcome_ERROR_MEMORY_ALLOCATION;

				Index = Instance->Count;

				Instance->List[Index].Name = CString_Set(Policy[PolicyIndex].Name);
				if (no Instance->List[Index].Name)
					return Outcome_ERROR_MEMORY_ALLOCATION;

				Instance->List[Index].Prefix = CString_Set(Arguments.Entry[ArgumentIndex]);
				if (no Instance->List[Index].Prefix)
					return Outcome_ERROR_MEMORY_ALLOCATION;
	
				Instance->List[Index].Type = Policy[PolicyIndex].Type;
				switch (Instance->List[Index].Type)
				{
					case Parser_NUMBER:
						Instance->List[Index].Value.Numeric = atof(
							Arguments.Entry[++ArgumentIndex]
						);
						break;
					case Parser_STRING:
						Instance->List[Index].Value.Text = CString_Set(
							Arguments.Entry[++ArgumentIndex]
						);
						if (no Instance->List[Index].Value.Text)
							return Outcome_ERROR_MEMORY_ALLOCATION;
						break;
					case Parser_NONE:
					case ParserValueType_COUNT_:
						break;
					break;
				}

				Index++;
				Instance->Count = Index;
				break;
			}
		}

		if (not IsFound and Policy[PolicyIndex].Importance is Parser_REQUIRED)
		{
			Parser_Free(Instance);
			return Outcome_ERROR_REQUIRED_MISSING;
		}
	}

	Instance->IsParsed = true;
	return Outcome_OK;
}

/*##====[ FUNCTIONS ]====##*/

Void Parser_Free
(
	Parser pointer Instance
)
{
	WholeInteger Index;

	if (not Instance->IsParsed or Instance->Count is 0)
		return;

	for (Index = 0; Index < Instance->Count; Index++)
	{
		if (Instance->List[Index].Name)
			Memory_Free(Instance->List[Index].Name);
		if (Instance->List[Index].Prefix)
			Memory_Free(Instance->List[Index].Prefix);
		if (Instance->List[Index].Type is Parser_STRING)
			Memory_Free(Instance->List[Index].Value.Text);
	}

	Memory_Free(Instance->List);

	Instance->List = NULL;
	Instance->IsParsed = false;
	Instance->Count = 0;
}

Boolean Parser_OptionExists
(
	Parser pointer Instance,
	CString Prefix
)
{
	WholeInteger Index;

	if (not Instance->IsParsed)
		return false;

	for (Index = 0; Index < Instance->Count; Index++)
	{
		if (CString_Matches(Instance->List[Index].Prefix, Prefix))
			return true;
	}

	return false;
}

Outcome Parser_HandleArguments
(
	Parser pointer Instance, 
	Arguments Arguments,
	ParserPolicy Policy[]
)
{
	return Parser_Run(Instance, Arguments, Policy);
}

Outcome Parser_HandleString
(
	Parser pointer Instance, 
	String Source, 
	String Delimiter, 
	ParserPolicy Policy[]
)
{
	Outcome Result;
	Arguments Arguments;

	Outcome_Handle(
		Result,
		Arguments_ConvertCString(address Arguments, Source.Contents, Delimiter.Contents),
		NoAction
	)

	Result = Parser_Run(Instance, Arguments, Policy);
	Arguments_Free(address Arguments);
	return Result;
}

CString Parser_GetOptionString
(
	Parser pointer Instance, 
	CString Prefix
)
{
	WholeInteger Index;

	if (no Instance->IsParsed)
		return NULL;

	for (Index = 0; Index < Instance->Count; Index++)
	{
		if (Instance->List[Index].Type isnt Parser_STRING)
			continue;
		if (CString_Matches(Instance->List[Index].Prefix, Prefix))
			return Instance->List[Index].Value.Text;
	}

	return NULL;
}

Double Parser_GetOptionNumber
(
	Parser pointer Instance, 
	CString Prefix
)
{
	WholeInteger Index;

	if (no Instance->IsParsed)
		return 0.0;

	for (Index = 0; Index < Instance->Count; Index++)
	{
		if (Instance->List[Index].Type isnt Parser_NUMBER)
			continue;
		if (CString_Matches(Instance->List[Index].Prefix, Prefix))
			return Instance->List[Index].Value.Numeric;
	}

	return 0.0;
}
