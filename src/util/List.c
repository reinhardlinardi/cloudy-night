#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <stdbool.h>

#include "List.h"


#define List_ElmtSize(list)  (list)->elmt_size

// Constructor

void
List_Create (List*   self,
             size_t  elmt_size)
{
	assert (self != NULL);

	List_Last(self) = NULL;
	List_First(self) = NULL;

	List_ElmtSize(self) = elmt_size;
}


// Allocation

ListElmt*
ListElmt_Alloc (List*  self)
{
	assert (self != NULL);

	size_t payload = List_ElmtSize(self);
	ListElmt* mem = (ListElmt*) malloc (sizeof (ListElmt) + payload);

	ListElmt_Prev(mem) = NULL;
	ListElmt_Next(mem) = NULL;

	return mem;
}

void
ListElmt_Clean (ListElmt**  self_var)
{
	assert (self_var != NULL);

	free (*self_var);
	*self_var = NULL;
}


// Traits

bool
List_IsEmpty (List*  self)
{
	assert (self != NULL);

	return (List_Last(self) == NULL)
	    && (List_First(self) == NULL);
}

size_t
List_Count (List*  self)
{
	assert (self != NULL);

	ListElmt* i = List_First(self);
	size_t n = 0;

	for (; i != NULL; i = ListElmt_Next(i))
		n++;

	return n;
}


// Lookup

ListElmt*
List_Search (List*           self,
			 ListSearchHook  hook,
			 void*           ptr)
{
	assert (self != NULL);
	assert (hook != NULL);

	ListElmt* p = List_First(self);

	while ((p != NULL) && !hook (ListElmt_Mem(p), ptr))
		p = ListElmt_Next(p);

	return p;
}


// Add by Element

void
List_InsertFirst (List*      self,
                  ListElmt*  elmt)
{
	assert (self != NULL);
	assert (elmt != NULL);

	if (List_IsEmpty (self))
	{
		ListElmt* q = elmt;

		while (ListElmt_Next(q) != NULL)
			q = ListElmt_Next(q);

		List_Last(self) = q;
		List_First(self) = elmt;
	}
	else
		List_InsertBefore (self, elmt, List_First(self));
}

void
List_InsertLast (List*      self,
                 ListElmt*  elmt)
{
	assert (self != NULL);
	assert (elmt != NULL);

	if (List_IsEmpty (self))
		List_InsertFirst (self, elmt);
	else
		List_InsertAfter (self, elmt, List_Last(self));
}

void
List_InsertAfter (List*      self,
                  ListElmt*  elmt,
                  ListElmt*  elmt_prec)
{
	assert (self != NULL);
	assert (elmt != NULL);
	assert (elmt_prec != NULL);

	ListElmt* q = elmt;

	while (ListElmt_Next(q) != NULL)
		q = ListElmt_Next(q);

	ListElmt* n = ListElmt_Next(elmt_prec);

	ListElmt_Prev(elmt) = elmt_prec;
	ListElmt_Next(q) = n;
	ListElmt_Next(elmt_prec) = elmt;

	if (n == NULL)
		List_Last(self) = q;
	else
		ListElmt_Prev(n) = q;
}

void
List_InsertBefore (List*      self,
                   ListElmt*  elmt,
                   ListElmt*  elmt_succ)
{
	assert (self != NULL);
	assert (elmt != NULL);
	assert (elmt_succ != NULL);

	ListElmt* Q = elmt;

	while (ListElmt_Next(Q) != NULL)
		Q = ListElmt_Next(Q);

	ListElmt* b = ListElmt_Prev(elmt_succ);

	ListElmt_Prev(elmt) = b;
	ListElmt_Next(Q) = elmt_succ;
	ListElmt_Prev(elmt_succ) = Q;

	if (b == NULL)
		List_First(self) = elmt;
	else
		ListElmt_Next(b) = elmt;
}

// Delete by Element

void
List_DelFirst (List*       self,
               ListElmt**  elmt)
{
	assert (self != NULL);
	assert (elmt != NULL);
	assert (!List_IsEmpty (self));

	*elmt = List_First(self);

	if (List_First(self) == List_Last(self))
	{
		List_Last(self) = NULL;
		List_First(self) = NULL;

		ListElmt_Prev(*elmt) = NULL;
		ListElmt_Next(*elmt) = NULL;
	}
	else
		List_DelBefore (self, elmt, ListElmt_Next(*elmt));
}

void
List_DelLast (List*       self,
              ListElmt**  elmt)
{
	assert (self != NULL);
	assert (elmt != NULL);
	assert (!List_IsEmpty (self));

	*elmt = List_Last(self);

	if (List_First(self) == List_Last(self))
		List_DelFirst (self, elmt);
	else
		List_DelAfter (self, elmt, ListElmt_Prev(*elmt));
}

void
List_Del (List*      self,
          ListElmt*  elmt)
{
	assert (self != NULL);
	assert (elmt != NULL);

	if (ListElmt_Next(elmt) != NULL)
		List_DelBefore (self, &elmt, ListElmt_Next(elmt));
	else
	if (ListElmt_Prev(elmt) != NULL)
		List_DelAfter (self, &elmt, ListElmt_Prev(elmt));
	else
		List_DelFirst (self, &elmt);
}

void
List_DelAfter (List*       self,
               ListElmt**  elmt_var,
			   ListElmt*   elmt_prec)
{
	assert (self != NULL);
	assert (elmt_var != NULL);
	assert (elmt_prec != NULL);

	*elmt_var = ListElmt_Next(elmt_prec);

	assert (*elmt_var != NULL);

	ListElmt* n = ListElmt_Next(*elmt_var);

	ListElmt_Next(elmt_prec) = n;

	if (n == NULL)
		List_Last(self) = elmt_prec;
	else
		ListElmt_Prev(n) = elmt_prec;

	ListElmt_Prev(*elmt_var) = NULL;
	ListElmt_Next(*elmt_var) = NULL;
}

void
List_DelBefore (List*       self,
                ListElmt**  elmt_var,
                ListElmt*   elmt_succ)
{
	assert (self != NULL);
	assert (elmt_var != NULL);
	assert (elmt_succ != NULL);

	*elmt_var = ListElmt_Prev(elmt_succ);

	assert (*elmt_var != NULL);

	ListElmt* b = ListElmt_Prev(*elmt_var);

	ListElmt_Prev(elmt_succ) = b;

	if (b == NULL)
		List_First(self) = elmt_succ;
	else
		ListElmt_Next(b) = elmt_succ;

	ListElmt_Prev(*elmt_var) = NULL;
	ListElmt_Next(*elmt_var) = NULL;
}
