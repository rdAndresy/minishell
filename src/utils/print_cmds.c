#include "minishell.h"

// Print the list of commands from the lexer
void	ft_print_basic(t_basic *lst)
{
	t_basic	*tmp;

	tmp = lst;
	printf(BOLD MAGENTA "#### COMMANDS ####" RESET_COLOR "\n");
	while (tmp)
	{
		printf(CYAN "cmd: " RESET_COLOR "%s\n", tmp->cmd);
		tmp = tmp->next;
	}
}

// Print the list of commands from the tokenizer
void	ft_print_token(t_token *lst)
{
	t_token	*tmp;
	t_redir	*tmp2;

	tmp = lst;
	printf(BOLD MAGENTA "#### COMMANDS ####" RESET_COLOR "\n");
	while (tmp)
	{
		printf(CYAN "cmd: " RESET_COLOR "%s\n", tmp->cmd);
		if (tmp->redir)
		{
			tmp2 = tmp->redir;
			printf(MAGENTA "### REDIR" RESET_COLOR "\n");
			while (tmp2)
			{
				printf(CYAN "type: " \
					RESET_COLOR "%d" CYAN " | file: " \
					RESET_COLOR "%s\n", tmp2->type, tmp2->file);
				tmp2 = tmp2->next;
			}
		}
		printf(BOLD YELLOW "-----------------" RESET_COLOR "\n");
		tmp = tmp->next;
	}
}

void	ft_print_redir(t_redir *tmp2)
{
	char	*prev;

	printf(MAGENTA "### REDIR" RESET_COLOR "\n");
	while (tmp2)
	{
		if (tmp2->previous)
			prev = tmp2->previous->file;
		else
			prev = NULL;
		printf(CYAN "type: " \
			RESET_COLOR "%d" CYAN " | file: " \
			RESET_COLOR "%s" CYAN " | prev: " \
			RESET_COLOR "%s" CYAN " | fd: " \
			RESET_COLOR "%d\n",
			tmp2->type, tmp2->file, prev, tmp2->fd);
		tmp2 = tmp2->next;
	}
}

// Print the list of commands and args from the parser
void	ft_print_cmd(t_token *lst)
{
	t_token	*tmp;
	int		i;

	tmp = lst;
	printf(BOLD MAGENTA "#### COMMANDS ####" RESET_COLOR "\n");
	while (tmp)
	{
		if (tmp->is_builtin)
			printf(CYAN "builtin: " RESET_COLOR "%s" CYAN " | index: " \
				RESET_COLOR "%d\n", tmp->cmd, tmp->index);
		else
			printf(CYAN "cmd: " RESET_COLOR "%s" CYAN " | index: " RESET_COLOR \
				"%d\n", tmp->cmd, tmp->index);
		if (tmp->args)
		{
			i = -1;
			while (tmp->args[++i])
				printf(CYAN "[arg_%d]: " RESET_COLOR "%s\n", i, tmp->args[i]);
		}
		if (tmp->redir)
			ft_print_redir(tmp->redir);
		printf(BOLD YELLOW "-----------------" RESET_COLOR "\n");
		tmp = tmp->next;
	}
}

// Print the list of commands from the tokenizer
void	ft_print_env(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	printf(BOLD MAGENTA "#### ENVIRONMENT ####" RESET_COLOR "\n");
	while (tmp)
	{
		printf(CYAN "key: " RESET_COLOR "%s\n", tmp->key);
		printf(CYAN "value: " RESET_COLOR "%s\n", tmp->value);
		printf(CYAN "index: " RESET_COLOR "%d\n", tmp->index);
		printf(BOLD YELLOW "-----------------" RESET_COLOR "\n");
		tmp = tmp->next;
	}
}
