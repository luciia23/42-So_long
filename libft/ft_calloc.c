#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*s;

	if (nmeb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	s = malloc(nmeb * size);
	if (!s)
		return (NULL);
	ft_bzero(s, nmeb * size);
	return (s);
}
