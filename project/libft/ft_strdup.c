#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*str;
	int		i;

	len = ft_strlen((char *)s);
	str = (char *) malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
