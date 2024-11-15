#include "libft.h"

void	ft_lstdelone(t_list *lst)
{
	ft_del(lst->content);
	free(lst);
}
