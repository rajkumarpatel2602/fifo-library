#include <fifo.h>

/// Helper methods
static bool is_fifo_full(fifo_t fifo){
    bool ret = false;
    if(fifo->filled_cnt >= fifo->ubuf_size){
        printf("FIFO Is Full!\n");
        ret = true;
    }
    return ret;
}

static bool is_fifo_empty(fifo_t fifo){
    bool ret = false;
    if(fifo->filled_cnt == 0){
        printf("FIFO Is Empty!\n");
        ret = true;
    }
    return ret;
}

/// Exposed to user
fifo_t fifo_create_from_user_buffer(uint32_t nr_entry, uint32_t size, void *buf){
    fifo_t fifo = NULL;
    if (nr_entry != 0){
        if(buf != NULL){
            fifo = (fifo_t)malloc(sizeof(struct fifo_des));
            if (fifo != NULL){
                fifo->ubuf = buf;
                fifo->ubuf_size = n
                fifo->entry_size = size;
                fifo->filled_cnt = 0;
                fifo->write_offset = 0;
                fifo->read_offset = 0;
            }
        }
    }
    return fifo;
}

fifo_t fifo_create(uint32_t nr_entry, uint32_t size){
    fifo_t fifo = NULL;
    if (nr_entry != 0){
        fifo = (fifo_t)malloc(sizeof(struct fifo_des));
        if (fifo != NULL){
            size_t buf_size = nr_entry * size;
            fifo->buf  = malloc(total_buf_size)
            if(fifo->ubuf == NULL){
                printf("Malloc failed!\n");
                free(fifo);
            }else{
                fifo->ubuf_size = buf_size;
                fifo->nr_entry = nr_entry;
                fifo->entry_size = size;
                fifo->filled_cnt = 0;
                fifo->write_offset = 0;
                fifo->read_offset = 0;
            }
        }
    }
    return fifo;
}

bool fifo_enqueue(fifo_t fifo, void *data){
    bool ret = true;
    if(!is_fifo_full(fifo)){
        if (fifo->write_offset >= ((int8_t *)fifo->ubuf) + fifo->ubuf_size){
            fifo->write_offset = 0;
        }
        memcopy(fifo->write_offset, data, fifo->entry_size);
        fifo->write_offset += fifo->entry_size;
    }else{
        ret = false;
    }
    return ret;
}

bool fifo_dequeue(fifo_t fifo, void *data){
    bool ret = true;
    if(!is_fifo_empty(fifo)){
        if(fifo->read_offset >= ((int8_t *)fifo->ubuf + fifo->ubuf_size)){
            fifo->read_offset = 0;
        }
        memcopy(data, fifo->read_offset, fifo->entry_size);
        fifo->read_offset += fifo->entry_size;
    }
}

bool fifo_peek(fifo_t fifo, void *data){
    bool ret = false;
    if(!is_fifo_empty(fifo)){
        memcopy(data, fifo->read_offset, fifo->entry_size);
        ret = true;
    }
    return ret;
}
