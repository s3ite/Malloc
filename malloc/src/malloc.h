#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
//=====================================ALLOCATION===============================
struct blk_meta
{
    struct blk_meta *next;
    struct blk_meta *prev;

    // -1 == free && 1 == busy
    int status;
    size_t size;
    char data[];
};

void blka_delete(struct blk_meta *blka);

struct blk_meta *blka_alloc(size_t size);
void blka_free(struct blk_meta *blk);
void blka_pop(struct blk_meta *blka);

//====================================CORE=====================================

__attribute__((visibility("default"))) void *malloc(size_t size);
__attribute__((visibility("default"))) void free(void *ptr);
__attribute__((visibility("default"))) void *realloc(void *ptr, size_t size);
__attribute__((visibility("default"))) void *calloc(size_t nmemb, size_t size);

__attribute__((visibility("default"))) void *my_malloc(size_t size);
__attribute__((visibility("default"))) void my_free(void *ptr);
__attribute__((visibility("default"))) void *my_realloc(void *ptr, size_t size);
__attribute__((visibility("default"))) void *my_calloc(size_t nmemb, size_t size);

#endif /* MALLOC_H */
