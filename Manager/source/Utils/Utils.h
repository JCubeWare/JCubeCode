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

#ifndef JCUBECODE_CLI_UTILS_H
#define JCUBECODE_CLI_UTILS_H

/*##====[ INCLUDES ]====##*/

#include "../Options.h"

/*##====[ MACRO LISTS ]====##*/

#define JCUBECODE_UTILS_FILE_LIST(OPTION_ACTION) \
	OPTION_ACTION(_utils_file, info, "List file info.") \
	OPTION_ACTION(_utils_file, dump, "Dump contents of file.") \
	OPTION_ACTION(_utils_file, create, "Create new files.") \
	OPTION_ACTION(_utils_file, copy, "Copy file at first path into second path.") \
	OPTION_ACTION(_utils_file, rename, "Rename file at first path into second path.") \
	OPTION_ACTION(_utils_file, delete, "Delete all provided file paths.")

#define JCUBECODE_UTILS_DIRECTORY_LIST(OPTION_ACTION) \
	OPTION_ACTION(_utils_directory, list, "List all entries") \
	OPTION_ACTION(_utils_directory, create, "Create new directory") \
	OPTION_ACTION(_utils_directory, copy, "Copy directory from first path to second path.") \
	OPTION_ACTION(_utils_directory, delete, "Delete the selected directory")

#define JCUBECODE_UTILS_JCDATA_LIST(OPTION_ACTION) \
	OPTION_ACTION(_utils_jcdata, load, "Load JCData from the file ")

#endif
