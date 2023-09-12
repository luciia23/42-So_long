#include "libft.h"

static void	check(unsigned char *d, unsigned char *s, size_t len)
{
	size_t	i;

	i = 0;
	if (d > s)
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (len == 0 || dst == src)
		return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	check(d, s, len);
	return (d);
}
