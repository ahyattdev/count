#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define PRINTUSAGE(file) fprintf(file, "Usage: %s [token] [file]\n", argv[0]);

#define PRINTERROR() printf("%s: %s: %s\n", argv[0], filename, strerror(errno));

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        PRINTUSAGE(stderr);
        return EXIT_FAILURE;
    } else if (strcmp(argv[1], "-h") || strcmp(argv[1], "--help")){
        PRINTUSAGE(stdout);
        return EXIT_SUCCESS;
    } else if (argc != 3) {
        PRINTUSAGE(stderr);
        return EXIT_FAILURE;
    }
    const char *token = argv[1];
    const char *filename = argv[2];
    FILE *file;
    if (!(file = fopen(filename, "rb"))) {
        PRINTERROR();
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
    printf("%i\n", count);
    return EXIT_SUCCESS;
}
