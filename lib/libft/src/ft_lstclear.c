#include "libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstclear_basic(t_basic **lst)
{
	t_basic	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->cmd)
			free((*lst)->cmd);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstclear_token(t_token **lst)
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->cmd)
			free((*lst)->cmd);
		if ((*lst)->args)
			ft_free_table((*lst)->args);
		if ((*lst)->redir)
			ft_lstclear_redir(&(*lst)->redir);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstclear_redir(t_redir **lst)
{
	t_redir	*tmp;

	while (*lst)
	{
		if ((*lst)->type == HERE_DOC
			&& !ft_strncmp((*lst)->file, ".tmpfile", 6))
			unlink((*lst)->file);
		tmp = (*lst)->next;
		free((*lst)->file);
		if ((*lst)->fd != -1)
			close((*lst)->fd);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstclear_env(t_mini **lst)
{
	t_env	*tmp_bash;

	while ((*lst)->env)
	{
		tmp_bash = (*lst)->env->next;
		ft_frees(2, (*lst)->env->key, (*lst)->env->value);
		free((*lst)->env);
		(*lst)->env = tmp_bash;
	}
	if ((*lst)->table_env)
		ft_free_table((*lst)->table_env);
	close((*lst)->fd_stdin);
	close((*lst)->fd_stdout);
	(*lst)->env = NULL;
	(*lst)->curr_cmds = NULL;
	free(*lst);
	*lst = NULL;
}
