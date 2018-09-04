/*
 * Brightsouls
 */

#pragma once

#include <stdbool.h>
#include <stdlib.h>


// Structure

typedef List     Stack;
typedef ListElmt StackElmt;


// Selector

#define Stack_Top(self)   List_First(self)


// Allocation

void
StackElmt_Alloc (StackElmt*  elmt);

void
StackElmt_Clean (StackElmt**  elmt_var);


// Constructor

void
Stack_Create (Stack*  self);


// Traits

bool
Stack_IsEmpty (Stack*  self);


// Admin

void
Stack_Push (Stack*      self,
            StackElmt*  elmt);

void
Stack_Pop (Stack*       self,
           StackElmt**  elmt_var);
