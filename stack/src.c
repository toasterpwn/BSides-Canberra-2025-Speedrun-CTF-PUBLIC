#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>


int8_t stack[INT16_MAX];
int16_t sp;
int8_t r;

void setup() {
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}

void banner() {
    puts("======== Shopping list ========\n");
}

void win(long arg) {
    int fd = -1;
    char buf[100] = {};
    fd = open("flag.txt", O_RDONLY);
    if (fd == -1) {
        printf("ERROR: contact admin\n");
        _exit(1);
    }
    read(fd, buf, sizeof(buf));
    write(1, buf, sizeof(buf));
    _exit(0);
}

void push(int8_t* stack, int8_t val) {
	stack[sp] = val;
	sp++;
}

void pop(int8_t* stack) {
	r = stack[sp];
	sp--;
}

void print(int8_t* stack) {
	printf("Stack of size 0x%02x", sp);
	printf("----\n");
	for (int i = INT16_MAX-1; i >= 0; i --) {
		if (i == sp) {
			printf("0x%02x [sp]\n", stack[i]);
		} else {
			printf("0x%02x\n", stack[i]);
		}
	}
	printf("----\n");
}

int main(void) {
	setup();
	banner();
	memset(&stack, 0, sizeof(stack));
	sp = 0;
	r = 0;

	while (1) {
		printf("Play with the stack!\n");
		printf("1. Push\n");
		printf("2. Pop\n");
		printf("3. Print\n");
		printf("choice> ");

		int choice;
		scanf("%d", &choice);
		getchar();

		switch (choice) {
			case 1:
				int8_t val;
				printf("val> ");
				scanf("%c", &val);
				push((int8_t*)&stack, val);
				printf("Pushed 0x%02x to the stack\n", val);
				break;
			case 2:
				pop((int8_t*)&stack);
				printf("Popped 0x%02x from the stack\n", r);
				break;
			case 3:
				print((int8_t*)&stack);
			case 4:
				puts("Goodbye!");
				exit(0);
			default:
				puts("Invalid!");
				exit(1);

		}

	}
}
