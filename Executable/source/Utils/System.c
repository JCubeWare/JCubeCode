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

#include "Utils.h"

/*##====[ MACRO ]====##*/

#define SayValue(_DATA_TYPE, _FORMAT) \
	PrintFormatted("%-20s" _FORMAT "\n", #_DATA_TYPE, _DATA_TYPE)

#define SayDataState(_DATA_TYPE) \
	PrintFormatted("%-20s %4ld bits (%ld bytes)\n", \
		#_DATA_TYPE ":", sizeof(_DATA_TYPE) * 8, sizeof(_DATA_TYPE));

/*##====[ HELPER FUNCTIONS ]====##*/

Outcome _utils_system
(
	Arguments Arguments
)
{
	ignore Arguments;

	PrintFormatted("\n##====[ SYSTEM ]====##\n\n");
	PrintFormatted("OS: %s\n", OS);
	PrintFormatted(
		"Architecture: %s, %d bit processor\n", 
		PROCESSOR_INSTRUCTION_SET,
		PROCESSOR_ARCH
	);
	PrintFormatted(
		"JCubeCode %d.%d.%d (Built on %s %s)\n",
		JCubeCode.Version.Major,
		JCubeCode.Version.Minor,
		JCubeCode.Version.Patch,
		JCubeCode.Build.Date,
		JCubeCode.Build.Time
	);
	PrintFormatted("\n##====[ DATA TYPES ]====##\n\n");
	SayDataState(Character);
	SayDataState(Short);
	SayDataState(Integer);
	SayDataState(Long);
	SayDataState(Float);
	SayDataState(Double);
	SayDataState(Generic pointer);
	SayDataState(MemoryAddress);
	PrintFormatted("\n##====[ SIZES ]====##\n\n");
	SayDataState(Signed8);
	SayDataState(Unsigned8);
	SayDataState(Signed16);
	SayDataState(Unsigned16);
	SayDataState(Signed32);
	SayDataState(Unsigned32);
	SayDataState(Signed64);
	SayDataState(Unsigned64);
	PrintFormatted("\n##====[ LIMITS ]====##\n\n");
	SayValue(CHAR_BIT, "%d");
	SayValue(MB_LEN_MAX, "%d");

	PrintFormatted("\n#===[ CHARACTER ]===#\n\n");
	SayValue(CHAR_MIN, "%d");
	SayValue(CHAR_MAX, "%d");
	SayValue(SCHAR_MIN, "%d");
	SayValue(SCHAR_MAX, "%d");
	SayValue(UCHAR_MAX, "%u");

	PrintFormatted("\n#===[ SHORT ]===#\n\n");
	SayValue(SHRT_MIN, "%d");
	SayValue(SHRT_MAX, "%d");
	SayValue(USHRT_MAX, "%u");

	PrintFormatted("\n#===[ INTEGER ]===#\n\n");
	SayValue(INT_MIN, "%d");
	SayValue(INT_MAX, "%d");
	SayValue(UINT_MAX, "%u");

	PrintFormatted("\n#===[ LONG ]===#\n\n");
	SayValue(LONG_MIN, "%ld");
	SayValue(LONG_MAX, "%ld");
	SayValue(ULONG_MAX, "%lu");
	return Outcome_OK;
}
