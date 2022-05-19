#include <stdio.h>

#include "../source/client.h"

int main() {
    printf("Hello World!\n");

    NPTYPE* pipe = ssipc_open();
    if(pipe == NULL){
        printf("Failed to open pipe: %i\n", GetLastError());
        exit(1);
    }
    printf("Opened pipe\n");
    int res = ssipc_write(pipe, 'c', "sfasjdf");
    if(res != 0) {
        printf("Failed to write message :/\n");
    } else {
        printf("Message sent!");
    }
    return 0;
}