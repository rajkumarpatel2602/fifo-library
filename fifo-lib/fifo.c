#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <fifo.h>


fifo_t fifo_create_from_user_buffer(uint32_t nr_entry, uint32_t size, void *buf){
    fifo_t fifo = NULL;
    if (nr_entry != 0 && size != 0){

        // validate user buffer and clean-up the space.
        assert(buf != NULL && "ERROR: NULL buffer provieded!\n");
        memset(buf, 0, nr_entry * size);

        // create fifo descriptor
        fifo = (fifo_t)malloc(sizeof(struct _fifo_des));
        if (fifo != NULL){
            fifo->ubuf = buf;
            fifo->ubuf_size = nr_entry * size;
            fifo->entry_size = size;
            fifo->filled_cnt = 0;
            fifo->write_offset = 0;
            fifo->read_offset = 0;
        }
    }
    return fifo;
}

fifo_t fifo_create(uint32_t nr_entry, uint32_t size){
    fifo_t fifo = NULL;
    if (nr_entry != 0 && size != 0){

        // create fifo descriptor
        fifo = (fifo_t)malloc(sizeof(struct _fifo_des));

        if (fifo != NULL){
            // allocate data memory for user entries
            size_t buf_size = nr_entry * size;
            fifo->ubuf  = (void *)calloc(nr_entry, size);
            assert(fifo->ubuf != NULL && "ERROR: User Buffer Malloc Failed!\n");

            //populate fifo descriptor
            fifo->ubuf_size = buf_size;
            fifo->nr_entry = nr_entry;
            fifo->entry_size = size;
            fifo->filled_cnt = 0;
            fifo->write_offset = 0;
            fifo->read_offset = 0;
        }
    }
    return fifo;
}

fifo_ret fifo_enqueue(fifo_t fifo, void *data){
    fifo_ret ret = SUCCESS;
    assert(fifo != NULL && "ERROR: Bad FIFO Descriptor pointer!");
    if (data == NULL){
        printf("ERROR: Invalid data pointer!\n");
        ret = INVALID_DATA_BUF;
    }
    else{
        // check if fifo is not full and write to fifo.
        if(!is_fifo_full(fifo)){
            memset((uint8_t *)fifo->ubuf + fifo->write_offset, 0, fifo->entry_size);
            memcpy((uint8_t *)fifo->ubuf + fifo->write_offset, data, fifo->entry_size);
            fifo->write_offset += fifo->entry_size;

            // reset write offset to zero if reached/exceeded size of user data buffer.
            if (fifo->write_offset >= fifo->ubuf_size){
                fifo->write_offset = 0;
            }
            fifo->filled_cnt += fifo->entry_size;
        }
        else{
            ret = FIFO_FULL;
        }
    }
    return ret;
}

fifo_ret fifo_dequeue(fifo_t fifo, void *data){
    fifo_ret ret = SUCCESS;
    assert(fifo != NULL && "ERROR: Bad FIFO Descriptor pointer!");
    if (data == NULL){
        printf("ERROR: Invalid data pointer!\n");
        ret = INVALID_DATA_BUF;
    }
    else{
        if(!is_fifo_empty(fifo)){

            // check if fifo is not empty and read from it
            memcpy(data, (uint8_t *)fifo->ubuf + fifo->read_offset, fifo->entry_size);
            fifo->read_offset += fifo->entry_size;

            // reset read offset to zero if reached/exceeded size of user data buffer
            if(fifo->read_offset >= fifo->ubuf_size){
                fifo->read_offset = 0;
            }
            fifo->filled_cnt -= fifo->entry_size;
        }
        else{
            ret = FIFO_EMPTY;
        }
    }
    return ret;
}

fifo_ret fifo_peek(fifo_t fifo, void *data){
    fifo_ret ret = SUCCESS;
    assert(fifo != NULL && "ERROR: Bad FIFO Descriptor pointer!");
    if (data == NULL){
        printf("ERROR: Invalid data pointer!\n");
        ret = INVALID_DATA_BUF;
    }
    else{

        // check if fifo is not empty and read entry
        if(!is_fifo_empty(fifo)){
            memcpy(data, fifo->ubuf + fifo->read_offset, fifo->entry_size);
        }
        else{
            ret = FIFO_EMPTY;
        }
    }
    return ret;
}

uint32_t fifo_present_entries(fifo_t fifo){
    uint32_t cnt = 0;
    assert(fifo != NULL && "ERROR: Bad FIFO Descriptor pointer!");

    // calculate number of entries in fifo
    cnt = (uint32_t)(fifo->filled_cnt / fifo->nr_entry);

    return cnt;
}

bool is_fifo_full(fifo_t fifo){
    bool ret = false;
    assert(fifo != NULL && "ERROR: Bad FIFO Descriptor pointer!");

    // check if filled count exceeded allocated user buffer size
    if(fifo->filled_cnt >= fifo->ubuf_size){
        printf("ERROR: FIFO Is Full!\n");
        ret = true;
    }
    return ret;
}

bool is_fifo_empty(fifo_t fifo){
    bool ret = false;
    assert(fifo != NULL && "ERROR: Bad FIFO Descriptor pointer!");

    // check if filled count is zero
    if(fifo->filled_cnt == 0){
        printf("ERROR: FIFO Is Empty!\n");
        ret = true;
    }
    return ret;
}
