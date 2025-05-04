#include "../mini_shell.h"

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


char *ft_substr(const char *s, int start, int len)
{
    char    *sub;
    int     i = 0;

    if (!s)
        return (NULL);
    sub = malloc(len + 1);
    if (!sub)
        return (NULL);
    while (i < len && s[start + i])
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	new = malloc(i + j + 1);
	if (!new)
		return (NULL);
	j = -1;
	while (s1 && s1[++j])
		new[j] = s1[j];
	(j == -1) && (j = 0);
	i = -1;
	while (s2 && s2[++i])
		new[j + i] = s2[i];
	new[j + i] = '\0';
	return (free(s1), new);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


char	*ft_strchr(const char *str, int c)
{
	unsigned char	c1;
	int				i;

	c1 = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == c1)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}