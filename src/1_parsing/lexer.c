#include "lexer.h"

int	ft_check_blanks(t_basic **cmds, t_mini *env, char *str)
{
	t_basic	*tmp;
	int		i;

	tmp = *cmds;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i] && (tmp->cmd[i] == ' ' || tmp->cmd[i] == '\t'))
			i++;
		if (!tmp->cmd[i] && (tmp->next || tmp != *cmds))
		{
			ft_lstclear_basic(cmds);
			ft_heredoc_lexer(ft_substr(str, 0, i), env);
			if (!g_sig)
				ft_perror("syntax error near unexpected token `|\'");
			return (EXIT_PARSING);
		}
		else if (!tmp->cmd[i] && !tmp->next)
			return (ft_lstclear_basic(cmds), env->return_val);
		tmp = tmp->next;
	}
	free(str);
	return (-1);
}

// Check if the first character of the input command line is a | or 
int	ft_check_extrems(char *str, int extreme, t_mini *env, int i)
{
	if (extreme == END)
	{
		i = ft_strlen(str) - 1;
		while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
			i--;
	}
	if (i < 0)
		i = 0;
	if (str[i] == '|')
	{
		ft_heredoc_lexer(ft_substr(str, 0, i), env);
		if (!g_sig && (!str[i + 1] || !ft_is_spaces(str + i + 1)))
			ft_perror("syntax error near unexpected token `newline\'");
		else if (!g_sig)
			ft_perror("syntax error near unexpected token `|\'");
		return (EXIT_FAILURE);
	}
	if ((str[i] == '<' && (!str[i + 1] || !ft_is_spaces(str + i + 1)))
		|| (str[i] == '>' && (!str[i + 1] || !ft_is_spaces(str + i + 1))))
	{
		if (!ft_heredoc_lexer(ft_substr(str, 0, i), env) && !g_sig)
			ft_perror("syntax error near unexpected token `newline\'");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_token_nb(char *str, char c, char *str_err, t_mini *env)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	if (str[i] && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
		return (ft_heredoc_n_perror(str_err, env, str[i], 0), -1);
	if (i > 1 && (c == '|' || i == 3))
		return (ft_heredoc_n_perror(str_err, env, c, 0), -1);
	else if (i > 2)
		return (ft_heredoc_n_perror(str_err, env, c, c), -1);
	else
	{
		j = 0;
		while (str[i + j] && (str[i + j] == ' ' || str[i + j] == '\t'))
			j++;
		if (str[i + j] && ((str[0] != '|' && (str[i + j] == '<'
						|| str[i + j] == '>')) || str[i + j] == '|'))
			return (ft_heredoc_n_perror(str_err, env, str[i + j], 0), -1);
	}
	if (i == 1 || (i == 2 && (c == '>' || c == '<')))
		return (free(str_err), i);
	return (free(str_err), 0);
}

// Check if there is a || condition in the input command line
// quotes !!!
int	ft_check_tokens(char *str, t_mini *env)
{
	int	i;
	int	j;

	if (ft_check_extrems(str, START, env, 0))
		return (EXIT_FAILURE);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && ((str[i] != '|' && str[i] != '<' && str[i] != '>')
				|| ft_checkquote(str, i)))
			i++;
		if (str[i] == '<')
			j += ft_token_nb(str + i, str[i], ft_substr(str, 0, i), env);
		else if (str[i] == '>')
			j += ft_token_nb(str + i, str[i], ft_substr(str, 0, i), env);
		else
			j += ft_token_nb(str + i, str[i], ft_substr(str, 0, i), env);
		if (j == -1)
			return (EXIT_FAILURE);
		else
			i += j;
	}
	return (ft_check_extrems(str, END, env, 0));
}

// Separate input command line into a linked list of commands for each pipe
// i is the index of the input command line caught by readline
// j is the index of the command
// k is the start position of the next command
int	lexer(char *input, t_mini *env, int i, int j)
{
	t_basic		*cmds;

	if (!input || ft_checkquote(input, -1) || ft_check_tokens(input, env))
	{
		if (g_sig)
			return (g_sig = 0, EXIT_INT);
		return (EXIT_PARSING);
	}
	cmds = NULL;
	while (input[i])
	{
		if (input[i] == '|' && !ft_checkquote(input, i))
			ft_lstadd_back_basic(&cmds, ft_lstnew_basic(input, &j, i));
		else if (!input[i + 1] && input[i] != '|')
			ft_lstadd_back_basic(&cmds, ft_lstnew_basic(input, &j, i + 1));
		if (j != 0 && !cmds)
			return (free(input), ft_perror("lexer: malloc fail"), EXIT_MALLOC);
		i++;
	}
	j = ft_check_blanks(&cmds, env, input);
	if (j != -1)
		return (j);
	if (g_sig)
		return (ft_lstclear_basic(&cmds), g_sig = 0, EXIT_INT);
	return (tokenizer(cmds, env));
}
