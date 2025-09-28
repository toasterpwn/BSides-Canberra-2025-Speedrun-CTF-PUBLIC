#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void setup() {
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}

void banner() {
    puts("======== Echo As A Service ========\n");
}


int main(void) {
    int fd = -1;
    char buf[0x100] = {};
    char input[0x100] = {};
    setup();
    banner();
    fd = open("flag.txt", O_RDONLY);
    if (fd == -1) {
        printf("ERROR: contact admin\n");
        exit(1);
    }
    read(fd, buf, sizeof(buf));

    while (1) {
        printf("[EAAS]> ");
        read(0, input, sizeof(input));
        printf(input);
    }
}
