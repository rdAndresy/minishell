#include "builtins.h"

int	ft_is_not_nflag(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
		i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	my_echo(char **cmd)
{
	int	i;
	int	b_printed;

	i = 1;
	b_printed = 0;
	if (!cmd[i])
		return (printf("\n"), EXIT_SUCCESS);
	if (!ft_is_not_nflag(cmd[i]))
		i++;
	while (cmd[i])
	{
		b_printed = 1;
		if (cmd[i + 1])
			printf("%s ", cmd[i]);
		else
			printf("%s", cmd[i]);
		i++;
	}
	if (!ft_is_not_nflag(cmd[0]) && b_printed)
		printf("\n");
	return (EXIT_SUCCESS);
}
