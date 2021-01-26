#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#    define MINIRENT_IMPLEMENTATION
#    include "minirent.h"
#else
#    include <dirent.h>
#endif // _WIN32

int main(int argc, char *argv[])
{
    const char *dir_path = ".";

    if (argc >= 2) {
        dir_path = argv[1];
    }

    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        fprintf(stderr, "ERROR: could not open directory %s: %s\n",
                dir_path, strerror(errno));
        exit(1);
    }

    errno = 0;
    struct dirent *dp = NULL;
    while ((dp = readdir(dir))) {
        // TODO: the output of ls is not sorted
        printf("%s\n", dp->d_name);
    }

    if (errno) {
        fprintf(stderr, "ERROR: could not read directory %s: %s\n",
                dir_path, strerror(errno));
        exit(1);
    }

    if (closedir(dir) < 0) {
        fprintf(stderr, "ERROR: could not close directory %s: %s\n",
                dir_path, strerror(errno));
        exit(1);
    }

    return 0;
}
