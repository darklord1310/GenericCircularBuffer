#include "GenericCircularBuffer.h"
#include <stdio.h>
#include <malloc.h>
#include <CException.h>
#include "Integer.h"
#include "Double.h"

/*
 * Initialize the circularbuffer
 *
 *Input :
 *					length is the length of the buffer
 *					sizeofType is the size of the variable type
 */
CircularBuffer *circularBufferNew(int length, int sizeofType)
{
	CircularBuffer *circularBuffer;
	circularBuffer = malloc(sizeof(CircularBuffer));
	circularBuffer->length = length;
	circularBuffer->size = 0;
	circularBuffer->sizeofType = sizeofType;
	circularBuffer->head=circularBuffer->buffer=circularBuffer->tail=malloc(sizeofType * length);
	
	return circularBuffer;
}


/*
 *	To free the buffer memory
 */
void circularBufferDel(CircularBuffer *circularBuffer)
{
	free(circularBuffer);
}



/*
 * Add a new value into the circular buffer
 *
 *Input :
 *					Pointer cb is the pointer which pointed to the CircularBuffer structure
 *					valueToAdd is the pointer pointed to the value which to be added into the CircularBuffer
 *					copy is a function pointer which point to the copyInt function
 * Error checking:
 *					will throw error when trying to add if the circular buffer is full
 */
void circularBufferAdd(CircularBuffer *cb, void *objectToAdd, void(*copy)(void*,void*))
{
	
	if( cb->size == cb->length)    		   // If size equals to length means buffer is full
		Throw(ERR_BUFFER_IS_FULL);
    else
	{
		if( cb->size == 0)				   // if size=0 means the first value to be added, hence point to tail
		{		
			copy(cb->tail, objectToAdd);
			cb->size++;
		}
		else
		{
			cb->buffer+=cb->sizeofType;		//  if not the first value in the circularbuffer, then point head to it
			copy(cb->buffer, objectToAdd);
			cb->head = cb->buffer;
			cb->size++;
		}
	}	
}

/*
 * Remove the tail in circular buffer 
 *
 *Input :
 *					Pointer cb is the pointer which pointed to the CircularBuffer structure
 *					objectToDel is the pointer pointed to the value to be remove
 *					copy is a function pointer which pointed to the copyInt function
 *
 * Error checking:
 *					will throw error when trying to remove if the circular buffer is empty
 */
void circularBufferRemove(CircularBuffer *cb, void *objectToDel, void(*copy)(void*,void*))
{
	
	if( cb->size == 0)              // Check whether the circularbuffer is empty or not
		 Throw(ERR_BUFFER_IS_EMPTY);
	else
		{
			copy(objectToDel,cb->tail);  // put the value in the pointer to variable removed_value, then decrement the size and increase the address of tail
			cb->size--;
			cb->tail+=cb->sizeofType;
		}
		
}

