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

#pragma once

#ifndef JCUBECODE_CORE_C89_TIME_H
#define JCUBECODE_CORE_C89_TIME_H

/*##====[ INCLUDE ]====##*/

#include "../../Core/Core.h"

/*##====[ FUNCTIONS ]====##*/

/*
 * Returns the current time and also puts it in the address provided in "Timer"
 * if it isn't Empty.
 */
JCubeLayer Time Time_Get
(
	Time pointer Timer
)
{
	return time(Timer);
}

/*
 * Returns the time at the address of "Timer" as a CString that's formatted as
 * WWW MMM DD HH:mm:ss YYYY (for example: "Sun Dec 17 21:34:26 2023").
 */
JCubeLayer CString Time_GetCString
(
	readonly Time pointer Timer
)
{
	return ctime(Timer);
}

/*
 * Returns the time difference between "First" and "Second".
 */
JCubeLayer Double Time_GetDifference
(
	Time First,
	Time Second
)
{
	return difftime(First, Second);
}

/*
 * Returns the processor time used by the program (user time + system time).
 * The result / CLOCKS_PER_SEC is program time in seconds.
 */
JCubeLayer Clock Clock_Get
(
	noarguments
)
{
	return clock();
}

/*
 * Returns the time at the address of "DateTimer" as a CString that's formatted
 * as WWW MMM DD HH:mm:ss YYYY (for example: "Sun Dec 17 21:34:26 2023").
 */
JCubeLayer CString DateTime_GetCString
(
	readonly DateTime pointer DateTimer
)
{
	return asctime(DateTimer);
}

/*
 * Converts time at address "Timer" into DateTime representated as GMT
 * (aka Greenwich Mean Time).
 */
JCubeLayer DateTime pointer DateTime_GetGMT
(
	readonly Time pointer Timer
)
{
	return gmtime(Timer);
}

/*
 * Converts time at address "Timer" into DateTime representated by the local
 * timezone.
 */
JCubeLayer DateTime pointer DateTime_GetLocal
(
	readonly Time pointer Timer
)
{
	return localtime(Timer);
}

/*
 * Converts the DateTime at address in "Instance" into Time and returns it.
 */
JCubeLayer Time DateTime_GetTime
(
	DateTime pointer Instance
)
{
	return mktime(Instance);
}

/*
 * Formats the DateTime at "Instance" according to your specified format in
 * "Format" and writes the result in "Destination" up to "MaxSize" characters.
 *
 * ## Formatting options ##
 * - "%a": Short weekday name (Sun)
 * - "%A": Full weekday name (Sunday)
 * - "%b": Short month name (Mar)
 * - "%B": Full month name (March)
 * - "%c": Date and time  (Sun Aug 19 02:56:02 2012)
 * - "%d": Day of the month (01-31)
 * - "%H": Hour in 24h format (00-23)
 * - "%I": Hour in 12h format (01-12)
 * - "%j": Day of the year (001-366)
 * - "%m": Month as a decimal number (01-12)
 * - "%M": Minute (00-59)
 * - "%p": AM or PM
 * - "%S": Second (00-61)
 * - "%U": Week number with first Sunday as first day of week one (00-53)
 * - "%w": Weekday as a decimal number with Sunday as 0 (0-6)
 * - "%W": Week number with first Monday as first day of week one (00-53)
 * - "%x": Date representation (08/19/12)
 * - "%X": Time representation (02:50:06)
 * - "%y": Year, last two digits (00-99)
 * - "%Y": Year (2024)
 * - "%Z": Timezone name or abbreviation (GMT)
 * - "%%": A % sign %
 */
JCubeLayer Size DateTime_GetCStringFormatted
(
	CString Destination,
	Size MaxSize,
	readonly CString Format,
	readonly DateTime pointer Instance
)
{
	return strftime(Destination, MaxSize, Format, Instance);
}

/*
 * Formats the DateTime at "Instance" according to your specified format in
 * "Format" and writes the result in "Destination" up to "MaxSize" characters.
 * Uses wide characters
 *
 * ## Formatting options ##
 * - "%a": Short weekday name (Sun)
 * - "%A": Full weekday name (Sunday)
 * - "%b": Short month name (Mar)
 * - "%B": Full month name (March)
 * - "%c": Date and time  (Sun Aug 19 02:56:02 2012)
 * - "%d": Day of the month (01-31)
 * - "%H": Hour in 24h format (00-23)
 * - "%I": Hour in 12h format (01-12)
 * - "%j": Day of the year (001-366)
 * - "%m": Month as a decimal number (01-12)
 * - "%M": Minute (00-59)
 * - "%p": AM or PM
 * - "%S": Second (00-61)
 * - "%U": Week number with first Sunday as first day of week one (00-53)
 * - "%w": Weekday as a decimal number with Sunday as 0 (0-6)
 * - "%W": Week number with first Monday as first day of week one (00-53)
 * - "%x": Date representation (08/19/12)
 * - "%X": Time representation (02:50:06)
 * - "%y": Year, last two digits (00-99)
 * - "%Y": Year (2024)
 * - "%Z": Timezone name or abbreviation (GMT)
 * - "%%": A % sign %
 */
JCubeLayer Size DateTime_GetWideCStringFormatted
(
	WideCharacter pointer Destination,
	Size MaxSize,
	readonly WideCharacter pointer Format,
	readonly DateTime pointer Instance
)
{
	return wcsftime(Destination, MaxSize, Format, Instance);
}

#endif
