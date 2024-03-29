#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void helper(){
    //명령어
    printf("=========================================== HELP ===========================================\n");
    printf("write [lba] [data]: Write data to the specified logical block address (LBA) of the device.\n");
    printf("read [lba] : Read data from the specified logical block address (LBA) of the device.\n");
    printf("fullwrite [data]: Write data to the entire device.\n");
    printf("fullread: Read data from the entire device.\n");
    printf("exit: Exit the program.\n");
    printf("============================================================================================\n");
}
int main(){
    while(1){
        char cmd[1024];
        printf("Song Ha Jang >> ");
        // scanf("%[^\n]%*c", cmd);
        
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1] = '\0';
        fflush(stdin);
        if(strlen(cmd) == 0) continue;

        char *token = strtok(cmd," ");
        char command[1024];
        command[0] = '\0';
        
        strcat(command, "SSD.exe ");
        while(token != NULL){
            if(strcmp(token, "write") == 0){
                strcat(command,"W");
            } else if(strcmp(token, "read") == 0){
                strcat(command,"R");
            } else if(strcmp(token, "exit") == 0){
                return 0;
            } else if(strcmp(token, "help") == 0){
                helper();
            } else if(strcmp(token, "fullwrite") == 0){
                strcat(command,"FW");
            } else if(strcmp(token, "fullread") == 0){
                strcat(command,"FR");
            } else if(strcmp(token, "testapp1") == 0){
                system("SSD.exe FW 0x21341234");
                system("SSD.exe FR");
                break;
            } else if(strcmp(token, "testapp2") == 0){
                for(int i = 0;i<5; i++){
                    char buffer[1024];
                    buffer[0] = '\0';
                    sprintf(buffer,"SSD.exe W %d 0xAAAABBBB", i);
                    for(int j = 0; j<30; j++){
                        system(buffer);
                    }
                }
                for(int i = 0;i<5; i++){
                    char buffer[1024];
                    buffer[0] = '\0';
                    sprintf(buffer,"SSD.exe W %d 0x12345678", i);
                    system(buffer);
                }
                
                for(int i = 0;i<5; i++){
                    char *buffer;
                    sprintf(buffer,"SSD.exe R %d", i);
                    system(buffer);
                }
                break;
            }else {
                strcat(command, " ");
                strcat(command,token);
            }

            //띄어쓰기 파싱
            token = strtok(NULL, " ");
        }

 
        system(command);

        
        
    }
}