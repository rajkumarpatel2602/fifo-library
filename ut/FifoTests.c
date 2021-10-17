#include <CuTest.h>
#include <fifo.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NR_INVALID_ENTRY                0
#define NR_MAX_POSSIBLE_ENTRY           4
#define NR_PARTIALLY_FILLED_ENTRY       2

#define VALID_NR_ENTRY                  1
#define INVALID_NR_ENTRY                0

#define INVALID_ENTRY_SIZE              0
#define EXAMPLE_ENTRY_SIZE              4
#define EXAMPLE_ENTRY_STR_SIZE          20

#define EXAMPLE_DATA_VAL                100


/// Tests for fifo_create() API
void Test_FifoCreate_WithZeroEntryCount(CuTest *tc){
    uint32_t nr_entry = NR_INVALID_ENTRY, size = EXAMPLE_ENTRY_SIZE;
    fifo_t testfifo = NULL;
    testfifo = fifo_create(nr_entry, size);
    fifo_t *expected = NULL;
    CuAssertPtrEquals(tc, expected, testfifo);
}

void Test_FifoCreate_WithZeroSize(CuTest *tc){
    uint32_t nr_entry = NR_MAX_POSSIBLE_ENTRY, size = INVALID_ENTRY_SIZE;
    fifo_t testfifo = NULL;
    testfifo = fifo_create(nr_entry, size);
    fifo_t *expected = NULL;
    CuAssertPtrEquals(tc, expected, testfifo);
}

void Test_FifoCreate_WithRightConditions(CuTest *tc){
    uint32_t nr_entry = NR_MAX_POSSIBLE_ENTRY, size = EXAMPLE_ENTRY_SIZE;
    fifo_t testfifo = NULL;
    testfifo = fifo_create(nr_entry, size);
    CuAssertPtrNotNull(tc, testfifo);
    free(testfifo->ubuf);
    free(testfifo);
}


/// Tests for fifo_create_from_user_buffer()
void Test_FifoCreateWithUserBuffer_WithZeroEntryCount(CuTest *tc){
    uint32_t nr_entry = NR_INVALID_ENTRY, size = EXAMPLE_ENTRY_SIZE;
    int32_t UserArr[NR_MAX_POSSIBLE_ENTRY * EXAMPLE_ENTRY_SIZE] = {0};
    fifo_t testfifo = NULL;
    testfifo = fifo_create_from_user_buffer(nr_entry, size, UserArr);
    fifo_t *expected = NULL;
    CuAssertPtrEquals(tc, expected, testfifo);
    free(testfifo);
}

void Test_FifoCreateWithUserBuffer_WithZeroSize(CuTest *tc){
    uint32_t nr_entry = NR_MAX_POSSIBLE_ENTRY, size = INVALID_ENTRY_SIZE;
    int32_t UserArr[NR_MAX_POSSIBLE_ENTRY * EXAMPLE_ENTRY_SIZE] = {0};
    fifo_t testfifo = NULL;
    testfifo = fifo_create_from_user_buffer(nr_entry, size, UserArr);
    fifo_t *expected = NULL;
    CuAssertPtrEquals(tc, expected, testfifo);
    free(testfifo);
}

void Test_FifoCreateWithUserBuffer_WithRightConditions(CuTest *tc){
    uint32_t nr_entry = NR_MAX_POSSIBLE_ENTRY, size = EXAMPLE_ENTRY_SIZE;
    int32_t UserArr[NR_MAX_POSSIBLE_ENTRY * EXAMPLE_ENTRY_SIZE] = {0};
    fifo_t testfifo = NULL;
    testfifo = fifo_create_from_user_buffer(nr_entry, size, UserArr);
    CuAssertPtrNotNull(tc, testfifo);
    free(testfifo);
}


