#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(char *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
