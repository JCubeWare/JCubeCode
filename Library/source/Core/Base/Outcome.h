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

#ifndef JCUBECODE_CORE_BASE_OUTCOME_H
#define JCUBECODE_CORE_BASE_OUTCOME_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Error handling is arguably the most important part of programming.
 * There's many things that go wrong so it's your duty to confirm when an error
 * happens and then gracefully handle it.
 *
 * Outcome is therefore a rather fitting name for an enumeration that literally
 * means "this is the outcome of this function".
 */

/*##====[ INCLUDES ]====##*/

#include "Types.h"

/*##====[ OUTCOME LIST ]====##*/

#define OUTCOME_LIST(OUTCOME_) \
	OUTCOME_(OK, "Everything is OK.") \
	OUTCOME_(FAIL, "General failure.") \
	OUTCOME_(UNKNOWN_OPTION, "Unknown option passed.") \
	OUTCOME_(ERROR_POINTER, "Passed pointer is empty or invalid.") \
	OUTCOME_(ERROR_INVALID_LENGTH, "Passed value's length is 0 or negative.") \
	OUTCOME_(ERROR_MEMORY_ALLOCATION, "Memory allocation failed.") \
	OUTCOME_(ERROR_BAD_ARGUMENT, "Passed argument makes no sense in function's context.") \
	OUTCOME_(ERROR_EMPTY_STRING, "Passed string is empty.") \
	OUTCOME_(ERROR_NOT_INITIALIZED, "Passed object is not initialized.") \
	OUTCOME_(ERROR_NOT_OPENED, "Stream opening has failed.") \
	OUTCOME_(ERROR_PRINTF, "Formatting failed.") \
	OUTCOME_(ERROR_WRITE, "Writing to stream failed.") \
	OUTCOME_(ERROR_READ, "Reading from stream failed.") \
	OUTCOME_(ERROR_SOCKET, "Socket setting or creation failed.") \
	OUTCOME_(ERROR_FILESTREAM, "General filestream error.") \
	OUTCOME_(ERROR_FILENAME, "Filename is too long, empty or contains invalid characters.") \
	OUTCOME_(ERROR_EMPTY_POLICY, "Policy is empty.") \
	OUTCOME_(ERROR_PARSING, "Parsing the associated data has failed.") \
	OUTCOME_(ERROR_ZERO_ARGUMENTS, "No arguments presented. At least one is required.") \
	OUTCOME_(ERROR_REQUIRED_MISSING, "Required argument is missing.") \
	OUTCOME_(ERROR_UNKNOWN_TYPE, "Data is of unknown type.") \
	OUTCOME_(ERROR_CONFIG_LOAD, "Configuration loading failed.") \
	OUTCOME_(ERROR_BAD_CONFIG_PATH, "Configuration path is invalid.") \
	OUTCOME_(ERROR_BAD_CONFIG_VALUE, "Configuration value is invalid.") \
	OUTCOME_(ERROR_INVALID_FORMAT, "Format of said data is presented incorrectly.") \
	OUTCOME_(ERROR_EMPTY_DYNAMIC, "Dynamic array is empty") \
	OUTCOME_(ERROR_OUT_OF_BOUNDS, "Write / Read is out of bounds.")

#define OUTCOME_ENUM(NAME, DESCRIPTION) Outcome_##NAME,

#define OUTCOME_STRUCT(NAME, DESCRIPTION) DESCRIPTION,

/*
 * This macro is used for other macros to behave as "NOTHING".
 */
#define NoAction

/*
 * Error handling for Outcome functions.
 * "ACTION" holds the lines to be run before returning.
 */
#define Outcome_Handle(VARIABLE, EXPRESSION, ACTION) VARIABLE = EXPRESSION; \
	if (VARIABLE){ACTION return VARIABLE;}

/*##====[ ENUMERATIONS ]====##*/

/*
 * Enumerated return states for general errors that can happen.
 * Verify that each function marked with Outcome is handled.
 */
typeenum(Outcome,
	OUTCOME_LIST(OUTCOME_ENUM)
);

/*
 * Written down errors to further inform the user about the return state.
 * Convenient for writing out errors.
 */
extern CString Outcome_Descriptions[];

#endif
