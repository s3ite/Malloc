#include "malloc.h"

size_t align(size_t size)
{
    if (size == 0)
        return sysconf(_SC_PAGESIZE);

    if (size % sysconf(_SC_PAGESIZE) == 0)
        return size;

    size_t addition;

    if (__builtin_add_overflow(size, sysconf(_SC_PAGESIZE), &addition))
        return 0;

    addition -= size % sysconf(_SC_PAGESIZE);

    return addition;
}

struct blk_meta *blka_alloc(size_t size)
{
    size_t sizealign = align(size);

    struct blk_meta *meta = mmap(NULL, sizealign, PROT_READ | PROT_WRITE,
                                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (meta == MAP_FAILED)
        return NULL;

    meta->size = sizealign - sizeof(struct blk_meta);
    meta->next = NULL;
    meta->prev = NULL;
    meta->status = -1;

    return meta;
}

void blka_free(struct blk_meta *blk)
{
    munmap(blk->data, blk->size + sizeof(struct blk_meta));
}

void blka_pop(struct blk_meta *blka)
{
    if (!blka || !blka)
        return;

    struct blk_meta *head = blka;
    blka = head->next;
    head->next = NULL;

    blka_free(head);
}

void blka_delete(struct blk_meta *blka)
{
    if (!blka)
        return;

    struct blk_meta *head = blka;

    for (; blka;)
    {
        head = blka;
        blka = blka->next;
        blka_free(head);
    }
}
