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

#ifndef JCUBECODE_CORE_BASE_LISTS_H
#define JCUBECODE_CORE_BASE_LISTS_H

/*##====[ DESCRIPTION ]====##*/
/*
 * This is a generic macro list. It's a very useful way to align structures and
 * enumerations.
 *
 * You can use this as a template.
 */

/*##====[ INCLUDES ]====##*/

#define MACROLIST_ENTRY(NAME, STRING, OUTCOME)

#define MACROLIST(MACROLIST_ENTRY) \
	MACROLIST_ENTRY(TESTENTRY, "String entry", OK) \
	MACROLIST_ENTRY(SUPERTESTENTRY, "Another entry", FAIL) \

#define MACROLIST_ENUM(NAME, STRING, OUTCOME) \
	EnumName_##NAME,

#define MACROLIST_STRUCT(NAME, STRING, OUTCOME) \
	{\
		NAME,\
		STRING,\
		Outcome_##OUTCOME \
	},

#endif
