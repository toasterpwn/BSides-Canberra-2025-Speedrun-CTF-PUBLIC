#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BODY_WIDTH 32
#define LINE_CHAR  '-'

static void print_border(void)
{
    putchar('+');
    for (int i = 0; i < BODY_WIDTH + 2; ++i) putchar(LINE_CHAR);
    puts("+");
}

static void print_center(const char *text)
{
    int len = (int)strlen(text);
    int pad = BODY_WIDTH - len;
    int left = pad / 2, right = pad - left;

    printf("| %*s%s%*s |\n", left, "", text, right, "");
}

static void print_wrapped(const char *msg)
{
    char buf[256];
    strncpy(buf, msg, sizeof buf - 1);
    buf[sizeof buf - 1] = '\0';

    char *tok = strtok(buf, " \t\n");
    char line[BODY_WIDTH + 1] = {0};
    int idx = 0;

    while (tok) {
        int wlen = (int)strlen(tok);
        if (idx && idx + 1 + wlen > BODY_WIDTH) {
            printf("| %-*.*s |\n", BODY_WIDTH, BODY_WIDTH, line);
            idx = 0;
        }
        if (idx) line[idx++] = ' ';
        memcpy(line + idx, tok, wlen + 1);
        idx += wlen;
        tok = strtok(NULL, " \t\n");
    }
    if (idx)
        printf("| %-*.*s |\n", BODY_WIDTH, BODY_WIDTH, line);
}

void postcard(const char *name, const char *message)
{
    print_border();
    print_center("~ Dear ~");
    print_center(name);
    print_border();
    print_wrapped(message);
    print_border();
}

void setup() {
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}


void win() {
    FILE* fp = NULL;
    char flag[100] = {};
    fp = fopen("flag.txt", "r");
    if (!fp) {
        printf("ERROR: contact admin\n");
        exit(1);
    }

    fread(flag, sizeof(char), sizeof(flag), fp);
    fwrite(flag, sizeof(char), sizeof(flag), stdout);
}

void banner() {
    puts("======== Postcard generator ========\n");
}

int main(void) {
    setup();
    banner();
    char name[100] = {};
    char message[100] = {};
    ssize_t ret = -1;
    
    printf("Enter recipient's name: ");
    ret = read(0, name, 0x100);
    if (name[ret - 1] == '\n') {
        name[ret - 1] = 0;
        
    }
    printf("Enter the message to send to %s: ", name);
    ret = read(0, message, 0x100);
    if (message[ret - 1] == '\n') {
        message[ret - 1] = 0;
        
    }

    postcard(name, message);
    puts("Goodbye!");
    
    return 0;
    
}
