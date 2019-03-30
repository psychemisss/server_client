#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void dump(const unsigned char *data_buffer, const unsigned int length){
    unsigned char byte;
    unsigned int i, j;
    
    //int file;
    //file = open("inpack", O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH); just file opening
    
    for(i = 0; i < length; i++){
        byte = data_buffer[i];
        printf("%02X ", data_buffer[i]); //converting data to hex

        if(((i%16) == 15) || (i == length -1)){
            for(j = 0; j < 15 - (i%16); j++)
                printf(" ");
            printf("| ");

            for(j = (i - (i%16)); j <= i; j++){
                byte = data_buffer[j];
                if((byte > 31) && (byte < 127))
                    printf("%c", byte);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
    
}

void throw_exeption(char *service, char *message, char *error_code){
    printf("[Error]:[%s] %s : %s\n", service, message, error_code);
    exit(1);
}

void debug_msg(char *service, char *message){
    printf("[Debug]:[%s] %s\n", service, message);
}