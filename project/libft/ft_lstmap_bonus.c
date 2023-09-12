#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*lst_new;
	t_list	*nodo;

	lst_new = NULL;
	if (lst)
	{
		while (lst)
		{
			nodo = ft_lstnew(((*f)(lst->content)));
			if (!nodo)
			{
				ft_lstclear(nodo->content, del);
				free(nodo);
				return (NULL);
			}
			ft_lstadd_back(&lst_new, nodo);
			lst = lst->next;
		}
	}
	return (lst_new);
}
