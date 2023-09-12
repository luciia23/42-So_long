#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"
/*Utilizamos variables estáticas para que su valor se mantenga en las diferentes llamadas a la función*/

//Lee el archivo hasta llegar a un salto de línea y lo guarda en la estática
char *read_line(int fd,char *buffer, char **remainder)
{
    int 	bytes_read;
	char	*tmp;

    bytes_read = 1;
    while (bytes_read > 0 && !gnl_strchr(*remainder, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == 0)
            break;
        if (bytes_read < 0)
        {
			free(remainder);
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
		tmp = *remainder;
        *remainder = gnl_strjoin(tmp, buffer);
    }
    free(buffer);
    return (*remainder);
}

//Obtiene la linea antes del \n
char	*get_line(char *remainder)
{
	char	*line;
	int		i;

	i = 0;
	while (remainder[i] != 0 && remainder[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] != '\n' && remainder[i] != 0)
	{
		line[i] = remainder[i];
		i++;
	}
	if (gnl_strchr(remainder, '\n'))
	{
		line[i] = remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

//mover la posición para después del salto de línea, y que siga imprimiendo desde ahí
char	*move_position(char *remainder)
{
	int	i;
	char	*new_line;
	int	j;

	i = 0;
	while (remainder[i] != '\n' && remainder[i] != 0)
		i++;
	if (gnl_strchr(remainder, '\n'))
		i++;
	new_line = (char*)malloc(sizeof(char) * (ft_strlen(&remainder[i]) + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	while (remainder[i + j])
	{
		new_line[j] = remainder[i + j];
		j++;
	}
	new_line[j] = '\0';
	free(remainder);
	return (new_line);	
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	remainder = read_line(fd, buffer, &remainder);
	if(!remainder || *remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = get_line(remainder);
	remainder = move_position(remainder);
	return (line);
}

// int main(){
// 	int fd;
// 	char *line;

// 	fd = open("files/largo.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while(line)
// 	{
// 		printf("----->%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
		
// 	return (0);
// }