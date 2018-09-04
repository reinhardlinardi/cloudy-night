/*
 * Brightsouls
 */

#include <stdlib.h>
#include <assert.h>

#include "String.h"


#define String_SpareSize      (16)

#define String_Buffer(str)    (str)->buf
#define String_Capacity(str)  (str)->cap


size_t
_CStr_Len (const char*  str)
{
	assert (str != NULL);

	size_t n = 0;

	while (*str++ != '\0')
		n++;

	return n;
}

static bool
_CStr_IsEqual (const char*  str_a,
               const char*  str_b,
               size_t       len)
{
	assert (str_a != NULL);
	assert (str_b != NULL);

	bool loop = true;

	while (loop && len)
	{
		if (*str_a++ == *str_b++)
			len--;
		else
			loop = false;
	}

	return loop;
}

static void
_CStr_Copy (char*        dest,
            const char*  src,
            size_t       len)
{
	assert (dest != NULL);
	assert (src != NULL);

	size_t i = len;
	while (i--) *dest++ = *src++;
}

static void
_String_Prepare (String*  self,
                 size_t   len)
{
	assert (self != NULL);

	String_Length(self) = len;

	if (len > String_Capacity(self))
	{
		size_t cap = ((len + 3) & ~((size_t) 3)) + String_SpareSize;
		char* buff = (char*) realloc (String_Buffer(self), sizeof (char) * cap);

		String_Buffer(self) = buff;
		String_Capacity(self) = cap;
	}
}


// Constructor

void
String_Create (String*  self)
{
	assert (self != NULL);

	String_Buffer(self) = NULL;
	String_Length(self) = 0;
	String_Capacity(self) = 0;
}

void
String_CreateFromCStr (String*      self,
                       const char*  cstr)
{
	assert (self != NULL);
	assert (cstr != NULL);

	String_Create (self);
	String_AppendCStr (self, cstr);
}


// Traits

bool
String_IsEqual (String*        self,
                const String*  pair)
{
	assert (self != NULL);
	assert (pair != NULL);

	size_t l = String_Length(self);
	bool ret = String_Length(pair) == l;

	if (ret && (l != 0))
		ret = _CStr_IsEqual (String_Buffer(self), String_Buffer(pair), l);

	return ret;
}

bool
String_IsEqualCStr (String*      self,
                    const char*  cstr)
{
	assert (self != NULL);
	assert (cstr != NULL);

	size_t l = String_Length(self);
	bool ret = _CStr_Len(cstr) == l;

	if (ret && (l != 0))
		_CStr_IsEqual (String_Buffer(self), cstr, l);

	return ret;
}


// Admin

void
String_Append (String*        self,
               const String*  pair)
{
	assert (self != NULL);
	assert (pair != NULL);

	size_t self_len = String_Length(self);
	size_t pair_len = String_Length(pair);

	_String_Prepare (self, self_len + pair_len);
	_CStr_Copy (String_Buffer(self) + self_len, String_Buffer(pair), pair_len);
}

void
String_AppendCStr (String*      self,
                   const char*  cstr)
{
	assert (self != NULL);
	assert (cstr != NULL);

	size_t self_len = String_Length(self);
	size_t cstr_len = _CStr_Len(cstr);

	_String_Prepare (self, self_len + cstr_len);
	_CStr_Copy (String_Buffer(self) + self_len, cstr, cstr_len);
}

void
String_AppendChar (String*  self,
                   char     ch)
{
	assert (self != NULL);

	size_t self_len = String_Length(self);

	_String_Prepare (self, self_len + 1);
	String_Char(self, self_len) = ch;
}


// Export

char*
String_Peek (String*  self)
{
	assert (self != NULL);

	size_t len = String_Length(self);

	char* buf = (char*) realloc (String_Buffer(self), len + 1);
	buf[len] = '\0';

	return buf;
}

char*
String_Eject (String*  self)
{
	assert (self != NULL);

	char* buf = String_Peek (self);

	String_Create (self);

	return buf;
}
