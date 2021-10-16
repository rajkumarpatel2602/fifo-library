// Application using fifo-lib
#include <stdio.h>
#include <fifo.h>

int main(){
    uint32_t nr_entry;
    uint8_t entry_size;
    int32_t data, popped_data;
    printf("Enter number of entries required in fifo!\n");
    scanf("%d", &nr_entry);
    entry_size = 4; //considered int for simplicity
    printf("Creating fifo with %u entry and %u size of each entry\n", nr_entry, entry_size);
    fifo_t myfifo = fifo_create(nr_entry, entry_size);
    if (myfifo == NULL){
        printf("Fifo creation failed!\n");
        exit(1);
    }
cont:
    printf ("Enter data for enqueue!\n");
    while(1){
        printf("Enter an interger!\nEnter -1 to quit enqueue\n");
        scanf("%d", &data);
        if(data == -1) break;
        if(!fifo_enqueue(myfifo, &data)){
            printf("Enqueue failed\n");
            exit(1);
        }
    }

    if(fifo_dequeue(myfifo, &popped_data))
        printf("pop : %d\n", popped_data);
    if(fifo_dequeue(myfifo, &popped_data))
        printf("pop : %d\n", popped_data);
    if(fifo_dequeue(myfifo, &popped_data))
        printf("pop : %d\n", popped_data);

    goto cont;

    exit(0);
}
