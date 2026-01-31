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

#ifndef JCUBECODE_CORE_BASE_FEATURES_H
#define JCUBECODE_CORE_BASE_FEATURES_H

/*##====[ DESCRIPTION ]====##*/
/*
 * One of the core aspects of JCubeCode: Features!
 * Here are few defines that shape the more readable experience.
 */

/*##====[ MEMORY / POINTERS ]====##*/

/*
 * This variable is a pointer. What it means that this variable holds a memory
 * address that we interact with as if the type of this pointer is what's 
 * at the address itself.
 */
#define pointer *
#define Pointer(TYPE) TYPE pointer

/*
 * The pointer is empty. It's pointing to 0, which on some low embedded chips
 * might reset the board if allowed to access.
 *
 * When navigating with pointers, it's best practise to ALWAYS verify if this
 * value is not on them when accessing something.
 */
#define nullpointer (void*)0

/*
 * This object is empty and will be set to have its bytes be all zero.
 */
#define nullobject {0}

/*
 * This function returns nothing
 */
#define nullreturn void

/*
 * Returns the memory address of the variable which you want the address of.
 * Perfect for use with pointers.
 */
#define address & 
#define Address(VARIABLE) address VARIABLE

/*
 * Accesses the value at the specified memory location.
 * Perfect for setting variables at pointers.
 */
#define valueat pointer
#define GetValueAt(MEMORY) pointer MEMORY

/*
 * Reverse abstraction for a void pointer, because the void pointer IS a memory
 * address of generic type.
 */
#define MemoryAddress Pointer(Void)

/*
 * Holds the memory address of a function named "NAME" with FUNCTION_ARGS
 * having the arguments such as (Integer, Integer)
 */
#define FunctionPointer(NAME, FUNCTION_ARGS) (pointer NAME) FUNCTION_ARGS

/*##====[ ARRAY MANAGEMENT ]====##*/

/*
 * This variable holds a reference to the underlying static array of type "TYPE"
 * Since the array is created at compilation, its size cannot be changed.
 */
#define ArrayStatic(TYPE) TYPE pointer

/*
 * This variable holds a reference to a dynamic array of type "TYPE".
 * This block of memory can be resized or be zero at the same time.
 *
 * In almost all the cases, it holds a reference to the first array member.
 * In special cases, it can be another member... for looping algorithms perhaps.
 */
#define ArrayDynamic(TYPE) TYPE pointer

/*
 * This memory location is the starting point for either a static or a dynamic
 * array. It doesn't matter which in the context.
 *
 * Mostly used to specify the intent that this is the start of the point where we
 * do anything in the array.
 */
#define ArrayAny(TYPE) TYPE pointer

/*##====[ CONSTANT ]====##*/

/*
 * This variable can only be assigned to once, and then no more.
 * You can't declare and then assign a value to it.
 */
#define readonly const

/*
 * This pointer variable can't be changed.
 * Whatever is on it can be changed using it.
 */
#define frozenpointer pointer readonly
#define PointerReadOnly(TYPE) TYPE pointer readonly

/*##====[ STATIC ]====##*/

/* 
 * This function / variable is visible only inside the current translation unit.
 * Other code files can't access this.
 */
#define local static

/*
 * This variable is inside a function, initialized once, but its value remains
 * between function calls as it has the entire program's lifetime.
 * 
 * This variable is located inside the data below the heap.
 */
#define persistent static

/*##====[ ARGUMENTS / FUNCTION SEMANTICS ]====##*/

/*
 * This function takes 0 arguments. Passing any is a syntax error.
 */
#define noarguments void

/*
 * This function takes a non-fixed number of arguments.
 * At least one named argument must be specified beforehand.
 */
#define variadicarguments ...

/*
 * This is a wrapper function that simply calls different functions based on
 * some enviroment attributes, such as OS, architecture and so on.
 *
 * Few behaviors may be slightly different.
 */

#ifdef __STDC_VERSION__
#define JCubeLayer local inline
#else
#define JCubeLayer local
#endif

/*##====[ TYPE HANDLING ]====##*/
/*
 * These functions handle creating custom types.
 * Instead of having to manually define a new type and it's definition,
 * these macros do it automagically and free up a bit of space.
 *
 * The implementation is _NAME, so if you still want to reference what the
 * type is, do so with that name, f.e. Structure _Test
 */

#define typestruct(NAME, MEMBERS) \
	typedef struct _##NAME NAME; \
	struct _##NAME \
	{ \
		MEMBERS \
	}

#define typeunion(NAME, MEMBERS) \
	typedef union _##NAME NAME; \
	union _##NAME \
	{ \
		MEMBERS \
	}

#define typeenum(NAME, ...) \
	enum _##NAME \
	{ \
		__VA_ARGS__  \
		NAME##_COUNT_ \
	}; \
	typedef enum _##NAME NAME

/*##====[ ARITHMETIC KEYWORDS ]====##*/

#define bitand &
#define bitor |
#define bitxor ^
#define bitinvert ~
#define bitleft <<
#define bitright >>
#define bitshift(DIRECTION, VALUE) DIRECTION(VALUE)

/*##====[ CONDITION KEYWORDS ]====##*/

/*
 * Does the same thing as not, but specifically used for verifying variables in
 * if statements.
 */
#define no !

/*
 * If the values match, returns 1
 */
#define is ==

/*
 * If the values don't match, returns 1
 */
#define isnt !=

/*
 * Same as 'is' but for numerical values.
 */
#define equals ==

/*##====[ C99 ]====##*/

#ifndef __STDC_VERSION__
	#define inline 
	#define true 1
	#define false 0
	#define and &&
	#define and_eq &=
	#define bitand &
	#define or ||
	#define or_eq |=
	#define bitor |
	#define xor ^
	#define xor_eq ^=
	#define not !
	#define not_eq !=
	#define compl ~
#endif

/*##====[ UNSORTED ]====##*/

/*
 * The value from this variable, outcome or function is ignored.
 * The compiler will optimize this accordingly.
 */
#define ignore (Void)

/*
 * Logical result of "EXPRESSION". For booleans.
 */
#define logic(EXPRESSION) (EXPRESSION)

/*
 * Automatically iterates from 0 to "MAX" using the "ITERATOR"
 */
#define repeat(ITERATOR, MAX) for (ITERATOR = 0; ITERATOR < MAX; ITERATOR++)

#endif
