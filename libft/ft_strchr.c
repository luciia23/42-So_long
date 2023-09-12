#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while ((s[i] != 0) && (s[i] != (unsigned char)c))
		i++;
	if ((s[i] == (unsigned char)c))
		return (&((char *)s)[i]);
	if (c == 0)
		return ((char *)s);
	return (NULL);
}
