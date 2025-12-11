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

#ifndef JCUBECODE_MODULES_JCDATA_H
#define JCUBECODE_MODULES_JCDATA_H

/*
 * TODO: Finish up JCData. Code is very messy but does function.
 */

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "Types.h"

/*##====[ DEFINES ]====##*/

#define JCDATA_KEY_MAXSIZE 1000
#define JCDATA_VALUE_MAXSIZE 2000

/*##====[ DATA TYPES ]====##*/

typeenum(DataIterating,
	DataIteration_ARRAY,
	DataIteration_OBJECT,
);

typeenum(DataParsing,
	DataParsing_KEY,
	DataParsing_VALUE,
	DataParsing_STRING,
	DataParsing_COMMENT,
);

typestruct(Data,
	Dictionary Entries;
);

/*##====[ FUNCTIONS ]====##*/

Data Data_New
(
	DictionaryInitial InitialState
);

DataValue Data_Get
(
	Data pointer Instance,
	CString Path
);

Outcome Data_Set
(
	Data pointer Instance,
	CString Path,
	DataValue Value
);

Data Data_Load
(
	CString Filename,
	Boolean DoKeepComments
);

Outcome Data_Save
(
	Data Instance,
	CString Filename,
	Boolean DoIndent
);

/*##====[ DATA INIT ]====##*/

DATATYPE_LIST(DATATYPE_FUNCTION_HEADER)

#endif
