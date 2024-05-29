/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoit <benoit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:54:50 by bdelamea          #+#    #+#             */
/*   Updated: 2024/05/24 08:52:48 by benoit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <termcap.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <fcntl.h>

# include "variables.h"
# include "libft.h"
# include "error.h"
# include "execution.h"
# include "lexer.h"
# include "structures.h"
# include "builtins.h"
# include "signals.h"

extern int	g_sig;

// Launching functions (env setting & TTY mode selection)
int		ft_interact(t_mini *env);
int		ft_non_interact_args(t_mini *env, char *av);
int		ft_non_interact_pipe(t_mini *env);
t_mini	*setup_env(char **input);

// Error functions
void	ft_perror(const char *format, ...);
int		ft_heredoc_lexer(char *input, t_mini *env);
int		ft_token_error(const char *message, t_basic *basic,
			t_token *token);

// Utils functions
int		ft_checkquote(char *input, int index);
int		ft_get_current_pid(void);
int		ft_is_spaces(char *str);
char	*ft_getenv(t_mini *env, char *var);
int		ft_max(int count, ...);
char	**ft_split_withquotes(char const *s, char c);
char	*ft_random_string(void);

// Print functions
void	ft_print_basic(t_basic *lst);
void	ft_print_env(t_env *env);
void	ft_print_token(t_token *lst);
void	ft_print_cmd(t_token *lst);
void	ft_print_table(char **table);

#endif