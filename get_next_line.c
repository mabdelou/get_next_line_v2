#include "get_next_line.h"


int ft_strlen_to(char *str,char to)
{
    int a;

    a = 0;
    while(str[++a] != to);
    return (a);
}

char *ft_strjoin(char *s1, char *s2)
{
    int a;
    int b;
    int size;
    char *new_str;

    a = -1;
    b = -1;
    if(s1 == NULL)
    {
        s1 = malloc(sizeof(char) * 1);
        s1[0] = 0;
    }
    size = ft_strlen_to(s1, '\0') + ft_strlen_to(s2, '\0');
    new_str = malloc(sizeof(char) * size + 1);
    if(!new_str)
        return (NULL);
    while(s1[++a] && a < size)
       new_str[a] = s1[a];
    while(s2[++b] && (a + b) < size)
       new_str[a + b] = s2[b];
    new_str[a + b] = '\0';
    free(s1);
    return (new_str);
}

char *ft_newline(char *line)
{
    int a;
    char *newline;

    a = -1;
    if(!line || line[0] == '\0')
        return(NULL);
    newline = malloc(sizeof(char) * ft_strlen_to(line, '\n') + 2);
    if(!newline)
        return (NULL);
    while(line[++a] && line[a] != '\n')
        newline[a] = line[a];
    newline[a] = '\n';
    newline[a + 1] = '\0';
    return (newline);
}

char *get_next_line(int fd)
{
    static t_data data;
    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if(data.buffer[fd] == NULL)
    {
        data.a = 0;
        data.buf[1] = 0;
        while(++data.a)
        {
            data.words = read(fd, &data.buf[0],BUFFER_SIZE);
            if(data.words == 0 || data.words == -1)
                break;
            data.buffer[fd] = ft_strjoin(data.buffer[fd], data.buf);
        }
        if(data.words == -1)
            return (NULL);
        data.origin_ptr[fd] = data.buffer[fd];
    }
    data.newline = ft_newline(data.buffer[fd]);
    if(data.buffer[fd][0])
        data.buffer[fd] = &data.buffer[fd][ft_strlen_to(data.buffer[fd], '\n')  + 1];
    return (data.newline);
}

int main()
{
    int fd;
    int fd2;
    int loop;
    char *line;

    fd = open("get_next_line.c", O_RDWR);
    fd2 = open("text", O_RDWR);
    loop = 13;
    while(--loop)
    {
        line = get_next_line(fd2);
        printf("%s",line);
        free(line);
    }
    close(fd);
    close(fd2);
}
