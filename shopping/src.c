#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void setup() {
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}

void banner() {
    puts("======== Shopping list ========\n");
}

void win() {
    int fd = -1;
    char buf[100] = {};
    fd = open("flag.txt", O_RDONLY);
    if (fd == -1) {
        printf("ERROR: contact admin\n");
        exit(1);
    }
    read(fd, buf, sizeof(buf));
    write(1, buf, sizeof(buf));
    _exit(0);
}

int vuln(void) {
    ssize_t ret = -1;
    int idx = 0;
    size_t listlen = 0;
    char item[0x10] = {};
    char list[0x100] = {};
    char* listp = (char*)&list;
    
    while (1) {
        printf("Enter item (or leave empty to exit): ");
        memset(item, 0, sizeof(item));
        ret = read(0, item, sizeof(item));
        if (item[ret - 1] == '\n') {
            item[ret - 1] = 0;
        }

        if (strcmp(item, "") == 0) {
            break;
        }

        ret = snprintf(listp, sizeof(list) - listlen, "%d) %s\n", idx, item);
        puts(list);
        listp += ret;
        listlen += ret;
        idx++;
    }

    puts("Goodbye!");
    return 0;
}

int main(void) {
    setup();
    banner();
    return vuln();
    
}
