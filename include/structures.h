#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_env
{
	char				*key;
	char				*value;
	int					index;
	struct s_env		*next;
}	t_env;

typedef struct s_basic_cmds
{
	char				*cmd;
	struct s_basic_cmds	*previous;
	struct s_basic_cmds	*next;
}	t_basic;

typedef enum e_redir_type
{
	HERE_DOC = 1,
	INFILE,
	APPEND,
	OUTFILE,
	ERROR,
}	t_type;

typedef struct s_redir
{
	char			*file;
	t_type			type;
	int				fd;
	struct s_redir	*previous;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token_cmds
{
	char				*cmd;
	char				**args;
	t_redir				*redir;
	int					err_redir;
	int					is_builtin;
	int					index;
	struct s_token_cmds	*previous;
	struct s_token_cmds	*next;
}	t_token;

typedef struct s_mini
{
	t_env			*env;
	char			**table_env;
	t_token			*curr_cmds;
	int				b_interact;
	int				b_exit;
	int				fd_stdin;
	int				fd_stdout;
	int				return_val;
	int				last_signal;
}	t_mini;

typedef struct s_exec
{
	t_token	*cmds;
	t_token	*curr;
	t_mini	*env;
	pid_t	pid;
	int		final_status;
	int		fd[2];
	int		fdp[2];
}	t_exec;

#endif
