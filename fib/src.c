#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static const char enc[] = {64, 80, 76, 76, 72, 70, 16, 7, 107, 165, 200};

void setup() {
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}

void banner() {
    puts("======== Fib ========\n");
}

int main(void) {
    char password[0x100] = {};
    char tmp_password[0x100] = {};
    int curr = 1;
    int prev = 1;
    int tmp = 0;
    ssize_t ret;
    
    setup();
    banner();
    printf("Enter the password: ");
    ret = read(0, password, 0x100);
    if (password[ret - 1] == '\n') {
        password[ret - 1] = 0;
    }

    if (strlen(password) != sizeof(enc)) {
        printf("Length WRONG!\n");
        return 1;
    }
     

    for (int i = 0; i < strlen(password); i ++) {
        tmp = curr;
        curr += prev;
        prev = tmp;
        tmp_password[i] = password[i] ^ curr;
    }

    if (memcmp(tmp_password, enc, sizeof(enc)) == 0) {
        printf("Correct! Your flag is bsides{%s}\n", password);
        return 0;
    }

    printf("password WRONG!\n");
    return 1;
}
