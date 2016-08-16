#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUsage(FILE *file) {
    fputs("Usage: count [token] [file]", file);
}
int main(int argc, const char *argv[]) {
    if (argc == 1) {
        printUsage(stderr);
        return EXIT_FAILURE;
    } else if (strcmp(argv[1], "-h") || strcmp(argv[1], "--help")){
        printUsage(stdout);
        return EXIT_SUCCESS;
    } else if (argc != 3) {
        printUsage(stderr);
        return EXIT_FAILURE;
    }
    const char *token = argv[1];
    const char *filename = argv[2];
    FILE *file;
    if (!(file = fopen(filename, "rb"))) {
        fputs(strcat("Could not open file: ", filename), stderr);
        return EXIT_FAILURE;
    }

    char charInFile;
    int indexInToken = 0;
    int count = 0;

    // Read every char in the file sequentially
    // Keep track of how many consecutive chars match the token
    while ((charInFile = fgetc(file)) != EOF) {
        if (charInFile == token[indexInToken]) {
            indexInToken ++;
        } else {
            indexInToken = 0;
        }
        if (indexInToken == strlen(token)) {
            count ++;
            indexInToken = 0;
        }
    }


    fclose(file);
    printf("%i", count);
    return EXIT_SUCCESS;
}
