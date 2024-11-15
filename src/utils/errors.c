#include "minishell.h"

// Exit the current line execution with a failure message in lexer.c part
void	ft_perror(const char *format, ...)
{
	int			i;
	va_list		args;

	ft_fprintf(STDERR_FILENO, "shell: ");
	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
			ft_putchar_fd(format[i], STDERR_FILENO);
		else
		{
			if (format[i + 1] == 'c')
				ft_fprintf(STDERR_FILENO, "%c", va_arg(args, int));
			else if (format[i + 1] == 's')
				ft_fprintf(STDERR_FILENO, "%s", va_arg(args, char *));
			else if (format[i + 1] == 'd')
				ft_fprintf(STDERR_FILENO, "%d", va_arg(args, int));
			i++;
		}
		i++;
	}
	va_end(args);
	ft_fprintf(STDERR_FILENO, "\n");
}

// Exit the current line execution with a failure message in tokenizer.c part
int	ft_token_error(const char *message, t_basic *basic, t_token *token)
{
	if (message)
		ft_fprintf(STDERR_FILENO, "shell: %s\n", message);
	ft_lstclear_basic(&basic);
	ft_lstclear_token(&token);
	return (EXIT_MALLOC);
}
