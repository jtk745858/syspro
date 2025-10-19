#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

int i_option = 0;
int p_option = 0;
int Q_option = 0;

char type(mode_t);
char *perm(mode_t);
void printStat(char *pathname, char *file, struct stat *st);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int opt;

    while ((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch (opt) {
            case 'i':
                i_option = 1;
                break;
            case 'p':
                p_option = 1;
                break;
            case 'Q':
                Q_option = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-ipQ] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc)
        dir = ".";
    else
        dir = argv[optind];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st);
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st)
{
    if (i_option) {
        printf("%-8ld ", (long)st->st_ino);
    }

    printf("%5d ", (int)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3d ", (int)st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name,
                       getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", (long)st->st_size);
    printf("%.12s ", ctime(&st->st_mtime)+4);

    if (Q_option) {
        printf("\"%s\"", file);
    } else {
        printf("%s", file);
    }

    if (p_option && S_ISDIR(st->st_mode)) {
        printf("/");
    }

    printf("\n");
}

char type(mode_t mode)
{
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
    return '?';
}

char* perm(mode_t mode)
{
    static char perms[10] = "---------";

    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';

    return perms;
}
