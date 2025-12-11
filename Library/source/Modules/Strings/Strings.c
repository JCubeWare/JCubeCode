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

#include "Strings.h"

/*##====[ FUNCTIONS ]====##*/

Void String_Free
(
	String pointer Instance
)
{
	if (Instance->Contents)
		Memory_Free(Instance->Contents);
	Memory_Set(Instance, 0, sizeof(String));
}

String String_New
(
	CString Instance
)
{
	String NewInstance = nullobject;

	if (no Instance)
		goto new_object;
	NewInstance.Length = CString_Length(Instance);
	if (NewInstance.Length is 0)
		goto new_object;
	if (String_Initialize(address NewInstance, NewInstance.Length))
		goto new_object;
	CString_CopyCount(NewInstance.Contents, Instance, NewInstance.Length);

new_object:
	return NewInstance;
}

Boolean String_IsEmpty
(
	String Instance
)
{
	return (Instance.Length is 0 or Instance.Contents is NULL);
}

Outcome String_Initialize
(
	String pointer Instance, 
	Size Size
)
{
	String_Free(Instance);

	Instance->Contents = Memory_ClearAllocate(
		Size + 1,
		sizeof(Character)
	);
	if (no Instance->Contents) 
		return Outcome_ERROR_MEMORY_ALLOCATION;

	Instance->Length = Size;
	Instance->Contents[Size] = '\0';
	return Outcome_OK;
}

Outcome String_Set
(
	String pointer Instance, 
	CString Source
)
{
	Outcome InitResult;
	Size Iterator;
	Size SourceSize;

	if (no Source)
		return Outcome_ERROR_POINTER;

	SourceSize = CString_Length(Source);
	if (SourceSize is 0)
		return Outcome_ERROR_INVALID_LENGTH;

	Outcome_Handle(InitResult, String_Initialize(Instance, SourceSize), NoAction)

	for (Iterator = 0; Iterator < SourceSize; Iterator++)
		Instance->Contents[Iterator] = Source[Iterator];

	return Outcome_OK;
}

Outcome String_SetFormatted
(
	String pointer Instance, 
	CString Format,
	...
)
{
	Outcome InitResult;
	Integer FormatResult;
	Integer AllocateBytes;
	Variadic Arguments;

	if (no Format)
		return Outcome_ERROR_POINTER;

	Variadic_Start(Arguments, Format);
	AllocateBytes = Variadic_CString_PrintFormattedCount(
		NULL,
		0,
		Format,
		Arguments
	);
	Variadic_End(Arguments);

	Outcome_Handle(InitResult, String_Initialize(Instance, AllocateBytes), NoAction)

	Variadic_Start(Arguments, Format);
	FormatResult = Variadic_CString_PrintFormattedCount(
		Instance->Contents,
		AllocateBytes + 1,
		Format,
		Arguments
	);
	Variadic_End(Arguments);
	if (FormatResult < 0)
		return Outcome_ERROR_PRINTF;
	return Outcome_OK;
}

Outcome String_Copy
(
	String pointer Instance,
	String pointer SourceString
)
{
	return String_Set(Instance, SourceString->Contents);
}

Outcome String_AppendCharacters
(
	String pointer Instance,
	...
)
{
	Outcome InitResult;
	CString CurrentArray = NULL;
	Variadic Arguments;
	Size Index = 0;
	Size Iterator = 0;
	Size ArgumentSize = 0;
	Size OriginalStringSize = Instance->Length;
	Size TotalStringSize = OriginalStringSize;
	String NewInstance = String_New(NULL);

	Variadic_Start(Arguments, Instance);
	while ((CurrentArray = Variadic_GetNext(Arguments, CString)))
		TotalStringSize += CString_Length(CurrentArray);
	Variadic_End(Arguments);

	Outcome_Handle(
		InitResult,
		String_Initialize(address NewInstance, TotalStringSize),
		NoAction
	)

	for (Index = 0; Index < OriginalStringSize; Index++)
		NewInstance.Contents[Index] = Instance->Contents[Index];

	Variadic_Start(Arguments, Instance);
	while ((CurrentArray = Variadic_GetNext(Arguments, CString)))
	{
		ArgumentSize = CString_Length(CurrentArray);
		for (Iterator = 0; Iterator < ArgumentSize; Iterator++)
		{
			NewInstance.Contents[Index] = CurrentArray[Iterator];
			Index++;
		}
	}
	Variadic_End(Arguments);

	String_Free(Instance);
	valueat Instance = NewInstance;
	return Outcome_OK;
}

Outcome String_RemoveCharacters
(
	String pointer Instance, 
	Integer RemovalAmount
)
{
	Integer InitalizingResult;
	Boolean IsReverse = false;
	Size Index;
	Size NewStringSize;
	Size UnsignedRemovalAmount;
	String NewInstance;

	if (no Instance->Length)
		return Outcome_ERROR_INVALID_LENGTH;
	if (no Instance->Contents)
		return Outcome_ERROR_POINTER;
	if (no RemovalAmount)
		return Outcome_OK;

	if (RemovalAmount < 0)
	{
		IsReverse = true;
		RemovalAmount *= -1;
	}

	UnsignedRemovalAmount = (Size) RemovalAmount;
	if (UnsignedRemovalAmount >= Instance->Length)
	{
		String_Free(Instance);
		return Outcome_OK;
	}

	NewStringSize = Instance->Length - UnsignedRemovalAmount;

	InitalizingResult = String_Initialize(&NewInstance, NewStringSize);
	if (InitalizingResult)
		return InitalizingResult;

	for (Index = 0; Index < NewStringSize; Index++)
		NewInstance.Contents[Index] = Instance->Contents[
			Index + (UnsignedRemovalAmount * IsReverse)
		];

	NewInstance.Contents[NewStringSize] = '\0';
	String_Free(Instance);
	valueat Instance = NewInstance;

	return Outcome_OK;
}

