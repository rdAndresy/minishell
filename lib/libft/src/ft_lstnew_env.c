#include "libft.h"

static t_env	*ft_create_node(char *key, char *value, int rank)
{
	char	*tmp_char;
	t_env	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->key = key;
	if (ft_strncmp(key, "SHLVL", 6) == 0)
	{
		tmp_char = ft_itoa(ft_atoi(value) + 1);
		free(value);
	}
	else if (value)
	{
		tmp_char = ft_strdup(value);
		free(value);
		if (!tmp_char)
			return (free(tmp), NULL);
	}
	else
		tmp_char = NULL;
	tmp->value = tmp_char;
	tmp->index = rank;
	tmp->next = NULL;
	return (tmp);
}

t_env	*ft_lstnew_env(char *str, int rank)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	if (!ft_strchr(str, '='))
	{
		key = ft_strdup(str);
		value = NULL;
	}
	else
	{
		key = ft_substr(str, 0, ft_strchr(str, '=') - str);
		if (!key)
			return (NULL);
		value = ft_strdup(str + ft_strlen(key) + 1);
		if (!value)
			return (free(key), NULL);
	}
	tmp = ft_create_node(key, value, rank);
	if (!tmp)
		return (free(key), free(value), NULL);
	return (tmp);
}
