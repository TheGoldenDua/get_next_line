/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:42:16 by del-ganb          #+#    #+#             */
/*   Updated: 2023/12/06 17:08:45 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *buffer)
{
	int	i;

	i = 0;
	if (!*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	return (ft_substr(buffer, 0, i + 1));
}

static char	*free_buffer(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = ft_strdup(buffer + i);
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*stash;
	char		*line;
	ssize_t		end;

	end = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = (char *)malloc(BUFFER_SIZE + 1);
	if (!stash)
		return (NULL);
	stash[0] = 0;
	while (end > 0 && !ft_strchr(stash, '\n'))
	{
		end = read(fd, stash, BUFFER_SIZE);
		if (end < 0)
			return (free(stash), free(buffer), NULL);
		stash[end] = '\0';
		buffer = ft_strjoin(buffer, stash);
	}
	line = get_line(buffer);
	buffer = free_buffer(buffer);
	free(stash);
	return (line);
}

// #include <stdio.h>
// int main()
// {
// 	int	fd;
// 	char *str;

// 	fd = open("get_next_line.h", O_RDONLY);
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	printf("%s", str);
// 	return (0);
// }