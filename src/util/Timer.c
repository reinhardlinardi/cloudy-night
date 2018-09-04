/*
 * Brightsouls
 */

#include <assert.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

#include "Timer.h"


#define SEC_NSEC   (1000000000)
#define USEC_NSEC  (1000)


static void
_Timer_Normalize (Timer*  self)
{
	assert (self != NULL);

	if (Timer_NSec(self) >= SEC_NSEC)
	{
		Timer_Sec(self) += Timer_NSec(self) / SEC_NSEC;
		Timer_NSec(self) = Timer_NSec(self) % SEC_NSEC;
	}
}


// Constructors

void
Timer_Create (Timer*  self)
{
	assert (self != NULL);

	Timer_Sec(self)  = 0;
	Timer_NSec(self) = 0;
}

void
Timer_CreateFromSystem (Timer*  self)
{
	assert (self != NULL);

	Timer_Create (self);
}

void
Timer_CreateFromTimespec (Timer*                  self,
                          const struct timespec*  ts)
{
	assert (self != NULL);
	assert (ts != NULL);

	Timer_Sec(self)  = ts->tv_sec;
	Timer_NSec(self) = ts->tv_nsec;

	_Timer_Normalize(self);
}


// Export

void
Timer_ToTimespec (const Timer*      self,
                  struct timespec*  ts)
{
	assert (self != NULL);
	assert (ts != NULL);

	ts->tv_sec  = Timer_Sec(self);
	ts->tv_nsec = Timer_NSec(self);
}

void
Timer_ToTimeval (const Timer*     self,
                 struct timeval*  tv)
{
	assert (self != NULL);
	assert (tv != NULL);

	tv->tv_sec  = Timer_Sec(self);
	tv->tv_usec = Timer_NSec(self) / USEC_NSEC;
}


// Arithmetics

void
Timer_Substract (Timer*        self,
                 const Timer*  pair)
{
	assert (self != NULL);
	assert (pair != NULL);

	Timer n = *self;

	if (Timer_IsGreater (&n, pair))
	{
		if (Timer_Sec(&n) > Timer_Sec(pair))
		{
			if(Timer_NSec(&n) >= Timer_NSec(pair))
			{
				Timer_NSec(self) = Timer_NSec(&n) - Timer_NSec(pair);
				Timer_Sec(self)  = Timer_Sec(&n) - Timer_Sec(pair);
			}
			else
			{
				Timer_NSec(self) = SEC_NSEC + Timer_NSec(&n) - Timer_NSec(pair);
				Timer_Sec(self)  = (Timer_Sec(&n) - 1) - Timer_Sec(pair);
			}
		}
		else
		{
			Timer_NSec(self) = Timer_NSec(&n) - Timer_NSec(pair);
			Timer_Sec(self)  = 0;
		}
	}
	else
		Timer_Create (self);
}

void
Timer_Add (Timer*        self,
           const Timer*  pair)
{
	assert (self != NULL);
	assert (pair != NULL);

	Timer n = *self;

	Timer_NSec(self) = Timer_NSec(&n) + Timer_NSec(pair);
	Timer_Sec(self)  = Timer_Sec(&n) + Timer_Sec(pair);

	_Timer_Normalize(self);
}


// Traits

bool
Timer_IsEqual (const Timer* self,
               const Timer* pair)
{
	assert (self != NULL);
	assert (pair != NULL);

	return (Timer_Sec(self)  == Timer_Sec(pair))
	    && (Timer_NSec(self) == Timer_NSec(pair));
}

bool
Timer_IsGreater (const Timer*  self,
                 const Timer*  pair)
{
	assert (self != NULL);
	assert (pair != NULL);

	bool out = false;

	if (Timer_Sec(self) > Timer_Sec(pair))
		out = true;
	else
	if ((Timer_Sec(self) == Timer_Sec(pair)) &&
	    (Timer_NSec(self) > Timer_NSec(pair)))
		out = true;

	return out;
}
