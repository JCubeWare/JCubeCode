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

#ifndef JCUBECODE_MODULES_JCDATA_TYPES_H
#define JCUBECODE_MODULES_JCDATA_TYPES_H

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"
#include "../Dynamic/Dynamic.h"
#include "../Dictionary/Dictionary.h"

/*##====[ MACRO LIST ]====##*/

#define NONE

#define DATATYPE_ENUM(NAME, TYPE, INIT, NEW) DataType_##NAME,
#define DATATYPE_UNION(NAME, TYPE, INIT, NEW) TYPE NAME;
#define DATATYPE_FUNCTION_NAME(NAME, TYPE, INIT, NEW) \
	DataValue pointer Data_##NAME(INIT Data)

#define DATATYPE_FUNCTION_HEADER(NAME, TYPE, INIT, NEW) DATATYPE_FUNCTION_NAME(NAME, TYPE, INIT, NEW);
#define DATATYPE_FUNCTION_FULL(NAME, TYPE, INIT, NEW) \
	DATATYPE_FUNCTION_NAME(NAME, TYPE, INIT, NEW) \
	{ \
	DataValue pointer NewInstance = Memory_New(DataValue); \
	NewInstance->Type = DataType_##NAME; \
	NewInstance->GetAs.NAME = NEW(Data); \
	return NewInstance; \
	}

#define DATATYPE_LIST(DATATYPE_) \
	DATATYPE_(Boolean, Boolean, Boolean, NONE) \
	DATATYPE_(String, CString, CString, NONE) \
	DATATYPE_(DateTime, DateTime, DateTime, NONE) \
	DATATYPE_(Float, Double, Double, NONE) \
	DATATYPE_(Integer, Integer, Integer, NONE) \
	DATATYPE_(Raw, ArrayDynamic(Byte), ArrayDynamic(Byte), NONE) \
	DATATYPE_(Array, Dynamic, DynamicInitial, Dynamic_New) \
	DATATYPE_(Object, Dictionary, DictionaryInitial, Dictionary_New)

/*##====[ DATA TYPES ]====##*/

typeenum(DataType,
	DataType_Null,
	DATATYPE_LIST(DATATYPE_ENUM)
);

typeunion(DataStorage,
	DATATYPE_LIST(DATATYPE_UNION)
);

typestruct(DataValue,
	DataType Type;
	DataStorage GetAs;
);

#endif
