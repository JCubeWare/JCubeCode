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

#ifndef JCUBECODE_CORE_C89_PROGRAMFLOW_H
#define JCUBECODE_CORE_C89_PROGRAMFLOW_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Functions that control the program flow, execution and various tasks like
 * a long jump, exiting and enviroment handling.
 */

/*##====[ INCLUDE ]====##*/

#include "../../Core/Core.h"

/*##====[ DEFINES ]====##*/

/*
 * Return the current value of the enviroment variable "Name".
 * If the value is empty or does not exist, NULL is returned.
 */
#define Program_Assert(EXPRESSION) assert(EXPRESSION)

/*##====[ FUNCTIONS ]====##*/

/*
 * Return the current value of the enviroment variable "Name".
 * If the value is empty or does not exist, NULL is returned.
 */
JCubeLayer CString Enviroment_GetCString
(
	readonly CString Name
)
{
	return getenv(Name);
}

/*
 * Aborts program execution and generates a core-dump.
 */
JCubeLayer Void Program_Abort
(
	noarguments
)
{
	abort();
}

/*
 * Call all exit functions in the reverse order of them being registered,
 * clean up input/output buffers and return the program with "ExitCode"
 */
JCubeLayer Void Program_Exit
(
	Integer ExitCode
)
{
	exit(ExitCode);
}

/*
 * Registers a callback function that will be executed at Program_Exit().
 *
 * Returns 0 on success and non-zero on failure.
 */
JCubeLayer Integer Program_RegisterExitCallback
(
	Void FunctionPointer(CallbackFunction, (noarguments))
)
{
	return atexit(CallbackFunction);
}

/*
 * Executes the command CString in "Command" as the system shell.
 *
 * Returns the exit code shell returned or -1 if creating new process failed.
 */
JCubeLayer Integer Program_SystemExecute
(
	readonly CString Command
)
{
	return system(Command);
}

/*
 * Registers the function in "CallbackFunction" to be executed at program being
 * signaled by "Signal"
 *
 * Returns SIG_ERR on failure.
 */
JCubeLayer SignalHandler Program_RegisterSignalHandler
(
	Integer Signal,
	SignalHandler CallbackFunction
)
{
	return signal(Signal, CallbackFunction);
}

/*
 * Sends signal "Signal" to the program.
 *
 * Returns 0 on success and non-zero on failure.
 */
JCubeLayer Integer Program_Signal
(
	Integer Signal
)
{
	return raise(Signal);
}

/*
 * Saves the current stack, registers and execution state into
 * "EnviromentBuffer", creating a "snapshot".
 *
 * Returns 0 at being called directly by itself.
 */
JCubeLayer Integer Program_SaveState
(
	ProgramJumpBuffer ProgramState
)
{
	return setjmp(ProgramState);
}

/*
 * Loads the stack, registers and execution state from "EnviromentBuffer".
 * 
 * Also causes Program_SaveState() to return "Status".
 */
JCubeLayer Void Program_LoadState
(
	ProgramJumpBuffer ProgramState,
	Integer Status
)
{
	longjmp(ProgramState, Status);
}

#endif
