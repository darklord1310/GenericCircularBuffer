#include "unity.h"
#include "GenericCircularBuffer.h"
#include "Double.h"
#include "Integer.h"
#include <CException.h>

void setUp(void)
{
}

void tearDown(void)
{
}

/*
 *	All the tests below are for int type 
 */
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


void test_circularBufferAdd_given_1_should_add_into_buffer()
{
	CEXCEPTION_T err;
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	int a = 1;
	Try{
	
	circularBufferAdd(cb, &a, copyInt);
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(1, cb->size);
	TEST_ASSERT_EQUAL(1, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(1, *((int*)(cb->tail)));
	TEST_ASSERT_EQUAL(1, *((int*)(cb->buffer)));
	}
	Catch(err){
		TEST_FAIL_MESSAGE("Should not expect error to be generated");
	}
	circularBufferDel(cb);
}

void test_circularBufferAdd_given_2_3_should_get_head_is_3_tail_is_2()
{
	CEXCEPTION_T err;
	int array[] = {2,3};
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	Try{
	circularBufferAdd(cb, &array[0], copyInt);
	circularBufferAdd(cb, &array[1], copyInt);
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(2, cb->size);
	TEST_ASSERT_EQUAL(3, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(2, *((int*)(cb->tail)));
	}Catch(err){
		TEST_FAIL_MESSAGE("Should not expect error to be generated");
	}
	circularBufferDel(cb);
}

void test_circularBufferAdd_given_3_5_8_should_get_head_is_8_tail_is_3()
{
	CEXCEPTION_T err;
	int array[] = {3,5,8};
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	Try{
	circularBufferAdd(cb, &array[0], copyInt);
	circularBufferAdd(cb, &array[1], copyInt);
	circularBufferAdd(cb, &array[2], copyInt);
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(3, cb->size);
	TEST_ASSERT_EQUAL(8, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(3, *((int*)(cb->tail)));
	}Catch(err){
		TEST_FAIL_MESSAGE("Should not expect error to be generated");
	}
	circularBufferDel(cb);
}

void test_circularBufferRemove_given_4_5_6_should_return_get_head_is_6_tail_is_5()
{
	CEXCEPTION_T err;
	int array[] = {4,5,6};
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	int objectToDel;
	Try{
	circularBufferAdd(cb, &array[0], copyInt);
	circularBufferAdd(cb, &array[1], copyInt);
	circularBufferAdd(cb, &array[2], copyInt);
	circularBufferRemove(cb, &objectToDel, copyInt);
	TEST_ASSERT_EQUAL(4,objectToDel);
	TEST_ASSERT_EQUAL(2,cb->size);
	TEST_ASSERT_EQUAL(6, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(5, *((int*)(cb->tail)));
	}Catch(err){
		TEST_FAIL_MESSAGE("Should not expect error to be generated");
	}
	circularBufferDel(cb);
}

void test_circularBufferRemove_given_3_5_8_should_return_get_head_is_8_tail_is_8()
{
	CEXCEPTION_T err;
	int array[] = {3,5,8};
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	int objectToDel;
	circularBufferAdd(cb, &array[0], copyInt);
	circularBufferAdd(cb, &array[1], copyInt);
	circularBufferAdd(cb, &array[2], copyInt);
	circularBufferRemove(cb, &objectToDel, copyInt);
	TEST_ASSERT_EQUAL(3,objectToDel);
	circularBufferRemove(cb, &objectToDel, copyInt);
	TEST_ASSERT_EQUAL(5,objectToDel);
	TEST_ASSERT_EQUAL(1,cb->size);
	TEST_ASSERT_EQUAL(8, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(8, *((int*)(cb->tail)));
	circularBufferDel(cb);
}

void test_circularBufferRemove_given_3_5_8_then_add_4_add_2_remove_twice_then_add_6_remove_again_should_get_head_is_6_tail_is_4()
{
	CEXCEPTION_T err;
	int array[] = {3,5,8};
	int value1 = 4, value2 =2 ,value3 = 6;
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	int objectToDel;
	Try{
	circularBufferAdd(cb, &array[0], copyInt);
	circularBufferAdd(cb, &array[1], copyInt);
	circularBufferAdd(cb, &array[2], copyInt);
	circularBufferAdd(cb, &value1, copyInt);
	circularBufferAdd(cb, &value2, copyInt);
	circularBufferRemove(cb, &objectToDel, copyInt);
	circularBufferRemove(cb, &objectToDel, copyInt);
	circularBufferAdd(cb, &value3, copyInt);
	circularBufferRemove(cb, &objectToDel, copyInt);
	TEST_ASSERT_EQUAL(3,cb->size);
	TEST_ASSERT_EQUAL(6, *((int*)(cb->head)));
	TEST_ASSERT_EQUAL(4, *((int*)(cb->tail)));
	}Catch(err){
		TEST_FAIL_MESSAGE("Should not expect error to be generated");
	}
	circularBufferDel(cb);
}

void test_circularBufferRemove_given_empty_should_get_err()
{
	CEXCEPTION_T err;
	CircularBuffer *cb = circularBufferNew(0,sizeof(int));
	int objectToDel;
	Try
	{
		circularBufferRemove(cb, &objectToDel, copyInt);
		TEST_FAIL_MESSAGE("Should expect error to be generated");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(err,ERR_BUFFER_IS_EMPTY);
		printf("Error is generated because of buffer is empty!");
	}
	circularBufferDel(cb);
}

void test_circularBufferRemove_given_7_8_9_when_remove_four_times_should_get_err()
{
	CEXCEPTION_T err;
	int array[] = {7,8,9};
	CircularBuffer *cb = circularBufferNew(3,sizeof(int));
	int objectToDel;
	Try
	{
		circularBufferAdd(cb, &array[0], copyInt);
		circularBufferAdd(cb, &array[1], copyInt);
		circularBufferAdd(cb, &array[2], copyInt);
		circularBufferRemove(cb, &objectToDel, copyInt);
		circularBufferRemove(cb, &objectToDel, copyInt);
		circularBufferRemove(cb, &objectToDel, copyInt);
		circularBufferRemove(cb, &objectToDel, copyInt);
		TEST_FAIL_MESSAGE("Should expect error to be generated");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(err,ERR_BUFFER_IS_EMPTY);
		printf("Error is generated because of buffer is empty!");
	}
	circularBufferDel(cb);
}


void test_circularBufferAdd_given_size_is_3_and_full_when_add_should_get_err()
{
	CEXCEPTION_T err;
	int array[] = {7,8,9};
	CircularBuffer *cb = circularBufferNew(3,sizeof(int));
	int objectToDel;
	Try
	{
		circularBufferAdd(cb, &array[0], copyInt);
		circularBufferAdd(cb, &array[1], copyInt);
		circularBufferAdd(cb, &array[2], copyInt);
		circularBufferAdd(cb, &array[2], copyInt);
		TEST_FAIL_MESSAGE("Should expect error to be generated");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(err,ERR_BUFFER_IS_FULL);
		printf("Error is generated because of buffer is full!");
	}
	circularBufferDel(cb);
}



/*
 *	All the tests below are for double type 
 */
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
