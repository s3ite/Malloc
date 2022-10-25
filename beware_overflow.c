#include "beware_overflow.h"

void *beware_overflow(void *ptr, size_t nmemb, size_t size)
{
    int hasoverflow = __builtin_umull_overflow(nmemb, size, ptr);
    return hasoverflow == 0 ? ptr : NULL;
}