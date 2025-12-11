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

#ifndef JCUBECODE_CORE_C89_FILESTREAM_H
#define JCUBECODE_CORE_C89_FILESTREAM_H

/*##====[ DESCRIPTION ]====##*/
/*
 * FileStreams are the abstraction that represent the connection between the
 * program and a file or another input output device.
 * They hold their position, error stream, buffer, mode and type (wide or byte).
 */

/*##====[ INCLUDE ]====##*/

#include "../../Core/Core.h"

/*##====[ FUNCTIONS ]====##*/

/*
 * getc() is usually identical to fgetc() but if it's a macro, it's much faster
 * Therefore, we create an optional wrapper.
 */
#if defined(getc)
#define FileStream_FastReadCharacter getc
#endif

/*
 * putc() is usually identical to fputc() but if it's a macro, it's much faster
 * Therefore, we create an optional wrapper.
 */
#if defined(putc)
#define FileStream_FastReadCharacter putc
#endif

/*
 * Reads one Character from the FileStream in "Stream" and advances the stream
 * position by the read character.
 *
 * On errors or at the end of the file, EOF is returned.
 */
JCubeLayer Integer FileStream_ReadCharacter
(
	FileStream pointer Stream
)
{
	return fgetc(Stream);
}

/*
 * Writes the first Byte from "Data" into the FileStream in "Stream" and
 * advances the stream position by the read character.
 *
 * On errors or at the end of the file, EOF is returned.
 */
JCubeLayer Integer FileStream_WriteCharacter
(
	Integer Data,
	FileStream pointer Stream
)
{
	return fputc(Data, Stream);
}

/*
 * Returns "Data" Character onto the FileStream in "Stream" and moves back the
 * file position.
 *
 * On errors or at the end of the file, EOF is returned.
 */
JCubeLayer Integer FileStream_UngetCharacter
(
	Integer Data,
	FileStream pointer Stream
)
{
	return ungetc(Data, Stream);
}

/*
 * Reads up to "Count" Bytes from "Stream" into "Destination".
 * Reading is stopped on newline (\n) or EOF.
 * Advances the file position by the amount of characters read.
 *
 * Returns the pointer to "Destination" or NULL.
 */
JCubeLayer CString FileStream_ReadCString
(
	CString Destination,
	Integer MaxCharacters,
	FileStream pointer Stream
)
{
	return fgets(Destination, MaxCharacters, Stream);
}

/*
 * Writes the "Source" CString into "Stream"
 * Reading is stopped on newline (\n) or EOF.
 * Advances the file position by the amount of characters read.
 *
 * Returns EOF and sets the error indicator for "Stream"
 */
JCubeLayer Integer FileStream_WriteCString
(
	readonly CString Source,
	FileStream pointer Stream
)
{
	return fputs(Source, Stream);
}

/*
 * Reads "Count" amount of members with the size "DataSize" from memory address
 * at "Data" and writes them into "Stream".
 *
 * Returns the amount of members written to "Stream".
 */
JCubeLayer Size FileStream_Write
(
	readonly MemoryAddress Data,
	Size DataSize,
	Size Count,
	FileStream pointer Stream 
)
{
	return fwrite(Data, DataSize, Count, Stream);
}

/*
 * Reads "Count" amount of members with the size "DataSize" from "Stream" into
 * the memory address at "Data"
 *
 * Returns the amount of members read from "Stream".
 */
JCubeLayer Size FileStream_Read
(
	MemoryAddress Data,
	Size DataSize, 
	Size Count,
	FileStream pointer Stream 
)
{
	return fread(Data, DataSize, Count, Stream);
}

/*
 * Opens a file at location "Filename" with attributes of "Modes" and returns a
 * memory address for the FileStream handler.
 *
 * ## Modes ##
 * - "r": Read (Open a file for reading, fails if file doesn't exist)
 * - "w": Write (Create a file for reading, overwrite if it exists)
 * - "a": Append (Append to a file, create if it doesn't exist)
 * - "+": Extended (Update mode, enables both read and write for any mode)
 * - "b": Binary (Opens file in binary mode)
 */
JCubeLayer FileStream pointer FileStream_Open
(
	readonly CString Filename,
	readonly CString Modes
)
{
	return fopen(Filename, Modes);
}

/*
 * Closes a file and then tries to reopen the file at "Filename" with attributes
 * of "Modes" and returns a memory address for the FileStream handler.
 *
 * ## Modes ##
 * - "r": Read (Open a file for reading, fails if file doesn't exist)
 * - "w": Write (Create a file for reading, overwrite if it exists)
 * - "a": Append (Append to a file, create if it doesn't exist)
 * - "+": Extended (Update mode, enables both read and write for any mode)
 * - "b": Binary (Opens file in binary mode)
 */
JCubeLayer FileStream pointer FileStream_Reopen
(
	readonly CString Filename,
	readonly CString Modes,
	FileStream pointer Stream
)
{
	return freopen(Filename, Modes, Stream);
}

/*
 * Closes the "Stream" and writes any unwritten data in the buffer.
 * Unread buffered data is discarded. 
 */
