#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_data
{
    char buf[2];
    char *origin_ptr[1024];
    char *buffer[1024];
    char *newline;
    int a;
    int words;
}t_data;

char *get_next_line(int fd);

#endif