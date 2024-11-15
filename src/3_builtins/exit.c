#include "builtins.h"

int	ft_ret_val(char *str)
{
	int					i;
	long int			ret;
	unsigned long int	ul_ret;

	i = 0;
	ret = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && i != 1 && str[0] != '-')
			return (-1);
		i++;
	}
	ret = ft_atoi(str);
	if (ret < 0)
	{
		ul_ret = (unsigned long int)ret;
		while (ul_ret > 256)
			ul_ret %= 256;
		return ((int)ul_ret);
	}
	while (ret > 256)
		ret %= 256;
	return ((int)ret);
}

int	my_exit(char **cmd, t_mini **env, int mode)
{
	int	ret;
	int	no_num;

	if (mode == OUT_CHILD_EXEC)
		printf("exit\n");
	no_num = 0;
	ret = EXIT_SUCCESS;
	if (cmd[1])
	{
		ret = ft_ret_val(cmd[1]);
		if (ret < 0)
		{
			ft_perror("%s: %s: numeric argument required", cmd[0], cmd[1]);
			ret = 2;
			no_num = 1;
		}
	}
	if (cmd[1] && cmd[2] && !no_num)
		return (ft_perror("%s: too many arguments", cmd[0]), EXIT_FAILURE);
	(*env)->b_exit = 2;
	ft_closes(2, (*env)->fd_stdin, (*env)->fd_stdout);
	return (ret);
}
