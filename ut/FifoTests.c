#include "CuTest.h"
#include <fifo.h>
#include <stddef.h>


void Test_FifoCreate_WithZeroEntryCount(CuTest *tc){
    uint32_t nr_entry = 0;
    uint32_t size = 4;
    fifo_t testfifo = NULL;
    testfifo = fifo_create(nr_entry, size);
    fifo_t *expected = NULL;
    CuAssertPtrEquals(tc, expected, testfifo);
}

void Test_FifoCreate_WithZeroSize(CuTest *tc){
    uint32_t nr_entry = 10;
    uint32_t size = 0;
    fifo_t testfifo = NULL;
    testfifo = fifo_create(nr_entry, size);
    fifo_t *expected = NULL;
    CuAssertPtrEquals(tc, expected, testfifo);
}

void Test_FifoCreate_WithRightConditions(CuTest *tc){
    uint32_t nr_entry = 10;
    uint32_t size = 4;
    fifo_t testfifo = NULL;
    testfifo = fifo_create(nr_entry, size);
    CuAssertPtrNotNull(tc, testfifo);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoEnqueue_WithNullData(CuTest *tc){
    uint32_t valid_nr_entry = 5;
    uint32_t valid_size = 4;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    int *test_data_ptr = NULL;
    CuAssertTrue(tc, !fifo_enqueue(testfifo, test_data_ptr));
}

void Test_FifoEnqueue_WithRightConditions(CuTest *tc){
    uint32_t valid_nr_entry = 5;
    uint32_t valid_size = 4;
    int32_t data = 100;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoEnqueue_WhenFifoIsFull(CuTest *tc){
    uint32_t valid_nr_entry = 1;
    uint32_t valid_size = 4;
    int32_t data = 100;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    data = 200;
    CuAssertTrue(tc, !fifo_enqueue(testfifo, &data));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoDequeue_WhenFifoIsEmpty(CuTest *tc){
    uint32_t valid_nr_entry = 1;
    uint32_t valid_size = 4;
    int32_t popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, !fifo_dequeue(testfifo, &popped_data));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoDequeue_WithRightConditions(CuTest *tc){
    uint32_t valid_nr_entry = 2;
    uint32_t valid_size = 4;
    int32_t data = 100;
    int32_t popped_data;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    data = 200;
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    CuAssertTrue(tc, fifo_dequeue(testfifo, &popped_data));
    CuAssertIntEquals(tc, popped_data, 100);
    CuAssertTrue(tc, fifo_dequeue(testfifo, &popped_data));
    CuAssertIntEquals(tc, popped_data, 200);
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoIsEmpty_WithEmptyFifo(CuTest *tc){
    uint32_t valid_nr_entry = 1;
    uint32_t valid_size = 4;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, is_fifo_empty(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoIsEmpty_WithPartiallyFilledFifo(CuTest *tc){
    uint32_t valid_nr_entry = 1;
    uint32_t valid_size = 4;
    int32_t data = 100;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    CuAssertTrue(tc, !is_fifo_empty(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}


void Test_FifoIsFull_WithFullFifo(CuTest *tc){
    uint32_t valid_nr_entry = 2;
    uint32_t valid_size = 4;
    int32_t data = 100;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    data = 200;
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    CuAssertTrue(tc, is_fifo_full(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

void Test_FifoIsFull_WithPartialllyFilledFifo(CuTest *tc){
    uint32_t valid_nr_entry = 2;
    uint32_t valid_size = 4;
    int32_t data = 100;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    CuAssertTrue(tc, !is_fifo_full(testfifo));
    free(testfifo->ubuf);
    free(testfifo);
}

CuSuite* FifoGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithZeroEntryCount);
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithZeroSize);
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithRightConditions);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WithNullData);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WithRightConditions);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WhenFifoIsFull);
    SUITE_ADD_TEST(suite, Test_FifoDequeue_WhenFifoIsEmpty);
    SUITE_ADD_TEST(suite, Test_FifoDequeue_WithRightConditions);
    SUITE_ADD_TEST(suite, Test_FifoIsEmpty_WithEmptyFifo);
    SUITE_ADD_TEST(suite, Test_FifoIsEmpty_WithPartiallyFilledFifo);
    SUITE_ADD_TEST(suite, Test_FifoIsFull_WithFullFifo);
    SUITE_ADD_TEST(suite, Test_FifoIsFull_WithPartialllyFilledFifo);
    //SUITE_ADD_TEST(suite, Test_FifoPeek_WithEmptyFifo);
    //SUITE_ADD_TEST(suite, Test_FifoPeek_WithFullFifo);
    //SUITE_ADD_TEST(suite, Test_FifoPeek_WithPartiallyFilledFifo);
    return suite;
}
