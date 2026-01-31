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

#ifndef JCUBECODE_CORE_C89_CHARACTER_H
#define JCUBECODE_CORE_C89_CHARACTER_H

/*##====[ DESCRIPTION ]====##*/
/*
 * These functions fully focus on characters and handling bytes.
 * Despite the C89 library declaring these types as Integer due to compatibility
 * with some older compilers, you can safely use Byte data types to represent.
 */

/*##====[ INCLUDE ]====##*/

#include "../Base/Base.h"

/*##====[ DEFINES ]====##*/

#define ErrorCode errno

/*##====[ FUNCTIONS ]====##*/

/*
 * Returns a non-zero value if the passed character is alphanumeric, which means
 * that it either is a letter from the alphabet or a digit.
 *
 * Contains: (A-Z) (a-z) (0-9)
 */
JCubeLayer Integer Character_IsAlphanumeric
(
	Integer Instance
)
{
	return isalnum(Instance);
}

/*
 * Returns a non-zero value if the passed character belongs to the alphabet.
 *
 * Contains: (A-Z) (a-z)
 */
JCubeLayer Integer Character_IsAlphabetic
(
	Integer Instance
)
{
	return isalpha(Instance);
}

/*
 * Returns a non-zero value if the passed character is lowercase.
 *
 * Contains: (a-z)
 */
JCubeLayer Integer Character_IsLowercase
(
	Integer Instance
)
{
	return islower(Instance);
}

/*
 * Returns a non-zero value if the passed character is uppercase.
 *
 * Contains: (A-Z)
 */
JCubeLayer Integer Character_IsUppercase
(
	Integer Instance
)
{
	return isupper(Instance);
}

/*
 * Returns a non-zero value if the passed character is a digit belonging to a 
 * decimal number.
 *
 * Contains: (0-9)
 */
JCubeLayer Integer Character_IsDigit
(
	Integer Instance
)
{
	return isdigit(Instance);
}

/*
 * Returns a non-zero value if the passed character is a digit belonging to a 
 * hexadecimal number.
 *
 * Contains: (0-9) (A-F) (a-f)
 */
JCubeLayer Integer Character_IsHexadecimal
(
	Integer Instance
)
{
	return isxdigit(Instance);
}

/*
 * Returns a non-zero value if the passed character is control character.
 * Control characters are invisible characters that are used for signaling and
 * controlling simple functions. (f.e. byte 7, which represents a Terminal bell)
 *
 * Contains: (Byte 0 - Byte 31), Byte 127 (DEL)
 */
JCubeLayer Integer Character_IsControlCharacter
(
	Integer Instance
)
{
	return iscntrl(Instance);
}

/*
 * Returns a non-zero value if the passed character is graphical.
 * Graphical characters can be printed on the screen and are visible.
 *
 * Contains: (Byte 33 - Byte 126)
 */
JCubeLayer Integer Character_IsGraphical
(
	Integer Instance
)
{
	return isgraph(Instance);
}

/*
 * Returns a non-zero value if a whitespace character.
 * Whitespace characters separate text into tokens, such as Space and Tabulator.
 *
 * Contains: (Byte 9 - Byte 13), Byte 32 (Space)
 */
JCubeLayer Integer Character_IsWhitespace
(
	Integer Instance
)
{
	return isspace(Instance);
}

/*
 * Returns a non-zero value if the passed character is printable.
 * It's very similiar to Character_IsGraphical() but also includes the space.
 *
 * Contains: (Byte 33 - Byte 126)
 */
JCubeLayer Integer Character_IsPrintable
(
	Integer Instance
)
{
	return isprint(Instance);
}

/*
 * Returns a non-zero value if the passed character belongs to punctation.
 * It's very similiar to Character_IsGraphical() but also includes the space.
 *
 * Contains: ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~
 */
JCubeLayer Integer Character_IsPunctation
(
	Integer Instance
)
{
	return ispunct(Instance);
}

/*
 * Returns this character as a lowercase version of itself.
 * If the character has no lowercase variant, "Instance" is returned instead.
 *
 * Contains: (A-Z)
 */
JCubeLayer Integer Character_GetAsLowercase
(
	Integer Instance
)
{
	return tolower(Instance);
}

/*
 * Returns this character as an uppercase version of itself.
 * If the character has no uppercase variant, "Instance" is returned instead.
 *
 * Contains: (a-z)
 */
JCubeLayer Integer Character_GetAsUppercase
(
	Integer Instance
)
{
	return toupper(Instance);
}

#endif
