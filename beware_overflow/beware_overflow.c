#include "beware_overflow.h"

void *beware_overflow(void *ptr, size_t nmemb, size_t size)
{
    size_t offset = nmemb * size;
    if (__builtin_umull_overflow(nmemb, size, &offset))
        return NULL;

    char *ptr2 = ptr;

    return ptr2 + offset;
}
