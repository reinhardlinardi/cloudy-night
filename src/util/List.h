/*
 * Brightsouls
 */

#pragma once

#include <stdbool.h>
#include <stdlib.h>


// Virtuals

typedef bool (*ListSearchHook) (void* mem, void *ptr);


// Structure

typedef struct _List List;
typedef struct _ListElmt ListElmt;

struct _List
{
	ListElmt*  first;
	ListElmt*  last;

	size_t     elmt_size;
};

struct _ListElmt
{
	ListElmt*  next;
	ListElmt*  prev;
};


// Selectors

#define List_First(list)  (list)->first
#define List_Last(list)   (list)->last

#define ListElmt_Prev(elmt)  (elmt)->prev
#define ListElmt_Next(elmt)  (elmt)->next

#define ListElmt_Mem(elmt)        (void*)(elmt + 1)
#define ListElmt_Val(elmt, type)  *((type*)ListElmt_Mem(elmt))


// Constructor

/**
 * Initialize new List.
 */
void
List_Create (List*   self,
             size_t  elmt_size);


// Allocation

/**
 * Allocate new ListElmt.
 */
ListElmt*
ListElmt_Alloc (List*  self);

/**
 * Deallocate ListElmt and clean.
 */
void
ListElmt_Clean (ListElmt** self_var);


// Traits

/**
 * Check for emptiness of the List.
 */
bool
List_IsEmpty (List*  self);

/**
 * Count elements in the List.
 */
size_t
List_Count (List*  self);


// Lookup

/**
 * Search for first element which met the given preconditions.
 */
ListElmt*
List_Search (List*           self,
             ListSearchHook  hook,
             void*           ptr);


// Add by Element

/**
 * Add element at first position of List.
 */
void
List_InsertFirst (List*      self,
                  ListElmt*  elmt);

/**
 * Add element at last position of List.
 */
void
List_InsertLast (List*      self,
                 ListElmt*  elmt);

/**
 * Add element before given element.
 */
void
List_InsertBefore (List*      self,
                   ListElmt*  elmt,
                   ListElmt*  elmt_pred);

/**
 * Add element after given element.
 */
void
List_InsertAfter (List*      self,
                  ListElmt*  elmt,
                  ListElmt*  elmt_succ);


// Delete by Element

/**
 * Delete given element in List.
 */
void
List_Del (List*      self,
          ListElmt*  elmt);

/**
 * Delete first element of List.
 */
void
List_DelFirst (List*       self,
               ListElmt**  elmt_var);

/**
 * Delete last element of List.
 */
void
List_DelLast (List*       self,
              ListElmt**  elmt_var);

/**
 * Delete element before given eleent from List.
 */
void
List_DelBefore (List*       self,
                ListElmt**  elmt_var,
                ListElmt*   elmt_pred);

/**
 * Delete element after given eleent from List.
 */
void
List_DelAfter (List*       self,
               ListElmt**  elmt_var,
               ListElmt*   elmt_succ);
