// Application using fifo-lib
#include <stdio.h>
#include <stdlib.h>
#include <fifo.h>

#define DATA_SIZE   4

int main(){
    uint32_t nr_entry;
    uint8_t entry_size;
    int32_t data, popped_data;
    fifo_ret rc = 0;
    printf("Enter number of entries required in fifo!\n");
    scanf("%d", &nr_entry);
    entry_size = DATA_SIZE; //considered int for simplicity
    printf("Creating fifo with %u entries with each entry size %u\n",
            nr_entry, entry_size);
    fifo_t myfifo = fifo_create(nr_entry, entry_size);
    if (myfifo == NULL){
        printf("Fifo creation failed!\n");
        exit(1);
    }

    /// Outer loop to keep on enqueuing data and dequeuing same.
    for(;;){
        /// Loop to take user data as input to enqueue.
        while(1){
            printf("\nEnter an integer data OR Enter -1 to quit enqueue and "\
                    "ctrl+c anytime to quit process!\n");
            scanf(" %d", &data);
            if(data == -1) break;
            if(rc = fifo_enqueue(myfifo, &data)){
                printf("enqueue failed with error code : %d\n", rc);
                break;
            }
        }

        /// dequeue entries
        while(1){
            printf("\nWanna dequeu? Press 'y' or 'Y' OR " \
                "other key to quit dequeue OR " \
                "ctrl+c anytime to quit process!\n");
            char ch;
            scanf(" %c", &ch);
            if(ch == 'y' || ch == 'Y'){
                if(!(rc = fifo_dequeue(myfifo, &popped_data))){
                    printf("pop : %d\n", popped_data);
                    continue;
                }
                else{
                    printf("dequeue failed with error code : %d\n", rc);
                }
            }
            break;
        }
    }

    exit(0);
}
