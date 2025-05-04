#include "mini_shell.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_joinchar(char *s, char c)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(s) + 2);
	if (!ret)
		return (NULL);
	while (s && s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = c;
	i++;
	ret[i] = '\0';
	return (free(s), ret);
}

char *get_str(char *str, char **envp)
{
	int i = 0;
	while (envp[i] && str)
	{
		if(ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return(ft_strdup(envp[i] + (ft_strlen(str) + 1)));
		i++;
	}
	return (ft_strdup(""));
}