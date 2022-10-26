#include "allocator.h"
#include <stdlib.h>
#include <sys/mman.h>

struct blk_allocator *blka_new(void)
{
	struct blk_alloccator *blka = malloc(sizeof(struct blk_allocator));
	struct blk_meta *meta = malloc(sizeof(struct blk_meta));

	meta->next = NULL;
	meta->data = NULL;
	meta->size = 0;

	blka->meta = meta;

	return blka;
}

struct blk_meta *blka_alloc(struct blk_allocator *blka, size_t size)
{
	void *addr = mmap(NULL, size,  PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (addr == MAP_FAILED)
		return NULL;

	struct blk_meta *meta = blka->meta;
	meta->data = addr;
	meta->size = size - sizeof(struct blk_meta);
	meta->next = NULL;

	return meta;
}

void blka_free(struct blk_meta *blk)
{
	munmap(blk->data, blk->size);

}

void blka_pop(struct blk_allocator *blka)
{
	struct blk_meta *head = blka->meta;
	blka->meta = head->next;
	head->next = NULL;

	blka_free(head);
}

void blka_delete(struct blk_allocator *blka)
{
	struct blk_meta *head = blka->meta;

	for(; blka->meta;)
	{
		head = blka->meta;
		blka->meta = blka->meta->next;
		free(head);
	}

	free(blka);
}