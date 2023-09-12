#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char		*str;
	unsigned int	i;

	str = s;
	i = 0;
	while (i < n)
	{
		if ((char)c == str[i])
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