JCubeLayer Integer FileStream_Close
(
	FileStream pointer Stream
)
{
	return fclose(Stream);
}

/*
 * For output FileStreams, writes any unwritten data from the stream's buffer
 * to the associated output device.
 *
 * For input streams the behavior is undefined and can possibly segfault.
 */
JCubeLayer Integer FileStream_Flush
(
	FileStream pointer Stream
)
{
	return fflush(Stream);
}

/*
 * Sets the internal buffer for input and outbut of "Stream" to be "Buffer".
 * If buffer is null, buffering is disabled altogether.
 */
JCubeLayer Void FileStream_SetBuffer
(
	FileStream pointer Stream,
	CString Buffer
)
{
	setbuf(Stream, Buffer);
}

/*
 * Changes the buffering mode of "Stream" to "Mode".
 * Tells the "Stream" to use "Size" bytes of "Buffer".
 * If "Buffer" is Empty, internal buffer is resized to "Size" instead.
 *
 * Returns 0 on success and non-zero on failure. 
 */
JCubeLayer Integer FileStream_SetVariableBuffer
(
	FileStream pointer Stream,
	CString Buffer,
	Integer Mode,
	Size Size
)
{
	return setvbuf(Stream, Buffer, Mode, Size);
}

/*
 * If "Mode" is bigger than 0, "Stream" will become wide-oriented.
 * If "Mode" is smaller than 0, "Stream" will become byte-oriented.
 * If "Mode" is 0, orientation is returned.
 *
 * Returns the current "Mode".
 */
JCubeLayer Integer FileStream_SetWide
(
	FileStream pointer Stream,
	Integer Mode
)
{
	return fwide(Stream, Mode);
}

/*
 * Sets the position of "Stream" to "Offset" from "Origin".
 *
 * ## Origin values ##
 * - SEEK_SET : Start of "Stream" (Supported on all modes)
 * - SEEK_CUR : Current position of "Stream"
 * - SEEK_END : End of "Stream"
 *
 * Returns 0 on success, non-zero on failure.
 */
JCubeLayer Integer FileStream_SetPosition
(
	FileStream pointer Stream,
	Long Offset,
	Integer Origin
)
{
	return fseek(Stream, Offset, Origin);
}

/*
 * Returns the current position of "Stream".
 * In binary mode, it's amount of bytes. In other modes, just a reference for
 * FileStream_SetPosition()
 */
JCubeLayer Integer FileStream_GetPosition
(
	FileStream pointer Stream
)
{
	return ftell(Stream);
}

/*
 * Sets the current position of "Stream" to value at "Position".
 *
 * Returns 0 on success, non-zero on failure and sets errno.
 */
JCubeLayer Integer FileStream_SetPositionObject
(
	FileStream pointer Stream,
	readonly FilePosition pointer Position
)
{
	return fsetpos(Stream, Position);
}

/*
 * Gets the current position of "Stream" and puts it into value at "Position".
 *
 * Returns 0 on success, non-zero on failure and sets errno.
 */
JCubeLayer Integer FileStream_GetPositionObject
(
	FileStream pointer Stream,
	FilePosition pointer Position
)
{
	return fgetpos(Stream, Position);
}

/*
 * Returns the error indicator for "Stream".
 * If the value is 0, everything is OK.
 */
JCubeLayer Integer FileStream_GetError
(
	FileStream pointer Stream
)
{
	return ferror(Stream);
}

/*
 * Verifies if the end of the file error was reached on "Stream".
 * Use this only after input stream returns an error, otherwise this function
 * is useless. It only returns after I/O operation.
 *
 * Returns a non-zero value if the end of "Stream" was reached and 0 otherwise.
 */
JCubeLayer Integer FileStream_IsAtEnd
(
	FileStream pointer Stream
)
{
	return feof(Stream);
}

/*
 * Resets the error flags and EOF indicator for "Stream".
 */
JCubeLayer Void FileStream_ClearError
(
	FileStream pointer Stream
)
{
	clearerr(Stream);
}

/*
 * Resets the position of "Stream" back to the start.
 */
JCubeLayer Void FileStream_RewindFile
(
	FileStream pointer Stream
)
{
	rewind(Stream);
}

/*
 * Opens a temporary file in mode "wb+" with an auto generated filename.
 * File is deleted upon being closed or upon normal program termination.
 * On errors, it depends on the implementation.
 */
JCubeLayer FileStream pointer FileStream_OpenTempFile
(
	noarguments
)
{
	return tmpfile();
}

/*
 * Creates a unique filename and stores it in "Destination".
 * The function is capable of generating up to TMP_MAX of unique filenames,
 * but some may already be in use, and thus not suitable return values.
 *
 * If "Destination" exists, returns "Filename".
 * If "Destination" is NULL, returns the address of the internal static buffer.
 * If no suitable name can be generated, NULL is returned.
 */
JCubeLayer CString FileStream_GetTempFileName
(
	CString Destination
)
{
	return tmpnam(Destination);
}

#endif
