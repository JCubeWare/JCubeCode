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

#ifndef JCUBECODE_CORE_BASE_PROCESSOR_H
#define JCUBECODE_CORE_BASE_PROCESSOR_H

/*##====[ DESCRIPTION ]====##*/
/*
 * Based on few things, such as used compiler or definitions, we can make an
 * educated rough guess on what system we're using currently.
 *
 * The size of the pointer by itself is a big lead in how to approach design
 * for the specified platform.
 *
 * JCubeCode's biggest strength is modularity so if you want to add your own
 * platform, do so here.
 */

#define PROCESSOR_ARCH (__SIZEOF_POINTER__ * 8)

#if defined(__x86_64__) || defined(__amd64__) || defined(__x86_64) || defined(__amd64)
	#define PROCESSOR_INSTRUCTION_SET "x86_64"
#elif defined(__i386__) || defined(i386) || defined(__i386)
	#define PROCESSOR_INSTRUCTION_SET "x86"
#elif defined(__aarch64__)
	#define PROCESSOR_INSTRUCTION_SET "ARM64 (AArch64)"
#elif defined(__arm__) || defined(__thumb__) || defined(__ARM_ARCH)
	#define PROCESSOR_INSTRUCTION_SET "ARM"
#elif defined(__mips__) || defined(__mips)
	#if defined(__MIPSEB__)
		#define PROCESSOR_INSTRUCTION_SET "Big Endian MIPS"
	#elif defined(__MIPSEL__)
		#define PROCESSOR_INSTRUCTION_SET "Little Endian MIPS"
	#else
		#define PROCESSOR_INSTRUCTION_SET "MIPS"
	#endif
#elif defined(__powerpc64__) || defined(__ppc64__)
	#define PROCESSOR_INSTRUCTION_SET "PowerPC64"
#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
	#define PROCESSOR_INSTRUCTION_SET "PowerPC32"
#elif defined(__riscv)
	#if __riscv_xlen == 64
		#define PROCESSOR_INSTRUCTION_SET "RISC-V (64-bit ABI)"
	#elif __riscv_xlen == 32
		#define PROCESSOR_INSTRUCTION_SET "RISC-V (32-bit ABI)"
	#else
		#define PROCESSOR_INSTRUCTION_SET "RISC-V"
	#endif
#elif defined(__sparc__) || defined(__sparc)
	#define PROCESSOR_INSTRUCTION_SET "SPARC"
#elif defined(__ia64__) || defined(__IA64__)
	#define PROCESSOR_INSTRUCTION_SET "Itanium (IA-64)"
#elif defined(__s390x__)
	#define PROCESSOR_INSTRUCTION_SET "IBM S/390x (64-bit)"
#elif defined(__s390__)
	#define PROCESSOR_INSTRUCTION_SET "IBM S/390 (31-bit)"
#elif defined(__alpha__)
	#define PROCESSOR_INSTRUCTION_SET "Alpha"
#elif defined(__loongarch__) || defined(__loongarch64)
	#ifdef __loongarch64
		#define PROCESSOR_INSTRUCTION_SET "LoongArch (64-bit)"
	#else
		#define PROCESSOR_INSTRUCTION_SET "LoongArch"
	#endif
#elif defined(__wasm__) || defined(__wasm32__) || defined(__wasm64__)
	#ifdef __wasm64__
		#define PROCESSOR_INSTRUCTION_SET "WebAssembly (64-bit)"
	#else
		#define PROCESSOR_INSTRUCTION_SET "WebAssembly (32-bit)"
	#endif
#elif defined(__AVR__)
	#define PROCESSOR_INSTRUCTION_SET "AVR (Microcontroller)"
#elif defined(__TMS320C6X__)
	#define PROCESSOR_INSTRUCTION_SET "TI C6000 (DSP)"
#else
	#define PROCESSOR_INSTRUCTION_SET "Unknown/Unsupported"
#endif

#endif
