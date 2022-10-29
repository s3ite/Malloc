#include "../src/malloc.h"

void testmalloc1(int val1, int val2)
{
    char *array = my_malloc(val1);
    char *array2 = my_malloc(val1);
    char *array3 = my_malloc(val1);

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array + i, array[i]);

    printf("\n%s\n\n", "================");

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array2 + i, array2[i]);

    printf("\n%s\n\n", "================");

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array3 + i, array3[i]);

    printf("\n%s\n\n", "================");

    size_t diff = (size_t)array3 - (size_t)array;
    printf("%ld\n", diff);
}

void *testmalloc2(int val1, char c)
{
    char *array = my_malloc(val1);
    for (int i = 0; i < val1; i++)
        array[i] = c;

    for (int i = 0; i < 20; i++)
        printf("%p : [%c]\n", array + i, array[i]);

    printf("\n%s\n\n", "================");

    return array;
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void testcalloc1(int val1, int val2)
{
    char *array = my_calloc(val1, val2);
    char *array2 = my_calloc(val1, val2);
    char *array3 = my_calloc(val1, val2);

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array + i, array[i]);

    printf("\n%s\n\n", "================");

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array2 + i, array2[i]);

    printf("\n%s\n\n", "================");

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array3 + i, array3[i]);

    printf("\n%s\n\n", "================");

    size_t diff = (size_t)array3 - (size_t)array;
    printf("%ld\n", diff);
}

void *testcalloc2(int val1, int val2)
{
    char *array = my_calloc(val1, val2);

    for (int i = 0; i < 20; i++)
        printf("%p : [%c]\n", array + i, array[i]);

    printf("\n%s\n\n", "================");

    return array;
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void testrealloc1(int val1, int val2)
{
    char *array = my_calloc(val1, val2);
    char *array2 = my_calloc(val1, val2);
    char *array3 = my_calloc(val1, val2);

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array + i, array[i]);

    printf("\n%s\n\n", "================");

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array2 + i, array2[i]);

    printf("\n%s\n\n", "================");

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array3 + i, array3[i]);

    printf("\n%s\n\n", "================");

    size_t diff = (size_t)array3 - (size_t)array;
    printf("%ld\n", diff);
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

int main(int argc, char const *argv[])
{
    /*
    int val1 = atoi(argv[1]);

    void *t1 = testmalloc2(val1, '#');
    void *t2 = testmalloc2(val1, '%');
    my_free(t1);
    
    char *t3 = my_realloc(t2, val1);

    for (int i = 0; i < val1; i++)
        printf("%p : [%c]\n", t3+i, t3[i]);

    char *t4 = my_calloc(val1-1, 1);
    for (int i = 0; i < val1; i++)
        printf("%p : [%c]\n", t4+i, t4[i]);

    void *init = my_malloc(val1);
    printf("%p\n", init);

    my_free(init);
    void *fin = my_malloc(val1);
    printf("%p\n", fin);

    char *array = my_calloc(val1-1, 1);
    printf("%p\n", array);

    for (int i = 0; i < 20; i++)
        printf("%p : [%d]\n", array + i, array[i]);
    */
    
    (void)argv;
    (void)argc;
}
