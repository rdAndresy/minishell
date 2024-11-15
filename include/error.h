#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define ERROR_NO_ENV "No environment"
# define ERROR_CMD_NOT_FOUND "Not found in PATH"
# define ERROR_NO_SUCH_FOD "Not found at address"
# define ERROR_NOT_A_DIR "Command is not a directory"
# define ERROR_DIR_NOT_FOUND "Command is a directory"
# define ERROR_NO_CMD "No command given"
# define ERROR_EMPTY_CMD "Empty command given"

# define EXIT_PARSING 2
# define EXIT_MALLOC 255
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NO_SUCH_FOD 127
# define EXIT_DIR_NOT_FOUND 126
# define EXIT_NOT_A_DIR 126
# define EXIT_REDIR_FAILED 1
# define EXIT_NO_CMD -1
# define EXIT_EMPTY_CMD 127

#endif