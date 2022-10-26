#include "allocator.h"

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

struct blk_allocator *blka_new(void)
{
    struct blk_allocator *blka = malloc(sizeof(struct blk_allocator));
    blka->meta = NULL;

    return blka;
}

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

struct blk_meta *blka_alloc(struct blk_allocator *blka, size_t size)
{
    size_t sizealign = align(size);

    struct blk_meta *meta = mmap(NULL, sizealign, PROT_READ | PROT_WRITE,
                                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (meta == MAP_FAILED)
        return NULL;

    meta->size = sizealign - sizeof(struct blk_allocator);
    meta->next = blka->meta;
    blka->meta = meta;

    return meta;
}

void blka_free(struct blk_meta *blk)
{
    munmap(blk->data, blk->size + sizeof(struct blk_meta));
}

void blka_pop(struct blk_allocator *blka)
{
    if (!blka || !blka->meta)
        return;

    struct blk_meta *head = blka->meta;
    blka->meta = head->next;
    head->next = NULL;

    blka_free(head);
}

void blka_delete(struct blk_allocator *blka)
{
    if (!blka)
        return;

    struct blk_meta *head = blka->meta;

    for (; blka->meta;)
    {
        head = blka->meta;
        blka->meta = blka->meta->next;
        blka_free(head);
    }

    free(blka);
}
