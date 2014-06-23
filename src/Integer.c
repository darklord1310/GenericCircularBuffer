#include "Integer.h"
#include <stdio.h>

void copyInt (void *a, void*b)
{
	int *buffer = (int *)a;
	int *object = (int *)b;
	*buffer = *object;
}