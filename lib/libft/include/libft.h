#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include "structures.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

typedef enum e_string_info
{
	NO_QUOTES = 0,
	HAS_QUOTES = 1,
	CMD,
	TOKEN,
	REDIR,
}	t_info;

typedef struct s_list
{
	char			*content;
	t_info			info;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

int				ft_abs(int x);
void			ft_del(char *val);
long int		ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			ft_closes(int count, ...);
int				ft_fprintf(int fd, const char *format, ...);
void			ft_free_table(char **str);
void			ft_frees(int count, ...);
int				ft_isalnum(int c);
int				ft_isalpha(char *str);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_back_basic(t_basic **alst, t_basic *new);
void			ft_lstadd_back_token(t_token **alst, t_token *new);
void			ft_lstadd_back_redir(t_redir **alst, t_redir *new);
void			ft_lstadd_back_env(t_env **alst, t_env *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst);
void			ft_lstclear_basic(t_basic **lst);
void			ft_lstclear_token(t_token **lst);
void			ft_lstclear_redir(t_redir **lst);
void			ft_lstclear_env(t_mini **lst);
void			ft_lstft_delone(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(char *));
t_list			*ft_lstlast(t_list *lst);
t_basic			*ft_lstlast_basic(t_basic *lst);
t_token			*ft_lstlast_token(t_token *lst);
t_redir			*ft_lstlast_redir(t_redir *lst);
t_env			*ft_lstlast_env(t_env *lst);
t_list			*ft_lstnew(char *raw, int bool_quotes);
t_basic			*ft_lstnew_basic(char *input, int *start, int end);
t_token			*ft_lstnew_token(char *cmd, t_redir *redir);
t_redir			*ft_lstnew_redir(char *file, t_type type);
t_env			*ft_lstnew_env(char *str, int rank);
int				ft_lstsize(t_list *lst);
int				ft_lstsize_env(t_env *lst);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *b, int c, size_t len);
int				ft_printf(const char *format, ...);
int				ft_printstr(char *str);
int				ft_printstr_fd(char *str, int fd);
int				ft_printptr(void *ptr);
int				ft_printptr_fd(void *ptr, int fd);
int				ft_printnbr(long int nbr);
int				ft_printnbr_fd(long int nbr, int fd);
int				ft_printuns(unsigned int nbr);
int				ft_printuns_fd(unsigned int nbr, int fd);
int				ft_printhex(unsigned long int nbr, int conv);
int				ft_printhex_fd(unsigned long int nbr, int conv, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s1);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, int start, size_t len);
int				ft_tablelen(char *table[]);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*get_next_line(int fd);

#endif