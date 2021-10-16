// Application using fifo-lib
#include <stdio.h>
#include <fifo.h>

int main(){
    uint32_t nr_entry;
    uint8_t entry_size;
    int8_t char_data;
    int32_t int_data;
    int32_t str[20];
    printf("Enter number of entries required in fifo!\n");
    scanf("%d\n", &nr_entry);
    for(;;)
    {
        printf("Provide size of each entry,\n 1: for char\n 4: for int, 20: for string of 20 bytes\n");// may fail in worng user input;
        scanf("%d\n", &entry_size);
        switch(entry_size){
            case 1: printf("%s type selected!\n", "Char"); break;
            case 4: printf("%s type selected!\n", "Integer"); break;
            case 20: printf("%s type selected!\n", "String"); break;
            default: printf("Wrong input!"); continue;
        }
        break;
    }
    printf("Creating fifo with %u entry and %u size of each entry\n", nr_entry, entry_size);
    fifo_t myfifo = fifo_create(nr_entry, entry_size);
    if (myfifo == NULL){
        printf("Fifo creation failed!\n");
    }
    else{
        printf("Enter data to enqueue!\n");
        if(entry_size == 1){
            printf("Enter a charcter!\n");
            scanf("%c", &char_data);
            fifo_enqueue(myfifo, &char_data);
        }else if(entry_size == 4){
            printf("Enter an interget!\n");
            scanf("%c", &char_data);
            fifo_enqueue(myfifo, &int_data);
        }else if(entry_size == 20){
            printf("Enter a string\n");
            scanf("%s", str);
            fifo_enqueue(myfifo, str);
        }
        fifo_display(myfifo);
    }
}
