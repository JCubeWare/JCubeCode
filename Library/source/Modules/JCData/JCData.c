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

#include "JCData.h"

/*##====[ LOCAL FUNCTIONS ]====##*/

local Void Data_IndentTab
(
	FileStream pointer File,
	Integer Amount
)
{
	Looper Repeater;
	repeat(Repeater, (Looper)Amount)
		FileStream_WriteCharacter('\t', File);
}

local DataValue pointer Data_CreateValue
(
	CString ValueBuffer
)
{
	DataValue pointer NewInstance = Memory_New(DataValue);

	/*
	 * String
	 */
	if (ValueBuffer[0] is '"')
	{
		Size Length = CString_Length(++ValueBuffer);
		ValueBuffer[Length - 1] = '\0';

		NewInstance->Type = DataType_String;
		NewInstance->GetAs.String = ValueBuffer;
	}

	/*
	 * Boolean
	 */
	else if (ValueBuffer[0] is 'F' or ValueBuffer[0] is 'T')
	{
		NewInstance->Type = DataType_Boolean;
		NewInstance->GetAs.Boolean = logic(ValueBuffer[0] is 'T');
	}

	/*
	 * Float
	 */
	else if (CString_FindFirst(ValueBuffer, '.'))
	{
		NewInstance->Type = DataType_Float;
		NewInstance->GetAs.Float = CString_GetAsDouble(ValueBuffer);
	}

	/*
	 * TODO: Finish date and time formats	
	 */

	/*
	 * Integer
	 */
	else
	{
		NewInstance->Type = DataType_Integer;
		NewInstance->GetAs.Integer = CString_GetAsInteger(ValueBuffer);
	}

	return NewInstance;
}

local Outcome Data_DumpValue
(
	CString EntryName,
	DataValue pointer CurrentData,
	FileStream pointer File,
	Boolean DoIndent,
	Size IndentLevel
)
{
	Size Iterator = 0;
	CString KeyFormat = DoIndent ? "%s = " : "%s=";
	DictionaryEntry pointer CurrentEntry = NULL;

	if (DoIndent)
		Data_IndentTab(File, IndentLevel);
	if (EntryName)
		FileStream_PrintFormatted(File, KeyFormat, EntryName);

	switch (CurrentData->Type)
	{
		case DataType_Null:
			break;
		case DataType_Object:
			FileStream_WriteCharacter('{', File);
			if (DoIndent)
				FileStream_WriteCharacter('\n', File);
			for (Iterator = 0; Iterator < CurrentData->GetAs.Object.Contents.Count; Iterator++)
			{
				CurrentEntry = CurrentData->GetAs.Object.Contents.Entries[Iterator].Data;
				Data_DumpValue(
					CurrentEntry->Key,
					CurrentEntry->Value.Data,
					File,
					DoIndent,
					IndentLevel + 1
				);
			}
			if (DoIndent)
				Data_IndentTab(File, IndentLevel);
			FileStream_WriteCharacter('}', File);
			break;
		case DataType_Array:
			FileStream_WriteCharacter('[', File);
			if (DoIndent)
				FileStream_WriteCharacter('\n', File);
			for (Iterator = 0; Iterator < CurrentData->GetAs.Array.Count; Iterator++)
				Data_DumpValue(
					NULL,
					CurrentData->GetAs.Array.Entries[Iterator].Data,
					File,
					DoIndent,
					IndentLevel + 1
				);
			if (DoIndent)
				Data_IndentTab(File, IndentLevel);
			FileStream_WriteCharacter(']', File);
			break;
		case DataType_Boolean:
			FileStream_WriteCharacter(CurrentData->GetAs.Boolean ? 'T' : 'F', File);
			break;
		case DataType_Integer:
			FileStream_PrintFormatted(File, "%d", CurrentData->GetAs.Integer);
			break;
		case DataType_Float:
			FileStream_PrintFormatted(File, "%g", CurrentData->GetAs.Float);
			break;
		case DataType_String:
			FileStream_WriteCharacter('\"', File);
			FileStream_WriteCStringEscaped(File, CurrentData->GetAs.String);
			FileStream_WriteCharacter('\"', File);
			break;
		default:
			break;
	}

	FileStream_WriteCharacter(';', File);
	if (DoIndent)
		FileStream_WriteCharacter('\n', File);
	return Outcome_OK;
}

local CString Data_CreateObject
(
	Dictionary pointer Instance,
	CString ParsedOffset
);

