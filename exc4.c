#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

void copy_file_chunked(FILE *in, FILE *out) {
    char buffer[BUFFER_SIZE];
    size_t read_bytes;

    while ((read_bytes = fread(buffer, 1, BUFFER_SIZE, in)) > 0) {
        fwrite(buffer, 1, read_bytes, out);
    }
}

void copy_file(FILE *in, FILE* out){

    fseek(in, 0, SEEK_END); 
    long length = ftell(in); 
    rewind(in);   

    char *content = malloc(sizeof(char)* length);   

    size_t bytes_read = fread(content, 1, length, in);

    fputs(content, out);
}

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr,"The argc should be 3 only!");
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if((in ==  NULL) || (out == NULL)){
        fprintf(stderr, "File does not exist!");
        return 1;
    }

    copy_file_chunked(in, out);

    fclose(in); fclose(out);
    return 0;
}