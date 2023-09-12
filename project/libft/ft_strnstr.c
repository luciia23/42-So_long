#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (i < len && haystack[i] && len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && (i + j) < len)
			{
				j++;
				if (needle[j] == 0)
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}