local CString Data_CreateArray
(
	Dynamic pointer Instance,
	CString ParsedOffset
)
{
	DataParsing State = DataParsing_VALUE;
	CString Iterator = ParsedOffset;
	Character ValueBuffer[JCDATA_VALUE_MAXSIZE] = nullobject;
	Integer ValuePosition = 0;
	DataValue pointer NewInstance = NULL;

	while (valueat Iterator isnt '\0')
	{
		if (State is DataParsing_VALUE)
		{
			if (ValuePosition is 0 and valueat Iterator is '#')
			{
				State = DataParsing_COMMENT;
				Iterator++;
				continue;
			}

			switch (valueat Iterator)
			{
				case ']':
					Iterator++;
					goto array_end;
				case '[':
					NewInstance = Data_Array(nullpointer);
					Iterator = Data_CreateArray(
						address NewInstance->GetAs.Array,
						++Iterator
					);
					goto add_datavalue;
				case '{':
					NewInstance = Data_Object(nullpointer);
					Iterator = Data_CreateObject(
						address NewInstance->GetAs.Object,
						++Iterator
					);
					goto add_datavalue;
				case '"':
					State = DataParsing_STRING;
					ValueBuffer[ValuePosition] = valueat Iterator;
					ValuePosition++;
					break;
				case ';':
					NewInstance = Data_CreateValue(CString_Set(ValueBuffer));
					goto add_datavalue;
				default:
					ValueBuffer[ValuePosition] = valueat Iterator;
					ValuePosition++;
					break;
				add_datavalue:
					Dynamic_Add(Instance, NewInstance, true);
					Memory_Clear(ValueBuffer);
					ValuePosition = 0;
			}
		}
		else if (State is DataParsing_STRING)
		{
			if (valueat Iterator is '"')
			{
				State = DataParsing_VALUE;
				ValueBuffer[ValuePosition] = valueat Iterator;
				ValuePosition++;
			}
				
			else if (valueat Iterator is '\\')
			{
				Iterator++;
				ValueBuffer[ValuePosition] = valueat Iterator;
				ValuePosition++;
			}
			else
			{
				ValueBuffer[ValuePosition] = valueat Iterator;
				ValuePosition++;
			}
		}
		else if (State is DataParsing_COMMENT)
		{
			if (valueat Iterator is '\n')
				State = DataParsing_VALUE;
		}

		Iterator++;
	}

array_end:
	return Iterator;
}

local CString Data_CreateObject
(
	Dictionary pointer Instance,
	CString ParsedOffset
)
{
	DataParsing State = DataParsing_KEY;
	CString Iterator = ParsedOffset;
	DataValue pointer NewInstance = NULL;
	Character KeyBuffer[JCDATA_KEY_MAXSIZE] = nullobject;
	Integer KeyPosition = 0;
	Character ValueBuffer[JCDATA_VALUE_MAXSIZE] = nullobject;
	Integer ValuePosition = 0;

	while (valueat Iterator isnt '\0')
	{
		if (valueat Iterator is '}')
		{
			Iterator++;
			goto object_end;
		}

		if (State is DataParsing_KEY)
		{
			switch (valueat Iterator)
			{
				case '#':
					State = DataParsing_COMMENT;
					break;
				case '=':
					State = DataParsing_VALUE;
					break;
				default:
					KeyBuffer[KeyPosition] = valueat Iterator;
					KeyPosition++;
				break;
			}
		}
		else if (State is DataParsing_VALUE)
		{
			switch (valueat Iterator)
			{
				case '[':
					NewInstance = Data_Array(NULL);
					Iterator = Data_CreateArray(
						address NewInstance->GetAs.Array,
						++Iterator
					);
					goto parsing_restart;
				case '{':
					NewInstance = Data_Object(NULL);
					Iterator = Data_CreateObject(
						address NewInstance->GetAs.Object,
						++Iterator
					);
					goto parsing_restart;
				case '"':
					State = DataParsing_STRING;
					ValueBuffer[ValuePosition] = valueat Iterator;
					ValuePosition++;
					break;
				case ';':
					NewInstance = Data_CreateValue(CString_Set(ValueBuffer));
					State = DataParsing_KEY;
					goto parsing_restart;
				default:
					ValueBuffer[ValuePosition] = valueat Iterator;
					ValuePosition++;
					break;
				parsing_restart:
					Dictionary_Set(
						Instance,
						CString_Set(KeyBuffer), 
						NewInstance,
						true
					);
					Memory_Clear(KeyBuffer);
					Memory_Clear(ValueBuffer);
					KeyPosition = 0;
					ValuePosition = 0;
					State = DataParsing_KEY;
			}
		}
		else if (State is DataParsing_STRING)
		{
			if (valueat Iterator is '"')
			{
				State = DataParsing_VALUE;
				ValueBuffer[ValuePosition] = valueat Iterator;
				ValuePosition++;
			}
				
			else if (valueat Iterator is '\\')
			{
				Iterator++;
				ValueBuffer[ValuePosition] = valueat Iterator;
				ValuePosition++;
			}
			else
			{
				ValueBuffer[ValuePosition] = valueat Iterator;
				ValuePosition++;
			}
		}
		else if (State is DataParsing_COMMENT)
		{
			if (valueat Iterator is '\n')
				State = DataParsing_KEY;
		}

		Iterator++;
	}
object_end:
	return Iterator;
}

