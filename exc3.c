#include <stdio.h>
int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr,"the argc should be 2 only!");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        return 1;
    }
    char c = fgetc(file);
    while(c != EOF){
        printf("%c\n", c);
        c = fgetc(file);
    }
    fclose(file);
    return 0;
}