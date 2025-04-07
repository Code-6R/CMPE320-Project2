#include <stddef.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int charPos = 0, j = 0, count = 0;
    char *line = NULL;
    FILE *input = NULL;
    size_t size = 0;
    input = fopen(argv[1], "r");

    while (getline(&line, &size, input) != -1) {
        line[strlen(line) - 1] = '\0';
        while (line[charPos] != '\0') {
            j = charPos;
            char chr = line[charPos];
            while (chr == line[j]) {
                j++;
            }
            j++;
            count = j - charPos;
            fwrite(&count, sizeof(count), 1, stdout);
            fprintf(stdout, "%c", chr);
            charPos = j;
        }

        fclose(input);
    }
    return 0;
}
