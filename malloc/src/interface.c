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

struct blk_meta *get_next(struct blk_meta *head, size_t size)
{
    struct blk_meta *next = (struct blk_meta *)((size_t)head + size);
    next->size = head->size - size;
    next->prev = head;
    next->next = head->next;
    next->status = -1;

    return next;
}

void *first_fit(size_t size)
{
    struct blk_meta *head = meta;
    struct blk_meta *tmpptr = meta;
    struct blk_meta *next = NULL;

    size = align_long_double(size + sizeof(struct blk_meta));

    for (; head != NULL; head = head->next)
    {
        // if free block
        if (head->status == -1 && size < head->size)
        {
            // Set next bloc
            next = get_next(head, size);

            head->status = 1;
            head->next = next;
            head->size = size - sizeof(struct blk_meta);
            return head->data;
        }

        tmpptr = head;
    }

    // if no bloc is suitable we allocate a new block;
    head = blka_alloc(size);
    if (!head)
        return NULL;

    size = align_long_double(size);
    next = get_next(head, size);

    tmpptr->next = head;

    head->next = NULL;
    head->prev = tmpptr;
    head->size = size - sizeof(struct blk_meta);
    head->status = 1;

    return head->data;
}

__attribute__((visibility("default"))) void *my_malloc(size_t size)
{
    if (!meta)
    {
        meta = blka_alloc(size);
        if (!meta)
            return NULL;
    }

    return first_fit(size);
}

__attribute__((visibility("default"))) void my_free(void *ptr)
{
    if (!ptr)
        return;

    struct blk_meta *head = ptr;
    head->status = -1;

    // free page if nothing inside except the bloc ptr
    if (head->next == NULL)
        blka_free(head);
}

void copy_data(struct blk_meta *base, struct blk_meta *dest, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        dest->data[i] = base->data[i];
}

__attribute__((visibility("default"))) void *my_realloc(void *ptr, size_t size)
{
    if (!ptr)
        return my_malloc(size);

    if (size == 0)
    {
        my_free(ptr);
        return ptr;
    }

    struct blk_meta *head = meta;
    size = align_long_double(size + sizeof(struct blk_meta));

    for (; head != NULL; head = head->next)
    {
        // if free block
        if (head->status == -1 && size < head->size)
        {
            copy_data(ptr, head, size);
            my_free(ptr);
        }
    }

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
    if (len == 0)
        return NULL;

    char *ptr = my_malloc(len);

    for (size_t i = 0; i < len; i++)
        ptr[i] = 0;

    return ptr;
}
