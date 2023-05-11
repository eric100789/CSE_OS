#include "mm.h"

struct header 
{
    unsigned int size;
    unsigned int free;
    struct header *next;
};
typedef header Header;

static void *Base = NULL;

static Header* get_memory(Header *last, unsigned int size)
{	
    void *begin = sbrk(0);
    Header *reqmem = (Header *) sbrk(sizeof(Header) + size);
    if(!reqmem)
    {
        printf("ERROR!");
        return NULL;
    }
    if(last == NULL)
    {
        last = reqmem;
    }
    reqmem->size = size;
    reqmem->free = 0;
    reqmem->next = NULL;
    return reqmem;
}

static void *find_space(unsigned int size)
{
    Header *current = (Header*)Base;
    while(current->next)
    {
        if(current->size>=size && current->free == 1)
        {
            return current;
        }
        current = current->next;
    }
    return current;
}

void* mymalloc(unsigned nbytes)
{
    Header *reqmem;
    if(!Base)
    {
        reqmem = get_memory(NULL, nbytes);
        Base = reqmem;
    }
    else
    {
        Header *newmem = (Header*) find_space(nbytes);
        
        if(newmem->next == NULL)
        { 
            reqmem = get_memory(newmem, nbytes);
            newmem->next = reqmem; 
        }
        else
        { 
            newmem->size = nbytes;
            newmem->free = 0;
            reqmem = newmem;
        }
    }
    
    return reqmem+1;
}

void* mycalloc(unsigned nmemb, unsigned size)
{
	void *ptr = mymalloc(nmemb * size);
	if (ptr != NULL) 
	{	
		memset(ptr, 0, nmemb * size);
	}
	return ptr;
}

void* myrealloc(void * ptr, unsigned size)
{
	if (ptr == NULL) return mymalloc(sizeof(size));
	if (size == 0)
	{
		myfree(ptr);
		return NULL;
	}
	Header *p = (Header *)ptr - 1;
	unsigned n = (p->size - 1) * sizeof(Header);
	void *temp = mymalloc(size);
	if (n < size) memcpy(temp, ptr, size);
	else memcpy(temp, ptr, size);
	myfree(ptr);
	return temp;					
}

void myfree(void *ptr)
{
    if(ptr == NULL) return;
    Header *h = (Header *)ptr-1;
    h->free = 1;
}

