///@file fifo.h

#ifndef __FIFO_H__
#define __FIFO_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*! fifo data structure */
typedef struct _fifo_des{
    void *ubuf;             /*!< buffer to hold user data */
    size_t ubuf_size;       /*!< size of ubuf in bytes */
    size_t nr_entry;        /*!< number or entries in fifo */
    size_t entry_size;      /*!< size of a fifo entry */
    uint8_t write_offset;   /*!< write offset to add an entry */
    uint8_t read_offset;    /*!< read offset to read and entry */
    uint32_t filled_cnt;    /*!< number of used bytes in ubuf */
}*fifo_t;

/*! fifo return status code */
typedef enum _fifo_ret{
    SUCCESS             = 0,    /**< fifo api call succeed */
    ALLOC_FAILED        = -1,   /**< memory allocation failed */
    FIFO_FULL           = -2,   /**< fifo is full */
    FIFO_EMPTY          = -3,   /**< fifo is empty */
    INVALID_DATA_BUF    = -4    /**< data buffer is NULL */
}fifo_ret;

/**
 * API to create a fifo with user allocated buffer for user
 * data sotrage.
 *
 * @param[in] nr_entry
 * @param[in] size
 * @param[in] buf
 * @param[out] fifo_t a pointer to fifo datastructure on success else NULL.
 */
fifo_t fifo_create_from_user_buffer(uint32_t nr_entry, uint32_t size, void *buf);

/**
 * API to create a fifo of given number of elements 
 * and size.
 *
 * @param[in] nr_entry
 * @param[in] size
 * @param[out] fifo_t a pointer to fifo datastructure on success else NULL.
 */
fifo_t fifo_create(uint32_t nr_entry, uint32_t size);

/**
 * API to push an entry to fifo.
 *
 * @param[in] fifo
 * @param[in] data
 * @param[out] ret 0 on success else appropriate enum.
 */
fifo_ret fifo_enqueue(fifo_t fifo, void *data);

/**
 * API to pop a fifo entry.
 *
 * @param[in] fifo
 * @param[in] data
 * @param[out] ret 0 on success else appropriate enum.
 */
fifo_ret fifo_dequeue(fifo_t fifo, void *data);

/**
 * API to get data of very first entry available 
 * to dequeue.
 *
 * @param[in] fifo
 * @param[in] data
 * @param[out] ret 0 on success else appropriate enum.
 */
fifo_ret fifo_peek(fifo_t fifo, void *data);

/**
 * API to check if fifo is full.
 *
 * @param[in] fifo
 * @param[out] ret true if fifo is full.
 */
bool is_fifo_full(fifo_t fifo);

/**
 * API to Check if fifo is empty.
 *
 * @param[in] fifo
 * @param[out] ret true if fifo is empty
 */
bool is_fifo_empty(fifo_t fifo);

/**
 * API to get number of entries in fifo.
 *
 * @param[in] fifo
 * @param[out] ret count of entries present in fifo.
 */
uint32_t fifo_present_entries(fifo_t fifo);

#endif