local DataValue pointer Data_LocateEntry
(
	Dictionary pointer Entries,
	CString Path
)
{
	DataIterating State = DataIteration_OBJECT;
	Generic pointer Iterator = Entries;
	CString PathIterator = Path;
	DataValue pointer FoundValue = NULL;
	Integer Position = 0;
	Integer Offset = 0;
	Integer PreviousOffset = 0;

object_iterator:
	Position = 0;
	Offset = 0;

	while (PathIterator[Position] isnt '\0')
	{
		if (PathIterator[Position] is '.')
		{
			PathIterator[Position] = '\0';
			if (PathIterator[Position + 1] is '\0')
				break;

			if (State is DataIteration_OBJECT)
				FoundValue = (DataValue pointer) Dictionary_Get(Iterator, PathIterator);
			if (State is DataIteration_ARRAY)
				FoundValue = (DataValue pointer) Dynamic_Get(Iterator, PreviousOffset);
			if (no FoundValue or FoundValue->Type isnt DataType_Object)
				return NULL;

			PathIterator = address PathIterator[Position + 1];
			Iterator = address FoundValue->GetAs.Object;
			State = DataIteration_OBJECT;
			
			goto object_iterator;
		}
		if (PathIterator[Position] is '[')
		{
			Integer ArrayOffsetEnd;
			CString Start = NULL;

			PathIterator[Position] = '\0';
			if (PathIterator[Position + 1] is '\0')
				return NULL;
			if (PathIterator[Position + 1] is ']')
				break;

			ArrayOffsetEnd = Position + 1;
			Start = address PathIterator[Position + 1];			

			while (PathIterator[ArrayOffsetEnd] isnt '\0')
			{
				if (PathIterator[ArrayOffsetEnd] is ']')
				{
					PathIterator[ArrayOffsetEnd] = '\0';

					Offset = CString_GetAsInteger(Start);
					
					if (State is DataIteration_OBJECT)
						FoundValue = (DataValue pointer) Dictionary_Get(Iterator, PathIterator);
					if (State is DataIteration_ARRAY)
						FoundValue = (DataValue pointer) Dynamic_Get(Iterator, PreviousOffset);
					if (no FoundValue or FoundValue->Type isnt DataType_Array)
						return NULL;

					PathIterator = address PathIterator[ArrayOffsetEnd + 1];
					Iterator = address FoundValue->GetAs.Array;
					State = DataIteration_ARRAY;
					PreviousOffset = Offset;

					goto object_iterator;
				}
				ArrayOffsetEnd++;
			}			
		}
		Position++;
	}

	if (State is DataIteration_OBJECT)
		return Dictionary_Get(Iterator, PathIterator);
	if (State is DataIteration_ARRAY)
	{
		MemoryHandler pointer Member = Dynamic_Get(Iterator, PreviousOffset);
		if (Member)
			return Member->Data; 
	}

	return NULL;
}

/*##====[ FUNCTIONS ]====##*/

Data Data_New
(
	DictionaryEntry InitialState[]
)
{
	Data NewInstance = {Dictionary_New(InitialState)};
	return NewInstance;
}

DataValue Data_Get
(
	Data pointer Instance,
	CString Path
)
{
	DataValue pointer Result = nullpointer;
	DataValue Value = nullobject;
	CString PathEditable = CString_Set(Path);

	if (no PathEditable)
		goto default_value;

	Result = Data_LocateEntry(address Instance->Entries, PathEditable);
	if (no Result)
		goto default_value;

	Value = valueat Result;

default_value:
	Memory_Free(PathEditable);
	return Value;
}

