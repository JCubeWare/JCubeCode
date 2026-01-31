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

#pragma once

#ifndef JCUBECODE_CORE_BASE_TYPES_H
#define JCUBECODE_CORE_BASE_TYPES_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Type wrappers that allow you to quickswap if your platform struggles.
 * I prefer the data types starting with big letters because it looks more
 * natural and we're no longer limited by "file too big" problems.
 *
 * Some data types here also carry intent despite being basic types wrapped for
 * much easier code reading experience.
 *
 * One could argue this does result in the code being slightly more complicated
 * due to having to "learn" them, but that's why we have this file here.
 */

/*##====[ INCLUDE ]====##*/

#include "Imports.h"
#include "Features.h"

/*##====[ BASIC TYPES ]====##*/

typedef void Void;
typedef char Character;
typedef short Short;
typedef int Integer;
typedef long Long;
typedef float Float;
typedef double Double;
typedef long double LongDouble;
typedef unsigned char WholeCharacter;
typedef unsigned short WholeShort;
typedef unsigned int WholeInteger;
typedef unsigned long WholeLong;

/*##====[ C89 ]====##*/

typedef div_t IntegerDivision;
typedef ldiv_t LongDivision;

typedef Void FunctionPointer(SignalHandler, (Integer));
typedef jmp_buf ProgramJumpBuffer;

typedef wchar_t WideCharacter;
typedef size_t Size;
typedef ptrdiff_t PointerDifference;
typedef FILE FileStream;
typedef fpos_t FilePosition;

typedef clock_t Clock;
typedef time_t Time;
typedef struct tm DateTime;

typedef va_list Variadic;

/*##====[ C99 ]====##*/

#ifdef __STDC_VERSION__

typedef long long DoubleLong;
typedef bool Boolean;

#if __STDC_NO_COMPLEX__ is 1
typedef double Complex;
typedef double Imaginary;
#else
typedef _Complex double Complex;
typedef double Imaginary;
#endif

#else

typedef char Boolean;

#endif

/*##====[ BYTE SIZES ]====##*/

#ifdef __STDC_VERSION_

typedef int8_t Signed8;
typedef uint8_t Unsigned8;
typedef int16_t Signed16;
typedef uint16_t Unsigned16;
typedef int32_t Signed32;
typedef uint32_t Unsigned32;
typedef int64_t Signed64;
typedef uint64_t Unsigned64;

#else

typedef char Signed8;
typedef unsigned char Unsigned8;
typedef short Signed16;
typedef unsigned short Unsigned16;
typedef int Signed32;
typedef unsigned int Unsigned32;

#if defined(_MSC_VER)
typedef __int64 Signed64;
typedef unsigned __int64 Unsigned64;
#elif defined(__GNUC__) || defined(__clang__)
typedef long long Signed64;
typedef unsigned long long Unsigned64;
#else
#pragma message("This platform does not support 64-bit variables.")
#endif
#endif

/*##====[ CROSS-PLATFORM ]====##*/

#if defined(OS_LINUX)

typedef DIR pointer DirectoryHandler;
typedef struct dirent DirectoryEntry;
typedef Integer SocketHandler;

#elif defined(OS_WINDOWS_)

typedef HANDLE DirectoryHandler;
typedef SOCKET SocketHandler;

#elif defined(OS_MACINTOSH)

#elif defined(OS_JCUBEOS)

#else
	#warning "No applicable data types."
#endif

/*##====[ JCUBECODE SPECIFIC ]===##*/

/*
 * Strings in C don't exist, but char* does. Since pointer arithmetics can
 * mess with perception of things, it's more convenient to wrap the type so
 * in the future, implementations can swap.
 */
typedef Pointer(Character) CString;

/*
 * Just communicating the intent that this pointer holds any data, which the
 * programmer should know about.
 */
typedef Void Generic;

/*
 * It's sometimes easier to imagine a character as a byte.
 * Best used for embedded, data handling and other such situations
 */
typedef unsigned char Byte;

/*
 * This variable's only use is to iterate.
 * "What is my purpose?"
 * "You handle loop indexes."
 * "Oh my god."
 */
typedef WholeInteger Looper;

#endif
