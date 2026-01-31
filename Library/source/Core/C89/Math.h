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

#ifndef JCUBECODE_CORE_C89_MATH_H
#define JCUBECODE_CORE_C89_MATH_H

/*##====[ INCLUDE ]====##*/

#include "../../Core/Core.h"

/*##====[ FUNCTIONS ]====##*/

/*
 * Seed the random generator with a specified number.
 * It's standard practice to use the current time, but you may use your own seed
 * for better and less deterministic results.
 */
JCubeLayer Void Math_SeedRandom
(
	WholeInteger Seed
)
{
	srand(Seed);
}

/*
 * Returns a random number between 0 and RAND_MAX (inclusive).
 * For better results, use Math_RandomSeed()
 */
JCubeLayer Integer Math_Random
(
	noarguments
)
{
	return rand();
}

/*
 * Returns the nearest integral number rounded upward that is equal to or bigger
 * than "Number".
 *
 * For example, 2.6 becomes 3.0, but 2.2 also becomes 3.0.
 */
JCubeLayer Double Math_Ceiling
(
	Double Number
)
{
	return ceil(Number);
}

/*
 * Returns the nearest integral number rounded downwards that is equal to or
 * smaller than "Number".
 *
 * For example, 2.3 becomes 2.0, but 2.8 also becomes 2.0.
 */
JCubeLayer Double Math_Floor
(
	Double Number
)
{
	return floor(Number);
}

/*
 * Returns a Modulo remainder of division between the "Dividend" and "Divisor"
 * represented by a floating point value.
 */
JCubeLayer Double Math_Modulus
(
	Double Dividend,
	Double Divisor
)
{
	return fmod(Dividend, Divisor);
}

/*
 * Returns a structure that contains the result of division between "Dividend"
 * and "Divisor". Structure in question has the result and remainder in it.
 */
JCubeLayer IntegerDivision Math_DivideIntegers
(
	Integer Dividend,
	Integer Divisor
)
{
	return div(Dividend, Divisor);
}

/*
 * Returns a structure that contains the result of division between "Dividend"
 * and "Divisor". Structure in question has the result and remainder in it.
 */
JCubeLayer LongDivision Math_DivideLongs
(
	Long Dividend,
	Long Divisor
)
{
	return ldiv(Dividend, Divisor);
}

/*
 * Returns a square root for "Number".
 */
JCubeLayer Double Math_SquareRoot
(
	Double Number
)
{
	return sqrt(Number);
}

/*
 * Returns an exponent of "Base" to the power of "Exponent".
 */
JCubeLayer Double Math_Exponent
(
	Double Base,
	Double Exponent
)
{
	return pow(Base, Exponent);
}

/*
 * Returns a multiplication of "Base" by 2 to the power of "Exponent".
 * Essentially recombines a mantissa and an exponent into a correct Float.
 */
JCubeLayer Double Math_BinaryScientific_Set
(
	Double Base,
	Integer Exponent
)
{
	return ldexp(Base, Exponent);
}

/*
 * Returns a mantissa of the provided "Number" and stores the exponent at the
 * address in "StoredExponent"
 */
JCubeLayer Double Math_BinaryScientific_Get
(
	Double Number,
	Integer pointer StoredExponent
)
{
	return frexp(Number, StoredExponent);
}

/*
 * Returns the exponential function of "Exponent" by calculating Euler's number
 * to the power of "Exponent" (e^"Exponent")
 */
JCubeLayer Double Math_EulerExponent
(
	Double Exponent
)
{
	return exp(Exponent);
}

/*
JCubeLayer Double Math_Round
(
	Double Number
)
{
	return round(Number);
}
*/

/*
 * Returns the natural logarithm of "Number" (log[e]("Number")).
 */
JCubeLayer Double Math_Logarithm
(
	Double Number
)
{
	return log(Number);
}

/*
 * Returns the base 10 logarithm of "Number" (log[10]("Number")).
 */
JCubeLayer Double Math_Logarithm_Base10
(
	Double Number
)
{
	return log10(Number);
}

/*
 * Splits "Number" into the integral and fractional parts. Fractional part is
 * returned by this function, while the integral is stored in "IntegerPart" 
 */
JCubeLayer Double Math_Float_Split
(
	Double Number,
	Double pointer IntegerPart
)
{
	return modf(Number, IntegerPart);
}

/*
 * Return the absolute value of Integer "Number"
 */
JCubeLayer Integer Math_Integer_GetAbsolute
(
	Integer Number
)
{
	return abs(Number);
}

/*
 * Return the absolute value of Long "Number"
 */
JCubeLayer Long Math_Long_GetAbsolute
(
	Long Number
)
{
	return labs(Number);
}

/*
 * Return the absolute value of Float "Number"
 */
JCubeLayer Float Math_Float_GetAbsolute
(
	Float Number
)
{
	return fabsf(Number);
}

/*
 * Return the absolute value of Double "Number"
 */
JCubeLayer Double Math_Double_GetAbsolute
(
	Double Number
)
{
	return fabs(Number);
}

/*
 * Return the absolute value of LongDouble "Number"
 */
JCubeLayer LongDouble Math_LongDouble_GetAbsolute
(
	LongDouble Number
)
{
	return fabsl(Number);
}

/*##====[ GONIOMETRY ]====##*/

/*
 * Returns the sine value of "Number".
 */
JCubeLayer Double Math_Sine
(
	Double Number
)
{
	return sin(Number);
}

/*
 * Returns the hyperbolic sine value of "Number".
 */
JCubeLayer Double Math_SineHyperbolic
(
	Double Number
)
{
	return sinh(Number);
}

/*
 * Returns the cosine value of "Number".
 */
JCubeLayer Double Math_Cosine
(
	Double Number
)
{
	return cos(Number);
}

/*
 * Returns the hyperbolic cosine value of "Number".
 */
JCubeLayer Double Math_CosineHyperbolic
(
	Double Number
)
{
	return cosh(Number);
}

/*
 * Returns the tangent cosine value of "Number".
 */
JCubeLayer Double Math_Tangent
(
	Double Number
)
{
	return tan(Number);
}

/*
 * Returns the hyperbolic tangent value of "Number".
 */
JCubeLayer Double Math_TangentHyperbolic
(
	Double Number
)
{
	return tanh(Number);
}

/*
 * Returns the arc sine value of "Number".
 */
JCubeLayer Double Math_ArcSine
(
	Double Number
)
{
	return asin(Number);
}

/*
 * Returns the arc cosine value of "Number".
 */
JCubeLayer Double Math_ArcCosine
(
	Double Number
)
{
	return acos(Number);
}

/*
 * Returns the arc tangent value of the ratio in radians.
 */
JCubeLayer Double Math_ArcTangent_Ratio
(
	Double Ratio
)
{
	return atan(Ratio);
}

/*
 * Returns the arc tangent value of the coordinates in radians.
 */
JCubeLayer Double Math_ArcTangent_Coordinates
(
	Double XCoordinate,
	Double YCoordinate
)
{
	return atan2(XCoordinate, YCoordinate);
}

#endif
