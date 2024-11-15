#include "minishell.h"

// Check if there is an unclosed quote in the input command line
// or if a value is between quotes
// Returns un error if there is unclosed quotes
// Returns 1 if the value is between single quotes
// Returns 2 if the value is between double quotes
int	ft_checkquote(char *input, int index)
{
	int			i;
	int			in_sg_quote;
	int			in_db_quote;

	i = 0;
	in_sg_quote = 0;
	in_db_quote = 0;
	while (input[i])
	{
		if (input[i] == '\"' && !in_sg_quote)
			in_db_quote = !in_db_quote;
		else if (input[i] == '\'' && !in_db_quote)
			in_sg_quote = !in_sg_quote;
		if (index >= 0 && i == index && in_sg_quote)
			return (1);
		if (index >= 0 && i == index && in_db_quote)
			return (2);
		i++;
	}
	if (in_sg_quote || in_db_quote)
		return (ft_perror(
				"syntax error with unclosed \" or \' quotes"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_max(int count, ...)
{
	va_list	ap;
	int		max;
	int		current;

	va_start(ap, count);
	max = va_arg(ap, int);
	while (count > 1)
	{
		current = va_arg(ap, int);
		if (current > max)
			max = current;
		count--;
	}
	va_end(ap);
	return (max);
}

char	*ft_getenv(t_mini *env, char *var)
{
	t_env	*tmp;
	char	*res;

	tmp = env->env;
	while (tmp && var[0] != 0)
	{
		if (!ft_strncmp(tmp->key, var,
				ft_max(2, ft_strlen(tmp->key), ft_strlen(var))))
		{
			if (!tmp->value || !tmp->value[0])
				return (NULL);
			res = ft_strdup(tmp->value);
			if (!res)
				return (NULL);
			return (res);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_is_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_print_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		printf(CYAN "[%d]: " RESET_COLOR "%s\n", i, table[i]);
		i++;
	}
}
