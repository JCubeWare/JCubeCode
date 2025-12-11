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

#include "Utils.h"

/*##====[ HELPER FUNCTIONS ]====##*/

local Void PrintData
(
	DataValue Value
)
{
	Looper Iterator;

	PrintFormatted("Type: ");

	switch (Value.Type)
	{
		case DataType_Array:
			PrintFormatted("Array[%ld], Contents:\n", Value.GetAs.Array.Count);
			for (Iterator = 0; Iterator < Value.GetAs.Array.Count; Iterator++)
			{
				DataValue pointer ArrayEntry = Value.GetAs.Array.Entries[Iterator].Data;
				PrintFormatted(" [%d]: ", Iterator);
				PrintData(valueat ArrayEntry);
			}
			break;
		case DataType_Boolean:
			PrintFormatted("Boolean, Contents: %s", Value.GetAs.Boolean ? "true" : "false");
			break;
		case DataType_DateTime:
			PrintFormatted("DateTime (WIP)");
			break;
		case DataType_Float:
			PrintFormatted("Float, Contents: %g", Value.GetAs.Float);
			break;
		case DataType_Integer:
			PrintFormatted("Integer, Contents: %d", Value.GetAs.Integer);
			break;
		case DataType_Object:
			PrintFormatted("Object[%ld], Contents:\n", Value.GetAs.Object.Contents.Count);
			for (Iterator = 0; Iterator < Value.GetAs.Object.Contents.Count; Iterator++)
			{
				DictionaryEntry pointer ObjectEntry = Value.GetAs.Object.Contents.Entries[Iterator].Data;
				DataValue pointer ObjectValue = ObjectEntry->Value.Data;
				PrintFormatted(" '%s': ", ObjectEntry->Key);
				PrintData(valueat ObjectValue);
			}
			break;
		case DataType_Raw:
			PrintFormatted("Raw (Binary) (WIP)");
			break;
		case DataType_String:
			PrintFormatted("String, Contents: %s", Value.GetAs.String);
			break;
		default:
			PrintFormatted("NULL");
		break;
	}
	PrintFormatted("\n");
}

Outcome _utils_jcdata_load
(
	Arguments Arguments
)
{
	if (Arguments.Count isnt 1)
	{
		PrintFormatted("Format: [path]\n");
		return Outcome_FAIL;
	}
	else
	{
		Data Test = Data_Load(Arguments.Entry[0], true);
		Looper Iterator;
		DictionaryEntry pointer CurrentEntry;
		DataValue pointer CurrentValue;

		PrintFormatted(
			"\n##====[ JCDATA ]====##\nCount: %ld\n\n",
			Test.Entries.Contents.Count
		);

		for (Iterator = 0; Iterator < Test.Entries.Contents.Count; Iterator++)
		{
			CurrentEntry = Test.Entries.Contents.Entries[Iterator].Data;
			CurrentValue = CurrentEntry->Value.Data;
			PrintFormatted("'%s': ", CurrentEntry->Key);
			PrintData(valueat CurrentValue);
		}
		return Outcome_OK;
	}
}

/*##====[ VARIABLES ]====##*/

JCubeCode_Option UtilsJCDataOptions[] = {
	JCUBECODE_UTILS_JCDATA_LIST(JCUBECODE_OPTION_STRUCT)
	{NULL}
};

/*##====[ SUBMENU ]====##*/

JCUBECODE_FUNCTION_SUBMENU(_utils_jcdata, UtilsJCDataOptions)
