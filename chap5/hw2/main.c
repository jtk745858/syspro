#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "How to use: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char **lines = NULL;
    char buffer[MAX];
    int line_count = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_count++;
        lines = (char **)realloc(lines, line_count * sizeof(char *));
        if (lines == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        lines[line_count - 1] = (char *)malloc(strlen(buffer) + 1);
        if (lines[line_count - 1] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        strcpy(lines[line_count - 1], buffer);
    }
    fclose(file);

    for (int i = line_count - 1; i >= 0; i--) {
        char *line = lines[i];
        size_t len = strcspn(line, "\n");
        printf("%.*s\n", (int)len, line);
    }

    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
