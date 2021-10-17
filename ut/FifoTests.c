#include <CuTest.h>
#include <fifo.h>
#include <stddef.h>

#define NR_INVALID_ENTRY               0
#define NR_MAX_POSSIBLE_ENTRY          4
#define NR_PARTIALLY_FILLED_ENTRY      2

#define VALID_NR_ENTRY      1
#define INVALID_NR_ENTRY    0

#define INVALID_ENTRY_SIZE  0
#define EXAMPLE_ENTRY_SIZE  4

#define EXAMPLE_DATA_VAL  100

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

void Test_FifoPresentEntries_WithDynamicBuffer(CuTest *tc){
    uint32_t nr_entry = NR_MAX_POSSIBLE_ENTRY, size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = NULL;
    testfifo = fifo_create(nr_entry, size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
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
        CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    }
    CuAssertIntEquals(tc, fifo_present_entries(testfifo), NR_MAX_POSSIBLE_ENTRY);
    free(testfifo);
}

void Test_FifoEnqueue_WithNullData(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    int *test_data_ptr = NULL;
    CuAssertTrue(tc, !fifo_enqueue(testfifo, test_data_ptr));
    free(testfifo);
}

void Test_FifoEnqueue_WithRightConditions(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoEnqueue_WhenFifoIsFull(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    }
    CuAssertTrue(tc, !fifo_enqueue(testfifo, &data));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoDequeue_WhenFifoIsEmpty(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    int32_t popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, !fifo_dequeue(testfifo, &popped_data));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoDequeue_WithRightConditions(CuTest *tc){
    uint32_t valid_nr_entry = NR_PARTIALLY_FILLED_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    int32_t data = EXAMPLE_DATA_VAL;
    int32_t popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    data++;
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    CuAssertTrue(tc, fifo_dequeue(testfifo, &popped_data));
    CuAssertIntEquals(tc, popped_data, EXAMPLE_DATA_VAL);
    CuAssertTrue(tc, fifo_dequeue(testfifo, &popped_data));
    CuAssertIntEquals(tc, popped_data, EXAMPLE_DATA_VAL + 1);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoIsEmpty_WithEmptyFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, is_fifo_empty(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoIsEmpty_WithPartiallyFilledFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++, data++){
        CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    }
    CuAssertTrue(tc, !is_fifo_empty(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoIsFull_WithFullFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    }
    CuAssertTrue(tc, is_fifo_full(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoIsFull_WithPartialllyFilledFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++, data++){
        CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    }
    CuAssertTrue(tc, !is_fifo_full(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoPeek_WhenFifoIsEmpty(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE;
    int32_t popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, !fifo_peek(testfifo, &popped_data));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoPeek_WhenFifoIsFull(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL, popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_MAX_POSSIBLE_ENTRY; i++, data++){
        CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    }
    CuAssertTrue(tc, fifo_peek(testfifo, &popped_data));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoPeek_WithPartiallyFilledFifo(CuTest *tc){
    uint32_t valid_nr_entry = NR_MAX_POSSIBLE_ENTRY, valid_size = EXAMPLE_ENTRY_SIZE, i;
    int32_t data = EXAMPLE_DATA_VAL, popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++, data++){
        CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    }
    for(i=0; i<NR_PARTIALLY_FILLED_ENTRY; i++, data++){
        CuAssertTrue(tc, fifo_peek(testfifo, &popped_data));
        CuAssertIntEquals(tc, popped_data, EXAMPLE_DATA_VAL+i);
        CuAssertTrue(tc, fifo_dequeue(testfifo, &popped_data));
    }
    free(testfifo->ubuf);
    free(testfifo);
}

CuSuite* FifoGetSuite() {
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
    SUITE_ADD_TEST(suite, Test_FifoDequeue_WithRightConditions);
    SUITE_ADD_TEST(suite, Test_FifoIsEmpty_WithEmptyFifo);
    SUITE_ADD_TEST(suite, Test_FifoIsEmpty_WithPartiallyFilledFifo);
    SUITE_ADD_TEST(suite, Test_FifoIsFull_WithFullFifo);
    SUITE_ADD_TEST(suite, Test_FifoIsFull_WithPartialllyFilledFifo);
    SUITE_ADD_TEST(suite, Test_FifoPeek_WhenFifoIsEmpty);
    SUITE_ADD_TEST(suite, Test_FifoPeek_WhenFifoIsFull);
    SUITE_ADD_TEST(suite, Test_FifoPeek_WithPartiallyFilledFifo);
    return suite;
}
