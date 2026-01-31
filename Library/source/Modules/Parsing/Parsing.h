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

#ifndef JCUBECODE_MODULES_PARSING_H
#define JCUBECODE_MODULES_PARSING_H

#ifdef JCUBECODE_TODO
#pragma message("[J][C]ube[Code] >> TODO: Reprogram obsolete Parsing module.")
#endif

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../Arguments/Arguments.h"
#include "../Strings/Strings.h"

/*##====[ DATA TYPES ]====##*/

typeenum(ParserValueType,
	Parser_NUMBER,
	Parser_STRING,
	Parser_NONE,
);

typeenum(ParserImportance,
	Parser_REQUIRED,
	Parser_OPTIONAL,
);

typeunion(ParserArgumentValue,
	CString Text;
	Double Numeric;
);

typestruct(ParserPolicy,
	CString Name;
	CString Prefix;
	CString Description;
	ParserValueType Type;
	ParserImportance Importance;
);

typestruct(ParserArgument,
	CString Name;
	CString Prefix;
	ParserImportance Importance;
	ParserValueType Type;
	ParserArgumentValue Value;
);

typestruct(Parser,
	Boolean InitDone;
	Boolean IsParsed;
	Size Count;
	ParserArgument pointer List;
);

/*##====[ FUNCTIONS ]====##*/

Parser Parser_New
(
	ParserPolicy Policy
);

Void Parser_Free
(
	Parser pointer Instance
);

Outcome Parser_HandleArguments
(
	Parser pointer Instance, 
	Arguments Arguments,
	ParserPolicy Policy[]
);

Outcome Parser_HandleString
(
	Parser pointer Instance, 
	String Source, 
	String Delimiter, 
	ParserPolicy Policy[]
);

CString Parser_GetOptionString
(
	Parser pointer Instance, 
	CString Prefix
);

Double Parser_GetOptionNumber
(
	Parser pointer Instance, 
	CString Prefix
);

Boolean Parser_OptionExists
(
	Parser pointer Instance,
	CString Prefix
);

#endif
