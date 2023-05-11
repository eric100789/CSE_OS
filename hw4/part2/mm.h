#ifndef __MY_MM_H_INCLUDED__
#define __MY_MM_H_INCLUDED__

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void* mymalloc(unsigned size);
void* mycalloc(unsigned nmemb, unsigned size);
void* myrealloc(void *ptr, unsigned size);
void myfree(void *ptr);

#endif
