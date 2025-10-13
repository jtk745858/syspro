#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_line(char **lines, int line_num, int total_lines) {
    if (line_num >= 1 && line_num <= total_lines) {
        char *line = lines[line_num - 1];
        size_t len = strcspn(line, "\n");
        printf("%.*s\n", (int)len, line);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "How to use: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int line_count = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_count++;
    }

    rewind(file);

    char **lines = (char **)malloc(line_count * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    int current_line = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lines[current_line] = (char *)malloc(strlen(buffer) + 1);
        if (lines[current_line] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        strcpy(lines[current_line], buffer);
        current_line++;
    }
    fclose(file);

    printf("File read success\n");
    printf("Total Line : %d\n", line_count);
    printf("You can choose 1 ~ %d Line\n", line_count);
    printf("Please 'Enter' the line to select : ");

    char input_buffer[256];
    fgets(input_buffer, sizeof(input_buffer), stdin);

    if (strchr(input_buffer, '-')) {
        int start, end;
        if (sscanf(input_buffer, "%d-%d", &start, &end) == 2) {
            for (int i = start; i <= end; i++) {
                print_line(lines, i, line_count);
            }
        }
		else {
            fprintf(stderr, "Error: Invalid range format.\n");
        }
    }
	else if (strchr(input_buffer, ',')) {
        char *token = strtok(input_buffer, ", \n");
        while (token != NULL) {
            int num = atoi(token);
            print_line(lines, num, line_count);
            token = strtok(NULL, ", \n");
        }
    } 
	else if (strchr(input_buffer, '*')) {
        for (int i = 1; i <= line_count; i++) {
            print_line(lines, i, line_count);
        }
    } 
	else {
        int num = atoi(input_buffer);
        if (num > 0) {
            print_line(lines, num, line_count);
        }
		else {
            fprintf(stderr, "Error: Invalid input.\n");
        }
    }

    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
