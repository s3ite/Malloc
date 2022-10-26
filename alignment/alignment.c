#include "alignment.h"

size_t align(size_t size)
{
    if (size % sizeof(long double) == 0)
        return size;

    size_t addition;

    if (_builtin_add_overflow(size, sizeof(long double), &addition))
        return 0;

    addition -= size % sizeof(long double);

    return addidtion;
}
