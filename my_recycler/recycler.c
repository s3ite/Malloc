#include "recycler.h"

struct recycler *recycler_create(size_t block_size, size_t total_size)
{
    if (block_size == 0 || total_size == 0
        || block_size % (sizeof(size_t)) != 0)
        return NULL;

    struct recycler *newrecycler = malloc(sizeof(struct recycler));
    if (!newrecycler)
        return NULL;

    newrecycler->block_size = block_size;
    newrecycler->capacity = total_size / block_size;
    newrecycler->chunk = malloc(total_size);

    if (!newrecycler->chunk)
        return NULL;

    char *chunk = newrecycler->chunk;

    newrecycler->free = chunk;
    struct free_list *freeptr = newrecycler->free;
    freeptr->next = NULL;

    char *address_max = total_size + chunk;

    for (char *i = chunk + block_size; i < address_max; i += block_size)
    {
        void *tmp = i;
        struct free_list *newelt = tmp;
        newelt->next = freeptr;
        freeptr = newelt;
    }

    return newrecycler;
}

void recycler_destroy(struct recycler *r)
{
    if (!r)
        return;

    free(r->chunk);
    free(r);
}

void *recycler_allocate(struct recycler *r)
{
    if (!r || !(r->free))
        return NULL;

    struct free_list *list = r->free;
    struct free_list *head = list;
    list = list->next;
    head->next = NULL;
    return head;
}

void recycler_free(struct recycler *r, void *block)
{
    if (!r || !block)
        return;

    struct free_list *blockr = block;
    blockr->next = r->free;
    r->free = blockr;
}
