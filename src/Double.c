#include "Double.h"

void copyDouble (void *a, void*b)
{
	int *buffer = (int *)a;
	int *object = (int *)b;

	*buffer = *object;
}