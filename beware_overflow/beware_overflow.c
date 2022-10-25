#include "beware_overflow.h"

void *beware_overflow(void *ptr, size_t nmemb, size_t size)
{
    return __builtin_umull_overflow(nmemb, size, ptr) ? NULL : ptr;
}
