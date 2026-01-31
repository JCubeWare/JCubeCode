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

/*##====[ INCLUDES ]====##*/

#include "CString.h"

/*##====[ FEATURES ]====##*/

Boolean CString_Matches
(
	readonly CString First,
	readonly CString Second
)
{
	return logic(CString_Compare(First, Second) equals 0);
}

CString CString_Set
(
	CString Source
)
{
	if (no Source)
		return Source;
	{
		Size Length = CString_Length(Source);
		CString NewInstance = Memory_ClearAllocate(
			Length + 1,
			sizeof(Character)
		);
		if (no NewInstance)
			return NewInstance;

		NewInstance[Length] = '\0';

		CString_Copy(NewInstance, Source);
		return NewInstance;
	}
}

CString CString_SetFormatted
(
	CString Format,
	variadicarguments
)
{
	CString NewInstance = nullpointer;
	Size AllocateBytes;
	Variadic Arguments;

	if (no Format)
		return Format;

	Variadic_Start(Arguments, Format);
	AllocateBytes = Variadic_CString_PrintFormattedCount(
		nullpointer,
		0,
		Format,
		Arguments
	);
	Variadic_End(Arguments);

	NewInstance = Memory_ClearAllocate(AllocateBytes + 1, sizeof(Character));
	if (no NewInstance)
		return NewInstance;

	Variadic_Start(Arguments, Format);
	Variadic_CString_PrintFormattedCount(
		NewInstance,
		AllocateBytes + 1,
		Format,
		Arguments
	);
	Variadic_End(Arguments);
	return NewInstance;
}
