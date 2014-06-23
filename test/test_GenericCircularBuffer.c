#include "unity.h"
#include "GenericCircularBuffer.h"
#include "Double.h"
#include "Integer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_CircularBufferNew_should_create_new_CircularBuffer_object_of_integer_type(void)
{
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(0, cb->size);
	TEST_ASSERT_EQUAL(sizeof(int), cb->sizeofType);
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->tail);
	circularBufferDel(cb);
}

void test_CircularBufferNew_should_create_new_CircularBuffer_object_of_double_type(void)
{
	CircularBuffer *cb = circularBufferNew(13,sizeof(double));
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(13, cb->length);
	TEST_ASSERT_EQUAL(0, cb->size);
	TEST_ASSERT_EQUAL(sizeof(double), cb->sizeofType);
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->tail);
	circularBufferDel(cb);
}

void test_circularBufferAdd_given_1_should_add_into_buffer()
{
	int a = 1;
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	circularBufferAdd(cb, &a, copyInt);
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(1, cb->size);
	TEST_ASSERT_EQUAL(1, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(1, *((int*)(cb->tail)));
	TEST_ASSERT_EQUAL(1, *((int*)(cb->buffer)));
}

void test_circularBufferAdd_given_2_3_should_get_head_is_3_tail_is_2()
{
	int array[] = {2,3};
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	circularBufferAdd(cb, &array[0], copyInt);
	circularBufferAdd(cb, &array[1], copyInt);
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(2, cb->size);
	TEST_ASSERT_EQUAL(3, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(2, *((int*)(cb->tail)));
}

void test_circularBufferAdd_given_3_5_8_should_get_head_is_8_tail_is_3()
{
	int array[] = {3,5,8};
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	circularBufferAdd(cb, &array[0], copyInt);
	circularBufferAdd(cb, &array[1], copyInt);
	circularBufferAdd(cb, &array[2], copyInt);
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(3, cb->size);
	TEST_ASSERT_EQUAL(8, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(3, *((int*)(cb->tail)));
}