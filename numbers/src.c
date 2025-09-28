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
    puts("======== Numbers ========\n");
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
    size_t num_numbers = 0;
    size_t idx = 0;
    unsigned short value = 0;
    unsigned short* numbers = NULL;
    char choice;
    printf("How many numbers? ");
    scanf("%zu", &num_numbers);
    
    if (num_numbers * sizeof(unsigned short) < num_numbers) {
        printf("No overflowing!");
        exit(1);
    }

    numbers = malloc(num_numbers * sizeof(unsigned short));

    while (1) {
        printf("Which idx to set? ");
        scanf("%zu", &idx);
        
        if (idx >= num_numbers) {
            printf("No OOB!");
            exit(1);
        }
        
        printf("Value to set? ");
        scanf("%hu", &value);

        numbers[idx] = value;


        printf("Another? ");
        scanf(" %c", &choice);
        if (choice != 'y') {
            printf("byebye\n", choice);
            exit(0);
        }
    }
}

int main(void) {
    setup();
    banner();
    return vuln();

}
