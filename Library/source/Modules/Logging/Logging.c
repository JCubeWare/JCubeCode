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

#include "Logging.h"

/*##====[ DEFINES ]====##*/

#define LOG_MAX_TIMESTRING 128
#define LOG_TIMEFORMAT "%a %d %b %Y | %X"

#define LOG_FORMAT_TIME "(%s) "
#define LOG_FORMAT_MODULE "<%s> "
#define LOG_FORMAT_LEVEL "[%s] "

/*##====[ HELPER FUNCTIONS ]====##*/

local CString Logger_ColorStringCreate
(
	CString SourceString,
	TerminalColor ForegroundColor,
	TerminalColor BackgroundColor,
	TerminalFont TextDecoration
)
{
	Integer AllocateBytes;
	Integer Result;
	CString ColoredString = NULL;

	if (no SourceString)
		return NULL;

	AllocateBytes = CString_PrintFormattedCount(
		ColoredString,
		0,
		"\033[%d;%d;%dm%s\033[0m",
		TextDecoration,
		ForegroundColor,
		BackgroundColor + 10,
		SourceString
	);
	if (AllocateBytes < 0)
		return SourceString;

	ColoredString = Memory_ClearAllocate(AllocateBytes + 1, sizeof(Character));
	if (no ColoredString)
		return NULL;

	Result = CString_PrintFormattedCount(
		ColoredString,
		AllocateBytes + 1,
		"\033[%d;%d;%dm%s\033[0m",
		TextDecoration,
		ForegroundColor,
		BackgroundColor + 10,
		SourceString
	);
	if (Result < 0)
		return SourceString;

	ColoredString[AllocateBytes] = '\0';
	return ColoredString;
}

/*##====[ FUNCTIONS ]====##*/

Outcome Logger_Print
(
	Logger Instance,
	LogLevel LogLevel,
	CString FormatString,
	variadicarguments
)
{
	Time RawTime = Time_Get(NULL);
	DateTime pointer LocalTime = DateTime_GetLocal(address RawTime);
	CString LogIcon = NULL;
	Character TimeString[LOG_MAX_TIMESTRING];
	Variadic Arguments;

	if (LogLevel < Instance.Level)
		return Outcome_OK;
	if (LogLevel >= LogLevel_COUNT_)
		LogLevel = LogLevel_COUNT_ - 1;

	DateTime_GetCStringFormatted(
		TimeString,
		LOG_MAX_TIMESTRING,
		LOG_TIMEFORMAT,
		LocalTime
	);

	if (Instance.UseSpecialCharacters)
	{
		LogIcon = Logger_ColorStringCreate(
			LogLevels[LogLevel].Icon,
			LogLevels[LogLevel].Foreground,
			LogLevels[LogLevel].Background,
			LogLevels[LogLevel].Decoration
		);
		if (no LogIcon)
			return Outcome_ERROR_MEMORY_ALLOCATION;
	}
	else 
		LogIcon = LogLevels[LogLevel].Icon;
	
	FileStream_PrintFormatted(Instance.Stream, LOG_FORMAT_TIME, TimeString);
	if (Instance.ShowName and Instance.Name)
		FileStream_PrintFormatted(Instance.Stream, LOG_FORMAT_MODULE, Instance.Name);
	FileStream_PrintFormatted(Instance.Stream, LOG_FORMAT_LEVEL, LogIcon);

	Variadic_Start(Arguments, FormatString);
	Variadic_FileStream_PrintFormatted(Instance.Stream, FormatString, Arguments);
	Variadic_End(Arguments);
	FileStream_PrintFormatted(Instance.Stream, "\n");

	if (Instance.UseSpecialCharacters)
		Memory_Free(LogIcon);
	return Outcome_OK;
}
