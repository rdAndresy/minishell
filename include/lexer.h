#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

int		checker(t_token *cmds, t_mini *env);
int		expander(t_token *cmds, t_mini *env);
int		lexer(char *input, t_mini *env, int i, int j);
int		parser(t_token *cmds, t_mini *env);
int		tokenizer(t_basic *cmds, t_mini *env);

// specific functions of parser
t_token	*ft_build_token(t_list *split, t_redir *redir, char *str, char *cmd);
int		ft_create_infile(t_token *cmds, t_redir *redir, t_mini *env,
			char *name);
int		ft_directory_error(t_token **tmp, struct stat buf, int res);
int		ft_expand(char **cmd, t_mini *env, int mode, int i);
void	ft_heredoc_n_perror(char *input_err, t_mini *env, char c, char d);
int		ft_parse_redir(t_token *cmds, t_token *tmp, t_redir *redir,
			t_mini *env);
int		ft_remove_token_quotes(t_token *cmds);
int		ft_rm_quotes(char **str);
t_list	*ft_split_cmd(char **cmd, int i, int j, int k);

#endif