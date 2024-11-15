#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		ft_builtin_exec(t_exec *exec, int in_exec);
int		ft_update_pwd(t_env **env);
int		ft_is_builtin(char *cmd);
void	ft_print_export(t_env *env);
int		ft_check_arg(char **str);
int		my_cd(char **cmd, t_mini **env);
int		my_echo(char **cmd);
int		my_env(char **cmd, t_mini *env);
int		my_exit(char **cmd, t_mini **env, int mode);
int		my_export(char **cmd, t_mini **env, char *key, char *value);
int		my_pwd(char **cmd, t_mini *env);
int		my_unset(char **cmd, t_mini **env);

#endif