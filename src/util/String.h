/*
 * Brightsouls
 */

#pragma once

#include <stdbool.h>
#include <stdlib.h>


// Structure

typedef struct _String String;

struct _String
{
	char*  buf;

	size_t cap;
	size_t len;
};


// Selector

/**
 * Get/set length of String.
 */
#define String_Length(str)    (str)->len

/**
 * Get/set single character in String.
 */
#define String_Char(str, n)   (str)->buf[n]


// Constructor

/**
 * Create an empty String.
 */
void
String_Create (String*  self);

/**
 * Create String from C-string.
 */
void
String_CreateFromCStr (String*      self,
                       const char*  buf);


// Traits

/**
 * Check if two String is equal.
 */
bool
String_IsEqual (String*        self,
                const String*  pair);

/**
 * Check if String is equal with C-string.
 */
bool
String_IsEqualCStr (String*      self,
                    const char*  pair);


// Admin

/**
 * Append other String to String.
 */
void
String_Append (String*        self,
               const String*  pair);

/**
 * Append C-string to String.
 */
void
String_AppendCStr (String*      self,
                   const char*  pair);

/**
 * Append single character to String.
 */
void
String_AppendChar (String*  self,
                   char     ch);


// Export

/**
 * Pack and peek String buffer.
 */
char*
String_Peek (String*  self);

/**
 * Release String buffer.
 */
char*
String_Eject (String*  self);
