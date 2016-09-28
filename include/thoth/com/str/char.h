/*
* 	filename	: char.h
* 	component	: libc
* 	description	: Character-related function definitions
*
* 	This file is part of Thoth.
*
* 	Thoth is free software: you can redistribute it and/or modify
* 	it under the terms of the GNU General Public License as published by
* 	the Free Software Foundation, either version 3 of the License, or
* 	(at your option) any later version.
*
* 	Thoth is distributed in the hope that it will be useful,
* 	but WITHOUT ANY WARRANTY; without even the implied warranty of
* 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU General Public License for more details.
*
* 	You should have received a copy of the GNU General Public License
* 	along with Thoth.  If not, see <http://www.gnu.org/licenses/>.
*/

// Header Guard
#ifndef _THOTH_COM_STR_CHAR_H
#define _THOTH_COM_STR_CHAR_H 1

/* THOTH */

#include "thoth/com/type/all.h"

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif

/* Character Set Checking Functions */

bool	tc_is_alphanumeric(char c);		// Return true if the specified char is alphanumeric (i.e: a, 1, b, 2, ...)
bool	tc_is_alphabetic(char c);		// Return true if the specified char is alphabetic (i.e: a, b, c, ...)
bool	tc_is_lower(char c);			// Return true if the specified char is a lower-case letter (i.e: a, b, c, ...)
bool	tc_is_upper(char c);			// Return true if the specified char is an upper-case letter (i.e: A, B, C, ...)

bool	tc_is_control(char c);			// Return true if the specified char is a control character (i.e: is not printable)
bool	tc_is_printable(char c);		// Return true if the specified char is a printable character (i.e: is displayed on a screen)
bool	tc_is_graphical(char c);		// Return true if the specified char has graphical representation (i.e: influences the content on a screen)
bool	tc_is_punctuation(char c);		// Return true if the specified char is a punctuation character (e.g: ', ", ., ...)
bool	tc_is_whitespace(char c);		// Return true if the specified char is a whitespace character (e.g: space or tab)

bool	tc_is_sign(char c);				// Return true if the specified char is a sign character (e.g: + or -)
bool	tc_is_digit(char c);			// Return true if the specified char is a digit character (e.g: 0, 1, 2, ...)
bool	tc_is_hex(char c);				// Return true if the specified char is a hexadecimal character (e.g: 1, A, d)
bool	tc_is_base64(char c);			// Return true if the specified char is a MIME-standard base64 character (e.g: 1, D, f, =, ...)

bool	tc_is_operator(char c);			// Return true if the specified char is an operator character (e.g: +, ^, *, |, <, ...)
bool	tc_is_arithmeticop(char c);		// Return true if the specified char is an arithmetic operator character (e.g: +, -, *, /, ...)
bool	tc_is_comparisonop(char c);		// Return true if the specified char is a comparasion operator character (e.g: <, =, >, ...)
bool	tc_is_logicalop(char c);		// Return true if the specified char is a logical operator character (e.g: &, |, !, ...)

/* Character Set Shift Functions */

char	tc_to_lower(char c);			// Convert a character to its upper-case equivalent
char	tc_to_upper(char c);			// Convert a character to its lower-case equivalent

/* Character Conversion Functions */

char	tc_get_digitchar(uintg i);		// Get the digit character that corresponds to a give unsigned integer. If the integer is out of range, # is returned
char	tc_get_hexchar(uintg i);		// Get the hexadecimal character that corresponds to a give unsigned integer. If the integer is out of range, # is returned
char	tc_get_base64char(uintg i);		// Get the MIME-standard base64 character that corresponds to a give unsigned integer. If the integer is out of range, # is returned

uint8	tc_get_digitval(char c);		// Get the integer equivalent of a given digit character . If the character is not a digit, 255 is returned
uint8	tc_get_hexval(char c);			// Get the integer equivalent of a given hexadecimal character . If the character is not a hexadecimal character, 255 is returned
uint8	tc_get_base64val(char c);		// Get the integer equivalent of a given MIME-standard base64 character . If the character is not a MIME-standard base64 character, 255 is returned

// C++ Compatibility
#ifdef __cplusplus
} //extern "C"
#endif

#endif //#ifndef _THOTH_COM_STR_CHAR_H
