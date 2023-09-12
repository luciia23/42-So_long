#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*s;
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen((char *)src));
	s = (char *)src;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen((char *)src);
	i = 0;
	j = dstlen;
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	while (s[i] != 0 && i < dstsize - dstlen - 1)
	{
		dst[j] = s[i];
		j++;
		i++;
	}
	dst[j] = 0;
	return (srclen + dstlen);
}