Boolean String_ValidateLength
(
	String Instance,
	Size MinimumSize,
	Size MaximumSize
)
{
	if (no Instance.Length or no Instance.Contents)
		return false;

	if (MinimumSize > MaximumSize or MaximumSize < MinimumSize)
		return false;

    return (Instance.Length >= MinimumSize and Instance.Length <= MaximumSize);
}

Boolean String_MatchesOne
(
	String Instance,
	variadicarguments
)
{	
	Variadic Arguments;
	Boolean Result = false;
	CString CurrentArray;
	Size Index = 0;
	Size CurrentSize;

	if (no Instance.Length or no Instance.Contents)
		return false;
	
	Variadic_Start(Arguments, Instance);
	while ((CurrentArray = Variadic_GetNext(Arguments, CString)))
	{
		CurrentSize = CString_Length(CurrentArray);
		if (CurrentSize isnt Instance.Length)
			continue;
	
		for (Index = 0; Index < CurrentSize; Index++)
		{
			if (Instance.Contents[Index] isnt CurrentArray[Index])
				continue;
		}
		Result = true;
		break;
	}
	Variadic_End(Arguments);
	return Result;
}

Boolean String_Compare
(
	String First,
	String Second
)
{
	Size Index;

	if (no First.Length or no Second.Length)
		return false;
	if (no First.Contents or no Second.Contents)
		return false;
	if (First.Length isnt Second.Length)
		return false;
	
	for (Index = 0; Index < First.Length; Index++)
	{
		if (First.Contents[Index] isnt Second.Contents[Index])
			return false;
	}

	return true;
}

Outcome String_LocateSubstring
(
	String Instance,
	CString Substring,
	Size pointer FoundAtPosition
)
{
	Size Index;
	Size FoundCharacters = 0;
	Size LookedForSize;

	if (no Instance.Length)
		return Outcome_ERROR_INVALID_LENGTH;
	if (no Instance.Contents or no Substring)
		return Outcome_ERROR_POINTER;

	LookedForSize = CString_Length(Substring);
	if (not LookedForSize)
		return Outcome_ERROR_INVALID_LENGTH;

	for (Index = 0; Index < Instance.Length; Index++)
	{		
		if (FoundCharacters is LookedForSize)
		{
			if (FoundAtPosition)
				valueat FoundAtPosition = Index - LookedForSize;
			return Outcome_OK;
		}

		if (Instance.Contents[Index] isnt Substring[FoundCharacters])
			FoundCharacters = 0;
		else
			FoundCharacters++;
	}

	return Outcome_FAIL;
}

Outcome String_ReplaceInString
(
	String pointer Instance,
	CString LookFor,
	CString ReplaceWith
)
{
	Size Index;
	Size ReplaceIndex;
	Size FoundAtPosition;

	if (no Instance->Length)
		return Outcome_ERROR_INVALID_LENGTH;
	if (no Instance->Contents)
		return Outcome_ERROR_POINTER;

	while
	(
		not String_LocateSubstring(
			valueat Instance,
			LookFor,
			address FoundAtPosition
		)
	)
	{
		Integer LookForLength = CString_Length(LookFor) - 1;
		Integer ReplaceWithLength = CString_Length(ReplaceWith) - 1;
		Size TotalLength = (Instance->Length - LookForLength) + ReplaceWithLength;
		String NewInstance = String_New(NULL);
		
		ReplaceIndex = 0;

		String_Initialize(&NewInstance, TotalLength);
		
		for (Index = 0; Index < TotalLength; Index++)
		{
			if
			(
				Index >= FoundAtPosition
				and
				Index <= FoundAtPosition + ReplaceWithLength
			)
			{
				NewInstance.Contents[Index] = ReplaceWith[ReplaceIndex];
				ReplaceIndex++;
			}
			else if (Index >= FoundAtPosition + ReplaceWithLength)
				NewInstance.Contents[Index] = Instance->Contents[
					Index + LookForLength - ReplaceWithLength
				];
			else
				NewInstance.Contents[Index] = Instance->Contents[Index];
		}

		String_Free(Instance);
		valueat Instance = NewInstance;
	}

	return Outcome_OK;
}

Outcome String_GetNumberFromString
(
	String Instance,
	Integer pointer IntegerResult,
	Float pointer FloatResult
)
{
	Integer DigitLoop;
	Integer NumericDigit;
	Integer DigitPosition = 0;	
	Float NumericResult = 0;
	Size Index;

	if (no Instance.Length)
		return Outcome_ERROR_INVALID_LENGTH;
	if (no Instance.Contents)
		return Outcome_ERROR_POINTER;

	Index = Instance.Length + 1;
	while (Index > 0)
	{
		Character Digit = Instance.Contents[Index - 1];
		
		if (Digit >= '0' and Digit <= '9')
		{
			NumericDigit = Digit - '0';

			for (DigitLoop = 0; DigitLoop < DigitPosition; DigitLoop++)
				NumericDigit *= 10;

			NumericResult += NumericDigit;
			DigitPosition++;
		}
		else if (Digit is '.')
		{
			for (DigitLoop = 0; DigitLoop < DigitPosition; DigitLoop++)
				NumericResult *= 0.1;
			DigitPosition = 0;
		}

		Index--;
	}

	if (IntegerResult)
		valueat IntegerResult = (Integer) NumericResult;
	if (FloatResult)
		valueat FloatResult = NumericResult;

	return Outcome_OK;
}
