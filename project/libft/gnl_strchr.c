#include "libft.h"

char    *gnl_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (i < len && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	if (c == 0)
		return ((char *)s);
	return (NULL);
}