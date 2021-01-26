[![Build Status](https://github.com/tsoding/minirent/workflows/CI/badge.svg)](https://github.com/tsoding/minirent/actions)

# minirent

A subset of [dirent](https://pubs.opengroup.org/onlinepubs/9699919799/) interface for Windows.

The code that works with minirent must work with the dirent.

## Usage

[minirent.h](./minirent.h) is an [stb-style](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt) header-only library. That means that when you just include it it does not include the implementations of the functions. You have to define `MINIRENT_IMPLEMENTATION` macro:

```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#    define MINIRENT_IMPLEMENTATION
#    include <minirent.h>
#else
#    include <dirent.h>
#endif // _WIN32

int main(void)
{
    DIR *dir = opendir(".");
    assert(dir);

    errno = 0;
    struct dirent *dp = NULL;
    while ((dp = readdir(dir))) {
        printf("%s\n", dp->d_name);
    }
    assert(errno == 0);

    int err = closedir(dir);
    assert(err == 0);

    return 0;
}
```

For more information see [./examples/](./examples/) folder.
