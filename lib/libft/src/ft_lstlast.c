#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_basic	*ft_lstlast_basic(t_basic *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_redir	*ft_lstlast_redir(t_redir *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
