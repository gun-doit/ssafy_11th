#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NAND_WRITE(int LBA, char *value){
    FILE *NAND = fopen("NAND.txt", "r+");

    //파일을 열지 못함.
    if(NAND == NULL){
        printf("NAND.txt not found\n");
        return -1;
    }
    fseek(NAND, LBA * sizeof(int), SEEK_SET);

    // 파싱
    char *ptr = value + 2;
    while(*ptr != '\0'){
        // 스트링을 10진수로 변환

        // 파싱
        char temp[3];
        strncpy(temp, ptr, 2);
        temp[2] = '\0';
        int x = strtol(temp, NULL, 16);
        char WRITE_VALUE = (char)x;

        //저장
        fwrite(&WRITE_VALUE, sizeof(char), 1, NAND);
        ptr+=2;
    }
}

int NAND_READ(int LBA, int mode){
    FILE *NAND = fopen("NAND.txt", "rb");
    FILE *RESULT = fopen("result.txt", "w+");

    unsigned char buffer[100];

    //파일을 열지 못함.
    if(NAND == NULL){
        printf("NAND.txt not found\n");
        return -1;
    }
    fseek(NAND,LBA*sizeof(int), SEEK_SET);
    fseek(RESULT,0, SEEK_SET);

    size_t bytes_read = fread(buffer, sizeof(unsigned char), 4, NAND);
    if(bytes_read == 0){
        printf("[ERROR] read NAND.txt failed\n");
        return -1;
    }

    if(mode) printf("0x");
    else fprintf(RESULT,"0x");
    for (size_t i = 0; i < bytes_read; i++) {
        if(mode) printf("%02X", buffer[i]);
        else fprintf(RESULT, "%02X", buffer[i]);
    }
    if(mode)printf("\n");
    
    fclose(NAND);
    fclose(RESULT);
    return 0;
}

 
int main(int argc, char **argv){
    int LBA;
    if(argc >= 2){
        LBA = strtol(argv[2], NULL, 10);
        if(LBA < 0 || LBA > 99){
            printf("INVALID COMMAND\n");
            return -1;
        }
    }
    // FILE* NAND = fopen("NAND.txt", "w+");

    // //파일을 열지 못함.
    // if(NAND == NULL){
    //     printf("NAND.txt not found");
    //     return -1;
    // }

    // fseek(NAND, 0, SEEK_END);
    // int NAND_SIZE = ftell(NAND); 
    // printf("NAND_SIZE : %dbytes\n", NAND_SIZE);
    // int a = 0;
    // char b = (char)a;
    // for (int i = 0; i < 400; ++i) {
    //     fwrite(&b, sizeof(char), 1, NAND);
    // }

    if(strcmp(argv[1],"W") == 0){  
        if(strlen(argv[3]) != 10 || argv[3][0] != '0' || argv[3][1] != 'x'){
                printf("INVALID COMMAND\n");
                return -1;
        }  
        char *ptr = argv[3] + 2;
        while(*ptr != '\0'){
            if(!(('A' <= *ptr && *ptr <= 'F') || ('0' <= *ptr && *ptr <= '9'))){
                printf("INVALID COMMAND\n");
                return -1;
            }
            ptr++;
        }   
        NAND_WRITE(LBA, argv[3]); 
    }
    
    else if(strcmp(argv[1],"R") == 0){
        NAND_READ(LBA, 0);
    }

    else if(strcmp(argv[1], "FR") == 0){
        for(int i = 0; i<100; i++){
            NAND_READ(i, 1);
        }
    }

    else if(strcmp(argv[1], "FW") == 0){ 
        if(strlen(argv[2]) != 10 || argv[2][0] != '0' || argv[2][1] != 'x'){
            printf("INVALID COMMAND\n");
            return -1;
        }  
        char *ptr = argv[2] + 2;
        while(*ptr != '\0'){
            if(!(('A' <= *ptr && *ptr <= 'F') || ('0' <= *ptr && *ptr <= '9'))){
                printf("INVALID COMMAND\n");
                return -1;
            }
            ptr++;
        }   
        for(int i = 0; i<100; i++){
            NAND_WRITE(i, argv[2]);
        }
    }
    else{
        printf("INVALID COMMAND\n");
        return -1;
    }

    // fclose(NAND);
    return 0;
}