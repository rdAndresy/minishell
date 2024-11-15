#include "builtins.h"

int	my_pwd(char **cmd, t_mini *env)
{
	char	cwd[PATH_MAX];

	if (cmd || !cmd || env || !env)
	{
		if (getcwd(cwd, PATH_MAX))
			return (ft_fprintf(STDOUT_FILENO, "%s\n", cwd), EXIT_SUCCESS);
		else
			return (ft_fprintf(STDERR_FILENO,
					"pwd: error retrieving current directory: " \
					"getcwd: cannot access parent directories: %s\n",
					strerror(errno)), EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
