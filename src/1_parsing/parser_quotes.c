#include "lexer.h"

// Separates the string into substrings between quotes and without quotes
int	ft_lstcreate(t_list **lst, char *str, int i)
{
	int		j;
	int		in_quotes;

	in_quotes = ft_checkquote(str, i);
	if (in_quotes == 0)
	{
		j = 0;
		while (str[i + j] && str[i + j] != '\'' && str[i + j] != '\"')
			j++;
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, i, j), 0));
	}
	else
	{
		j = 1;
		while (str[i + j] && ((in_quotes == 1 && str[i + j] != '\'')
				|| (in_quotes == 2 && str[i + j] != '\"')))
			j++;
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, i, j + 1), 1));
		j++;
	}
	if (!ft_lstlast(*lst))
		(ft_lstclear(lst), j = -1);
	return (j);
}

// Converts a list of strings into a single string after quotes removal
char	*ft_lst_to_str(t_list *lst, char *res)
{
	char	*no_quotes;
	char	*old;
	t_list	*tmp;

	if (!res)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (tmp->info == NO_QUOTES)
			no_quotes = ft_strdup(tmp->content);
		else
			no_quotes = ft_substr(tmp->content, 1, ft_strlen(tmp->content) - 2);
		if (!no_quotes)
			return (NULL);
		old = ft_strdup(res);
		if (!old)
			return (free(no_quotes), NULL);
		(free(res), res = ft_strjoin(old, no_quotes));
		if (!res)
			return (NULL);
		(ft_frees(2, no_quotes, old), tmp = tmp->next);
	}
	return (res);
}

// Remove the quotes from the string
int	ft_rm_quotes(char **str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\'' && (*str)[i] != '\"')
		i++;
	tmp = ft_lstnew(ft_substr(*str, 0, i), 0);
	if (!tmp)
		return (EXIT_FAILURE);
	while (i != -1 && (*str)[i])
		i += ft_lstcreate(&tmp, *str, i);
	if (i == -1)
		return (EXIT_FAILURE);
	free(*str);
	*str = ft_lst_to_str(tmp, ft_strdup(""));
	ft_lstclear(&tmp);
	if (!*str)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_remove_token_quotes(t_token *cmds)
{
	int	i;

	if (ft_rm_quotes(&cmds->cmd))
		return (EXIT_FAILURE);
	i = 0;
	while (cmds && cmds->args[i])
		if (ft_rm_quotes(&cmds->args[i++]))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
