#include "page_begin.h"

void *page_begin(void *ptr, size_t page_size)
{
    char *tmp = NULL;

    size_t page_begin = (size_t)ptr & (~(page_size - 1));
    return tmp + page_begin;
}
