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

void Test_FifoCreate_WithRightArgs(CuTest *tc){
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

void Test_FifoEnqueue_WithRightArgs(CuTest *tc){
    uint32_t valid_nr_entry = 5;
    uint32_t valid_size = 4;
    int32_t data = 100;
    fifo_t testfifo = fifo_create(valid_nr_entry, valid_size);
    CuAssertPtrNotNull(tc, testfifo);
    CuAssertTrue(tc, fifo_enqueue(testfifo, &data));
    free(testfifo->ubuf);
    free(testfifo);
}

//void TestFifoEntryCount(){
//
//}
//
//void TestFifoDestroy(){
//
//}
//
//void TestFifoEntryCount(){
//
//}
//
//void TestFifoEnqueue(){
//
//}
//
//void TestFifoPeek(){
//
//}
//
//void TestFifoDequeue(){
//
//}

CuSuite* FifoGetSuite() {
    CuSuite* suite = CuSuiteNew();
    //SUITE_ADD_TEST(suite, TestStrToUpper);
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithZeroEntryCount);
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithZeroSize);
    SUITE_ADD_TEST(suite, Test_FifoCreate_WithRightArgs);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WithNullData);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WithRightArgs);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WithRightArgs);
    SUITE_ADD_TEST(suite, Test_FifoEnqueue_WithRightArgs);
    //SUITE_ADD_TEST(suite, TestFifoDestroy);
    //SUITE_ADD_TEST(suite, TestFifoEnqueue);
    //SUITE_ADD_TEST(suite, TestFifoDequeue);
    //SUITE_ADD_TEST(suite, TestFifoPeek);
    //SUITE_ADD_TEST(suite, TestFifoEntryCount);
    return suite;
}
