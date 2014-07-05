#include "Double.h"

void copyDouble (void *a, void*b)
{
	double *buffer = (double *)a;
	double *object = (double *)b;

	*buffer = *object;
}