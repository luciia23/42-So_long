#include "libft.h"

static char	*make_subs(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	i;
	unsigned int	j;

	subs = (char *) malloc(sizeof(*s) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			subs[j] = s[i];
			j++;
		}
		i++;
	}
	subs[j] = '\0';
	return (subs);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*subs;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	subs = make_subs(s, start, len);
	if (!subs)
		return (NULL);
	return (subs);
}
