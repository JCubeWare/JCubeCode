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

#ifndef JCUBECODE_CLI_COMMON_H
#define JCUBECODE_CLI_COMMON_H

/*##====[ JCUBECODE ]====##*/

#include <JCubeCode_0.0.1/JCubeCode.h>

/*##====[ DEFINES ]====##*/

#define JCUBECODE_ENTRY_SIZE 4096
#define JCUBECODE_COMMAND_MAX_SIZE 65535
#define JCUBECODE_GLOBAL_PATH ".JCubeCode"

/*##====[ OPTIONS ]====##*/

typestruct(JCubeCode_Option,
	CString Name;
	CString Description;
	Outcome FunctionPointer(DoFunction, (Arguments));
);

/*##====[ VARIABLES ]====##*/

extern JCubeCode_Option MainOptions[];
extern Logger Print;
extern CString CurrentDirectory;

/*##====[ FUNCTIONS ]====##*/

Boolean DoUserConfirm
(
	CString Text
);

#endif
