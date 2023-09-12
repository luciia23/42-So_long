#include "libft.h"

t_list		*ft_lstget(t_list *lst, int index)
{
	t_list	*n;
	int i;

	i = 0;
	n = lst;
	if (n == NULL)
		return (NULL);
	if (n->next == NULL)
		return (n);
	while (n != NULL)
	{
		if (i >= index)
			return (n);
		n = n->next;
		i++;
	}
	return (NULL);
}

void	ft_lstiter_param(t_list *lst1, t_list *lst2, t_list *lst3, t_list *lst4, void (*f)(void *, void *, void *, void *, void *), void * ptr)
{
	t_list	*temp1;
	t_list	*temp2;
	t_list	*temp3;
	t_list	*temp4;

	temp1 = lst1;
	temp2 = lst2;
	temp3 = lst3;
	temp4 = lst4;
	while (temp1 != NULL && temp2 != NULL && temp3 != NULL && temp4 != NULL)
	{
		f(temp1->content, temp2->content, temp3->content, temp4->content, ptr);
		temp1 = temp1->next;
		temp2 = temp2->next;
		temp3 = temp3->next;
		temp4 = temp4->next;
	}
}