/// Tests for fifo_present_entries() API
void Test_FifoPresentEntries_WithDynamicBuffer(CuTest *tc){
    uint32_t nr_entry = NR_MAX_POSSIBLE_ENTRY, size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = NULL;
    testfifo = fifo_create(nr_entry, size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    CuAssertIntEquals(tc, fifo_present_entries(testfifo), NR_MAX_POSSIBLE_ENTRY);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoPresentEntries_WithUserBuffer(CuTest *tc){
    uint32_t nr_entry = NR_MAX_POSSIBLE_ENTRY, size = EXAMPLE_ENTRY_SIZE, i;
    int32_t UserArr[NR_MAX_POSSIBLE_ENTRY * EXAMPLE_ENTRY_SIZE] = {0};
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = NULL;
    testfifo = fifo_create_from_user_buffer(nr_entry, size, UserArr);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    CuAssertIntEquals(tc, fifo_present_entries(testfifo), NR_MAX_POSSIBLE_ENTRY);
    free(testfifo);
}


/// Tests for fifo_enqueue() API
void Test_FifoEnqueue_WithNullData(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    int *test_data_ptr = NULL;
    CuAssertIntEquals(tc, fifo_enqueue(testfifo, test_data_ptr), INVALID_DATA_BUF);
    free(testfifo);
}

void Test_FifoEnqueue_WithRightConditions(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoEnqueue_WhenFifoIsFull(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), FIFO_FULL);
    free(testfifo->ubuf);
    free(testfifo);
}


/// Tests for fifo_dequeue() API
void Test_FifoDequeue_WhenFifoIsEmpty(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    int32_t popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertIntEquals(tc, fifo_dequeue(testfifo, &popped_data), FIFO_EMPTY);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoDequeue_WhenUserDataBuffNull(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    int32_t *popped_data_ptr = NULL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    CuAssertIntEquals(tc, fifo_dequeue(testfifo, popped_data_ptr), INVALID_DATA_BUF);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoDequeue_WithRightConditions(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    int32_t popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++){
        CuAssertIntEquals(tc, fifo_dequeue(testfifo, &popped_data), SUCCESS);
        CuAssertIntEquals(tc, popped_data, EXAMPLE_DATA_VAL + i);
    }
    CuAssertIntEquals(tc, fifo_dequeue(testfifo, &popped_data), FIFO_EMPTY);
    free(testfifo->ubuf);
    free(testfifo);
}


/// Test for enqueue-dequeue with dynamically allocated data buffer
void Test_FifoCreate_StringEnqueueDequeue(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_STR_SIZE, i;
    int8_t data_str[EXAMPLE_ENTRY_STR_SIZE] = "Fifo_Str_";
    int8_t popped_str[EXAMPLE_ENTRY_STR_SIZE]={0};
    int8_t pos = 0;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    pos = strlen(data_str);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++){
        data_str[pos] = i + '0';
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, data_str), SUCCESS);
    }
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++){
        CuAssertIntEquals(tc, fifo_dequeue(testfifo, popped_str), SUCCESS);
        data_str[pos] = i + '0';
        CuAssertStrEquals(tc, popped_str, data_str);
    }
    CuAssertIntEquals(tc, fifo_dequeue(testfifo, popped_str), FIFO_EMPTY);
    free(testfifo->ubuf);
    free(testfifo);
}


/// Test for enqueue-dequeue with user provided data buffer
void Test_FifoCreateWithUserBuffer_StringEnqueueDequeue(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_STR_SIZE, i;
    int8_t UserArr[NR_MAX_POSSIBLE_ENTRY * EXAMPLE_ENTRY_STR_SIZE] = {0};
    int8_t data_str[EXAMPLE_ENTRY_STR_SIZE] = "Fifo_Str_";
    int8_t popped_str[EXAMPLE_ENTRY_STR_SIZE]={0};
    int8_t pos = 0;
    fifo_t testfifo = fifo_create_from_user_buffer(valid_nr_entry, valid_size, UserArr);
    CuAssertPtrNotNull(tc, testfifo);
    pos = strlen(data_str);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++){
        data_str[pos] = i + '0';
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, data_str), SUCCESS);
    }
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++){
        CuAssertIntEquals(tc, fifo_dequeue(testfifo, popped_str), SUCCESS);
        data_str[pos] = i + '0';
        CuAssertStrEquals(tc, popped_str, data_str);
    }
    CuAssertIntEquals(tc, fifo_dequeue(testfifo, popped_str), FIFO_EMPTY);
    free(testfifo);
}


