#ifndef GenericCircularBuffer_H
#define GenericCircularBuffer_H

typedef enum {ERR_NO_ERROR, ERR_BUFFER_IS_FULL, ERR_BUFFER_IS_EMPTY}ErrorCode;

typedef struct
{
	void *head;
	void *tail;
	int length;    // total number of items allowable in the buffer
	int size;	   // current number of item in the buffer
	int sizeofType;
	void *buffer;
}CircularBuffer;


CircularBuffer *circularBufferNew(int length, int sizeofType);
void circularBufferAdd(CircularBuffer *cb, void *objectToAdd, void(*copy)(void*,void*));
void circularBufferDel(CircularBuffer *circularBuffer);
void circularBufferRemove(CircularBuffer *cb, void *objectToDel, void(*copy)(void*,void*));

#endif // GenericCircularBuffer_H
