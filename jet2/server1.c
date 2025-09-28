#include <stdio.h>
#include <string.h>
#include <math.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>


struct ticket {
    char title[100];
    char first_name[100];
    char last_name[100];
    char seat[100];
    char cabin[100];
};


int base64_encode(const char* message, size_t length, char* buffer) {
    BIO *bio, *b64;
    FILE* stream;
    int encodedSize = 4*ceil((double)length/3);

    stream = fmemopen(buffer, encodedSize+1, "w");
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_fp(stream, BIO_NOCLOSE);
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, message, length);
    BIO_flush(bio);
    BIO_free_all(bio);
    fclose(stream);

    while(*buffer++) {
        if(*buffer == '=') *buffer = 0;
        else if(*buffer == '+') *buffer = '-';
        else if(*buffer == '/') *buffer = '_';
    }

    return 0;
}

char* make_ticket_code(struct ticket* ticket){
    char header[1000];
    char body[1000];
    snprintf(header, sizeof(header), "{\"alg\": \"%s\", \"typ\": \"%s\"}", "HS256", "JWT");

    snprintf(body, sizeof(body), "{\"name\": \"%s %s %s\", \"cabin\": \"%s\", \"seat\": \"%s\"}",
        ticket->title, ticket->first_name, ticket->last_name,
        ticket->cabin,
        ticket->seat
        );

    char header_base64[5000];
    char body_base64[5000];

    base64_encode(header, strlen(header), header_base64);
    base64_encode(body, strlen(body), body_base64);

    char jwt_payload[10000];
    snprintf(jwt_payload, sizeof(jwt_payload), "%s.%s", header_base64, body_base64);

    char key[1024] = {0};
    FILE *f = fopen("flag.txt", "r");
    fgets(key, 1024, f);

    char hash[32];
    int hash_len = sizeof(hash);
    char hash_base64[500];

    HMAC(EVP_sha256(), key, strlen(key), jwt_payload, strlen(jwt_payload), hash, &hash_len);
    base64_encode(hash, hash_len, hash_base64);

    char* token = malloc(15000);
    snprintf(token, 15000, "%s.%s", jwt_payload, hash_base64);
    return token;
}


int main(){
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);

    struct ticket ticket;
    printf("===================\n");
    printf("Jet2 Booking System\n");

    printf("Title> ");
    scanf("%99s", ticket.title);

    printf("First Name> ");
    scanf("%99s", ticket.first_name);

    printf("Last Name> ");
    scanf("%99s", ticket.last_name);

    printf("Seat> ");
    scanf("%99s", ticket.seat);

    strcpy(ticket.cabin, "Economy");
    


    printf("===================\n");

    printf("Boarding Pass\n");
    printf("Name: %s %s %s\n", ticket.title, ticket.first_name, ticket.last_name);
    printf("Seat: %s %s\n",ticket.cabin, ticket.seat);
    printf("Ticket Code: %s\n", make_ticket_code(&ticket));
}