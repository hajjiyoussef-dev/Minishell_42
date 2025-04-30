#include "mini_shell.h"

char *ft_strdup(char *str)
{
    int i;
    char *line;
    
    i = 0;
    while (str[i])
        i++;
    line = malloc(i + 1);
    if (!line)
        return (NULL);
    i = 0;
    while (str[i])
    {
        line[i] = str[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}