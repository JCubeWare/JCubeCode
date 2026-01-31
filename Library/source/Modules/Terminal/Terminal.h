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

#ifndef JCUBECODE_MODULES_TERMINAL_H
#define JCUBECODE_MODULES_TERMINAL_H

#ifdef JCUBECODE_TODO
#pragma message("[J][C]ube[Code] >> TODO: Finish Terminal module.")
#endif

/*##====[ INCLUDES ]====##*/

#include "../../Core/Core.h"

/*##====[ DATA TYPES ]====##*/

typeenum(TerminalColor,
	TerminalColor_NONE = 0,
	TerminalColor_BLACK = 30,
	TerminalColor_DARK_RED,
	TerminalColor_DARK_GREEN,
	TerminalColor_DARK_YELLOW,
	TerminalColor_DARK_BLUE,
	TerminalColor_DARK_MAGENTA,
	TerminalColor_DARK_CYAN,
	TerminalColor_LIGHT_GRAY,
	TerminalColor_DARK_GRAY = 90,
	TerminalColor_RED,
	TerminalColor_GREEN,
	TerminalColor_YELLOW,
	TerminalColor_BLUE,
	TerminalColor_MAGENTA,
	TerminalColor_CYAN,
	TerminalColor_WHITE,
);

/*
 * All the available text decorations in common terminals.
 */
typeenum(TerminalFont,
	TerminalFont_NORMAL = 0,
	TerminalFont_BOLD,
	TerminalFont_FAINT, /* not widely supported */
	TerminalFont_ITALIC, /* not widely supported */
	TerminalFont_UNDERLINE,
	TerminalFont_BLINK_SLOW,
	TerminalFont_BLINK_RAPID,
	TerminalFont_COLOR_REVERSE,
	TerminalFont_CONCEAL,
	TerminalFont_CROSSED_OUT,
	TerminalFont_PRIMARY_FONT,
	TerminalFont_ALTERNATE_FONT_1,
	TerminalFont_ALTERNATE_FONT_2,
	TerminalFont_ALTERNATE_FONT_3,
	TerminalFont_ALTERNATE_FONT_4,
	TerminalFont_ALTERNATE_FONT_5,
	TerminalFont_ALTERNATE_FONT_6,
	TerminalFont_ALTERNATE_FONT_7,
	TerminalFont_ALTERNATE_FONT_8,
	TerminalFont_ALTERNATE_FONT_9,
	TerminalFont_FRAKTUR,
	TerminalFont_UNDERLINE_DOUBLE,
);

#endif
