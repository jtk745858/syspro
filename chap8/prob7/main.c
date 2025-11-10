#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [-e[VARNAME]] [-u] [-g] [-i] [-p]\n\n", prog_name);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -e[VARNAME]\tPrint the value of the specified environment variable (VARNAME).\n");
    fprintf(stderr, "\tIf VARNAME is omitted, print all environment variables.\n");
    fprintf(stderr, "-u\tPrint the real and effective user IDs (RUID, EUID).\n");
    fprintf(stderr, "-g\tPrint the real and effective group IDs (RGID, EGID).\n");
    fprintf(stderr, "-i\tPrint the current process ID (PID).\n");
    fprintf(stderr, "-p\tPrint the parent process ID (PPID).\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        
        if (strncmp(argv[i], "-e", 2) == 0) {
            if (strlen(argv[i]) == 2) {
                char **env = environ;
                while (env && *env) {
                    printf("%s\n", *env);
                    env++;
                }
            } else {
                char *var_name = argv[i] + 2;
                char *value = getenv(var_name);

                if (value) {
                    printf("%s\n", value);
                } else {
                    fprintf(stderr, "Error: Environment variable '%s' not found.\n", var_name);
                }
            }
        } 
        else if (strcmp(argv[i], "-u") == 0) {
            printf("My Realistic User ID : %u\n", getuid());
            printf("My Valid User ID : %u\n", geteuid());
        } 
        else if (strcmp(argv[i], "-g") == 0) {
            printf("My Realistic Group ID : %u\n", getgid());
            printf("My Valid Group ID : %u\n", getegid());
        } 
        else if (strcmp(argv[i], "-i") == 0) {
            printf("my process number : [%d]\n", getpid());
        } 
        else if (strcmp(argv[i], "-p") == 0) {
            printf("my parent's process number : [%d]\n", getppid());
        } 
        else {
            fprintf(stderr, "Error: Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    return 0;
}
