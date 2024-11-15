#include "libft.h"

t_list	*ft_lstnew(char *raw, int bool_quotes)
{
	t_list	*tmp;

	if (!raw)
		return (NULL);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->content = raw;
	if (!tmp->content)
	{
		free(tmp);
		return (NULL);
	}
	tmp->info = bool_quotes;
	tmp->previous = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_basic	*ft_lstnew_basic(char *input, int *start, int end)
{
	t_basic	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	if (end >= 0)
	{
		tmp->cmd = ft_substr(input, *start, end - *start);
		if (!tmp->cmd)
		{
			free(tmp);
			return (NULL);
		}
	}
	else
		tmp->cmd = NULL;
	tmp->previous = NULL;
	tmp->next = NULL;
	*start = end + 1;
	return (tmp);
}

t_token	*ft_lstnew_token(char *cmd, t_redir *redir)
{
	t_token	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	if (cmd)
		tmp->cmd = cmd;
	else
		tmp->cmd = NULL;
	tmp->args = NULL;
	if (redir)
		tmp->redir = redir;
	else
		tmp->redir = NULL;
	tmp->index = -1;
	tmp->is_builtin = 0;
	tmp->err_redir = 0;
	tmp->previous = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_redir	*ft_lstnew_redir(char *file, t_type type)
{
	t_redir	*tmp;

	if (!file)
		return (NULL);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->file = file;
	tmp->type = type;
	tmp->fd = -1;
	tmp->previous = NULL;
	tmp->next = NULL;
	return (tmp);
}