/// Tests for is_fifo_empty() API
void Test_IsFifoEmpty_WithEmptyFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, is_fifo_empty(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_IsFifoEmpty_WithPartiallyFilledFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    CuAssertTrue(tc, !is_fifo_empty(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}


/// Tests for is_fifo_full() API
void Test_IsFifoFull_WithFullFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    CuAssertTrue(tc, is_fifo_full(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_IsFifoFull_WithPartialllyFilledFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    CuAssertTrue(tc, !is_fifo_full(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}


/// Tests for fifo_peek() API
void Test_FifoPeek_WhenFifoIsEmpty(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    int32_t popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertIntEquals(tc, fifo_peek(testfifo, &popped_data), FIFO_EMPTY);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoPeek_WhenFifoIsFull(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL, popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++){
        CuAssertIntEquals(tc, fifo_peek(testfifo, &popped_data), SUCCESS);
        CuAssertIntEquals(tc, popped_data, EXAMPLE_DATA_VAL + i);
        CuAssertIntEquals(tc, fifo_dequeue(testfifo, &popped_data), SUCCESS);
        CuAssertIntEquals(tc, popped_data, EXAMPLE_DATA_VAL + i);
    }
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoPeek_WhenUserDataBuffNull(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    int32_t *popped_data_ptr = NULL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    CuAssertIntEquals(tc, fifo_peek(testfifo, popped_data_ptr), INVALID_DATA_BUF);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoPeek_WithPartiallyFilledFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL, popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++, data++){
        CuAssertIntEquals(tc, fifo_enqueue(testfifo, &data), SUCCESS);
    }
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++){
        CuAssertIntEquals(tc, fifo_peek(testfifo, &popped_data), SUCCESS);
        CuAssertIntEquals(tc, popped_data, EXAMPLE_DATA_VAL + i);
        CuAssertIntEquals(tc, fifo_dequeue(testfifo, &popped_data), SUCCESS);
        CuAssertIntEquals(tc, popped_data, EXAMPLE_DATA_VAL + i);
    }
    free(testfifo->ubuf);
    free(testfifo);
}


/// Entry point for this Fifo Tests suite
CuSuite* FifoTestSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithZeroEntryCount);
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithZeroSize);
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithRightConditions);

    SUITE_ADD_TEST(suite, Test_FifoCreateWithUserBuffer_WithZeroEntryCount);
    SUITE_ADD_TEST(suite, Test_FifoCreateWithUserBuffer_WithZeroSize);
    SUITE_ADD_TEST(suite, Test_FifoCreateWithUserBuffer_WithRightConditions);

    SUITE_ADD_TEST(suite, Test_FifoPresentEntries_WithDynamicBuffer);
    SUITE_ADD_TEST(suite, Test_FifoPresentEntries_WithUserBuffer);
    SUITE_ADD_TEST(suite, Test_FifoCreateWithUserBuffer_WithRightConditions);

    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WithNullData);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WithRightConditions);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WhenFifoIsFull);

    SUITE_ADD_TEST(suite, Test_FifoDequeue_WhenFifoIsEmpty);
    SUITE_ADD_TEST(suite, Test_FifoDequeue_WhenUserDataBuffNull);
    SUITE_ADD_TEST(suite, Test_FifoDequeue_WithRightConditions);

    SUITE_ADD_TEST(suite, Test_FifoCreate_StringEnqueueDequeue);
    SUITE_ADD_TEST(suite, Test_FifoCreateWithUserBuffer_StringEnqueueDequeue);

    SUITE_ADD_TEST(suite, Test_IsFifoEmpty_WithEmptyFifo);
    SUITE_ADD_TEST(suite, Test_IsFifoEmpty_WithPartiallyFilledFifo);

    SUITE_ADD_TEST(suite, Test_IsFifoFull_WithFullFifo);
    SUITE_ADD_TEST(suite, Test_IsFifoFull_WithPartialllyFilledFifo);

    SUITE_ADD_TEST(suite, Test_FifoPeek_WhenFifoIsEmpty);
    SUITE_ADD_TEST(suite, Test_FifoPeek_WhenFifoIsFull);
    SUITE_ADD_TEST(suite, Test_FifoPeek_WhenUserDataBuffNull);
    SUITE_ADD_TEST(suite, Test_FifoPeek_WithPartiallyFilledFifo);

    return suite;
}
