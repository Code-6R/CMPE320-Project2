#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*used https://www.geeksforgeeks.org/c-program-merge-contents-two-files-third-file/
 * as a reference
 */
FILE *fileHandler(int argc, char *argv[]) {
    FILE *fp[argc];
    if (argc == 1) {
        fprintf(stdout, "wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE); // exit(1)
    }
    for (int i = 1; i < argc; i++) {
        fp[i] = fopen(argv[i], "r");
    }
    fp[0] = fopen("combined.txt", "w");
    char ch;
    int i = argc - 1;
    while ( i != 0) {
        while ((ch = fgetc(fp[i])) != EOF)
            fputc(ch, fp[0]);
        i--;
    }
    for (i = 0; i < argc; i++) {
        fclose(fp[i]);
    }
    return fopen("combined.txt", "r");
}

int main(int argc, char *argv[]) {
    int j = 0, k = 0, n = 1;
    int *count = calloc(n, sizeof(int));
    char *chr = malloc(sizeof(char) * n);
    char *line = NULL;
    FILE *input = fileHandler(argc, argv);
    size_t size = 0;
    while (getline(&line, &size, input) != -1) {
        int charPos = 0;
        while (line[charPos] != '\0') {
            j = charPos;
            chr[k] = line[charPos];
            while (chr[k] == line[j])
                j++;
            count[k] = j - charPos;
            if (chr[k] == chr[k - 1] && k > 0) {
                count[k - 1] += count[k];
                k--;
                n--;
            }
            n++;
            count = realloc(count, sizeof(int) * n);
            chr = realloc(chr, sizeof(char) * n);
            if (count == NULL || chr == NULL) {
                free(count);
                free(chr);
                exit(EXIT_FAILURE);
            }
            charPos = j;
            k++;
        }
    }
    count[k] = 0;
    chr[k] = '\0';
    k = 0;
    while (chr[k] != '\0') {
        fwrite(&count[k], 4, 1, stdout);
        fprintf(stdout, "%c", chr[k]);
        k++;
    }
    fclose(input);
    free(count);
    free(chr);
    remove("combined.txt");
    return 0;
}
