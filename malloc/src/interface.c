#include "malloc.h"
struct blk_meta *meta = NULL;

size_t align_long_double(size_t size)
{
    if (size == 0)
        return sysconf(size);

    if (size % sizeof(long double) == 0)
        return size;

    size_t addition;

    if (__builtin_add_overflow(size, sizeof(long double), &addition))
        return 0;

    addition -= size % sizeof(long double);

    return addition;
}

void *first_fit(struct blk_meta *meta, size_t size)
{
    struct blk_meta *head = meta;

    for (; head; head = head->next)
    {
        // if free block
        if (head->status == -1 && size < head->size)
        {
            size = align_long_double(size + sizeof(struct blk_meta));
            // Set next bloc
            void *tmp = head;
            struct blk_meta *next = (struct blk_meta*)((size_t)tmp + size);

            
            next->size = head->size - size;
            next->prev = head;
            next->status = -1;
            
            head->status = 1;
            head->next = next;
            head->size = size - sizeof(struct blk_meta);
            return head;
        }
    }

    return NULL;
}

__attribute__((visibility("default"))) void *my_malloc(size_t size)
{
    if (!meta)
    {
        meta = blka_alloc(size);
        if (!meta)
            return NULL;
    }

    return first_fit(meta, size);
}

__attribute__((visibility("default"))) void my_free(void *ptr)
{
    struct blk_meta *head = ptr;
    head->status = -1;

    // free page if nothing inside except the bloc ptr
    struct blk_meta *tmp;

    for (; head;)
    {
        tmp = head;
        head = head->next;

        blka_free(tmp);
    }
}

__attribute__((visibility("default"))) void *my_realloc(void *ptr, size_t size)
{
    if (!ptr)
        return NULL;

    struct blk_meta *head = meta;

    for (; head; head = head->next)
    {}

    (void)ptr;
    (void)size;

    return NULL;
}

__attribute__((visibility("default"))) void *my_calloc(size_t nmemb,
                                                       size_t size)
{
    size_t offset = 0;
    if (__builtin_umull_overflow(nmemb, size, &offset))
        return NULL;

    size_t len = nmemb * size;
    char *ptr = my_malloc(len);

    for (size_t i = 0; i < len; i++)
        ptr[i] = '0';

    return ptr;
}