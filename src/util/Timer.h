/* File : Timer.h */
/* Tanggal : 10 November 2016 */

#pragma once

#include <stdbool.h>
#include <sys/time.h>
#include <time.h>


// Structure

typedef struct _Timer Timer;

struct _Timer
{
	time_t sec;  /* Seconds */
	long n_sec;  /* Nanoseconds */

};


// Selectors

#define Timer_Sec(dt)   (dt)->sec
#define Timer_NSec(dt)  (dt)->n_sec


// Constructor

void
Timer_Create (Timer*  self);

void
Timer_CreateFromSystem (Timer*  self);

void
Timer_CreateFromTimespec (Timer*                  self,
                          const struct timespec*  ts);


// Export

void
Timer_ToTimespec (const Timer*      self,
                  struct timespec*  ts);

void
Timer_ToTimeval (const Timer*     self,
                 struct timeval*  tv);


// Arithmetics

void
Timer_Substract (Timer*        self,
                 const Timer*  pair);

void
Timer_Add (Timer*        self,
           const Timer*  pair);


// Traits

bool
Timer_IsEqual (const Timer*  self,
               const Timer*  pair);

bool
Timer_IsGreater (const Timer*  self,
                 const Timer*  pair);
