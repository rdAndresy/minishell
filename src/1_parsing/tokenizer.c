#include "lexer.h"

// Check the type of redirection
t_type	ft_check_type(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (ft_strncmp(str + i, "<>", 2) == 0)
		return (OUTFILE);
	else if (ft_strncmp(str + i, "><", 2) == 0)
		return (OUTFILE);
	else if (ft_strncmp(str + i, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(str + i, "<", 1) == 0)
		return (INFILE);
	else if (ft_strncmp(str + i, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(str + i, ">", 1) == 0)
		return (OUTFILE);
	else
		return (ERROR);
	return (0);
}

// Build a new node in the token linked list with the command and redirections
t_token	*ft_build_token(t_list *split, t_redir *redir, char *str, char *cmd)
{
	t_list	*tmp;

	tmp = split;
	while (tmp && cmd)
	{
		if (tmp->info == CMD)
		{
			str = ft_strdup(cmd);
			if (!str)
				return (free(cmd), ft_lstclear_redir(&redir), NULL);
			(free(cmd), cmd = ft_strjoin(str, tmp->content), free(str));
			if (!cmd)
				return (ft_lstclear_redir(&redir), NULL);
		}
		else if (tmp->info == REDIR)
		{
			ft_lstadd_back_redir(&redir,
				ft_lstnew_redir(ft_strdup(tmp->content),
					ft_check_type(tmp->previous->content)));
			if (!redir)
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (ft_lstnew_token(cmd, redir));
}

// Create a new node in the temporary linked list
// with the command, token or redirection
int	ft_create_node(t_list **res, char **cmd, int len)
{
	t_list	*new;
	char	*str;
	char	*tmp;

	if (len == 0)
		return (EXIT_SUCCESS);
	str = ft_substr(*cmd, 0, len);
	if (!str)
		return (EXIT_FAILURE);
	if ((ft_strchr(str, '<') && !ft_checkquote(str, ft_strchr(str, '<') - str))
		|| (ft_strchr(str, '>')
			&& !ft_checkquote(str, ft_strchr(str, '>') - str)))
		new = ft_lstnew(str, TOKEN);
	else if (*res && ft_lstlast(*res)->info == 3)
		new = ft_lstnew(str, REDIR);
	else
		new = ft_lstnew(str, CMD);
	if (!new)
		return (free(str), EXIT_FAILURE);
	tmp = ft_substr(*cmd, 0 + len, ft_strlen(*cmd) - len);
	if (!tmp)
		ft_lstclear(res);
	free(*cmd);
	*cmd = tmp;
	return (ft_lstadd_back(res, new), EXIT_SUCCESS);
}

// Split the command line into substrings of commands, tokens and redirections
t_list	*ft_split_cmd(char **cmd, int i, int j, int k)
{
	t_list	*res;

	res = NULL;
	while ((*cmd)[i])
	{
		i = 0;
		while ((*cmd)[i] && (ft_checkquote(*cmd, i) || (!ft_checkquote(*cmd, i)
					&& (*cmd)[i] != '<' && (*cmd)[i] != '>')))
			i++;
		j = 0;
		while ((*cmd)[i + j] && !ft_checkquote(*cmd, i + j) && ((*cmd)[i + j]
				== '<' || (*cmd)[i + j] == '>' || (*cmd)[i + j] == ' '))
			j++;
		k = 0;
		while ((*cmd)[i + j + k]
			&& ((!ft_checkquote(*cmd, i + j + k) && ((*cmd)[i + j + k] != '<'
			&& (*cmd)[i + j + k] != '>' && (*cmd)[i + j + k] != ' '))
			|| ft_checkquote(*cmd, i + j + k)))
			k++;
		if (ft_create_node(&res, cmd, i) || ft_create_node(&res, cmd, j)
			|| ft_create_node(&res, cmd, k))
			return (NULL);
		i = 0;
	}
	return (res);
}

// Separate redirections and command resings before expanding the command line
int	tokenizer(t_basic *cmd, t_mini *env)
{
	t_token	*res;
	t_list	*split;
	t_basic	*tmp;

	tmp = cmd;
	res = NULL;
	while (tmp)
	{
		split = ft_split_cmd(&tmp->cmd, 0, 0, 0);
		if (!split)
			return (ft_token_error("tokenizer: malloc failed", cmd, NULL));
		ft_lstadd_back_token(&res,
			ft_build_token(split, NULL, NULL, ft_strdup("")));
		(ft_lstclear(&split), tmp = tmp->next);
		if (!res)
			return (ft_token_error("tokenizer: malloc failed", cmd, NULL));
	}
	env->curr_cmds = res;
	ft_lstclear_basic(&cmd);
	if (!env->b_interact)
		ft_lstclear(&split);
	return (expander(res, env));
}
