#include "../src/malloc.h"

void testmalloc1(int val1, int val2)
{
    char *array = my_malloc(val1);

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array + i, array[i]); 
}

void testcalloc1(int val1, int val2)
{
    char *array2 = my_calloc(val1, 2);

    for (int i = 0; i < val2; i++)
        printf("%p : [%d]\n", array2 + i, array2[i]); 
}


int main(int argc, char const *argv[])
{
    int val1 = atoi(argv[1]);
    int val2 = atoi(argv[2]);

    testcalloc1(val1, val2);
    (void) argc;
}