Outcome Data_Set
(
	Data pointer Instance,
	CString Path,
	DataValue Value
)
{
	DataValue pointer Result = nullpointer;
	CString PathEditable = CString_Set(Path);

	Result = Data_LocateEntry(address Instance->Entries, PathEditable);
	if (no Result)
		goto set_end;

	Memory_Copy(Result, address Value, sizeof(Value));

set_end:
	Memory_Free(PathEditable);
	return Outcome_OK;
}

Void Data_Free
(
	Data pointer Instance
)
{
	/*#pragma message("[J][C]ube[Code]>> TODO: Data_Free()")*/
	ignore Instance;
}

Outcome Data_Save
(
	Data Instance,
	CString Filename,
	Boolean DoIndent
)
{
	Size Iterator;
	FileStream pointer DumpFile = FileStream_Open(Filename, "wb");
	DictionaryEntry pointer CurrentEntry = NULL;

	if (no DumpFile)
		return Outcome_FAIL;

	for (Iterator = 0; Iterator < Instance.Entries.Contents.Count; Iterator++)
	{
		CurrentEntry = Instance.Entries.Contents.Entries[Iterator].Data;
		Data_DumpValue(
			CurrentEntry->Key,
			CurrentEntry->Value.Data,
			DumpFile,
			DoIndent,
			0
		);
	}

	FileStream_Close(DumpFile);
	return Outcome_OK;
}

CString Data_StripWhitespace
(
	CString FileBuffer,
	Size ReadResult
)
{
	Size Index = 0;
	Looper Iterator;
	CString ParsedBuffer = NULL;
	DataParsing State = DataParsing_VALUE;

	ParsedBuffer = Memory_ClearAllocate(ReadResult, sizeof(Byte));
	if (no ParsedBuffer)
		return NULL;

	for (Iterator = 0; Iterator < ReadResult; Iterator++)
	{
		if (State is DataParsing_VALUE)
		{
			switch (FileBuffer[Iterator])
			{
				case ' ':
				case '\t':
				case '\n':
					continue;
				case '"':
					State = DataParsing_STRING;
					break;
				case '#':
					State = DataParsing_COMMENT;
					break;
			}
		}
		else if (State is DataParsing_STRING)
		{
			if (FileBuffer[Iterator] is '"' and FileBuffer[Iterator - 1] isnt '\\')
				State = DataParsing_VALUE;
		}
		else if (State is DataParsing_COMMENT)
		{
			if (FileBuffer[Iterator] is '\n')
				State = DataParsing_VALUE;
		}

		ParsedBuffer[Index] = FileBuffer[Iterator];
		Index++;
	}

	return ParsedBuffer;
}

CString Data_LoadFileIntoMemory
(
	FileStream pointer DumpFile
)
{
	Size TotalSize = 0;
	Size ReadResult;
	CString Allocation = NULL;

	FileStream_SetPosition(DumpFile, 0L, SEEK_END);
	TotalSize = FileStream_GetPosition(DumpFile);
	FileStream_RewindFile(DumpFile);

	Allocation = Memory_ClearAllocate(TotalSize, sizeof(Byte));
	if (no Allocation)
		return NULL;

	ReadResult = FileStream_Read(
		Allocation,
		sizeof(Byte),
		TotalSize,
		DumpFile
	);
	if (ReadResult isnt TotalSize)
		return NULL;

	return Data_StripWhitespace(Allocation, ReadResult);
}

Data Data_Load
(
	CString Filename,
	Boolean DoKeepComments
)
{
	Data NewInstance = Data_New(NULL);
	FileStream pointer DumpFile = FileStream_Open(Filename, "rb");
	CString Parsed = NULL;
	CString FullFile = NULL;

	ignore DoKeepComments;

	if (no DumpFile)
		goto error_no_file;

	FullFile = FileStream_ReadFull(DumpFile);
	if (no FullFile)
		goto error_no_file;

	Parsed = Data_StripWhitespace(FullFile, CString_Length(FullFile));
	if (no Parsed)
		goto error_whitespace;

	Data_CreateObject(address NewInstance.Entries, Parsed);

	Memory_Free(Parsed);
error_whitespace:
	Memory_Free(FullFile);
error_no_file:
	return NewInstance;
}

/*##====[ DATA TYPES ]====##*/

DATATYPE_LIST(DATATYPE_FUNCTION_FULL)
