#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    // char buf = 'ÿ';
    // int x = strtol(buf, NULL, 16);
    // printf("%d\n", x);
    // printf("%c\n", (char)x);
    // printf("%c\n", buf);
    // int x = (int)buf;
    // printf("%d\n", x);
    // char test[3];
    // sprintf(test, "%x", x);
    // printf("%s",test);

    //  FILE *file;
    // unsigned char buffer[100]; // 읽어올 데이터를 저장할 버퍼

    // // 텍스트 파일을 바이너리 모드로 열기
    // file = fopen("NAND.txt", "rb");
    // if (file == NULL) {
    //     perror("파일 열기 실패");
    //     return 1;
    // }

    // // 파일에서 데이터 읽기
    // size_t bytes_read = fread(buffer, sizeof(unsigned char), 100, file);
    // if (bytes_read == 0) {
    //     perror("파일 읽기 실패");
    //     return 1;
    // }

    // // 읽은 데이터 출력
    // printf("읽은 데이터: ");
    // for (size_t i = 0; i < bytes_read; i++) {
    //     printf("%02X ", buffer[i]); // 바이너리 데이터를 16진수로 출력
    // }
    // printf("\n");

    // // 파일 닫기
    // fclose(file);
char *pattern = "^[A-Fa-f0-9]+$";
    char *str = "A0C3F5";

    regex_t regex;
    int reti;

    // 정규표현식 컴파일
    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // 문자열 매칭 검사
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        printf("'%s' matches the pattern\n", str);
    } else if (reti == REG_NOMATCH) {
        printf("'%s' does not match the pattern\n", str);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    regfree(&regex); // 정규표현식 메모리 해제

    return 0;

    return 0;
}