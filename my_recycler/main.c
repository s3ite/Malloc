#include "recycler.h"


int main(void)
{
	
	struct recycler *recycler = recycler_create(32, 1024);
	free(recycler);
	return 0;
}