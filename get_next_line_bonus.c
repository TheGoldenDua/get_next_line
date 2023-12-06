/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:02:48 by del-ganb          #+#    #+#             */
/*   Updated: 2023/12/05 18:09:23 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buffer[4096];
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
			return (free(stash), free(buffer[fd]), NULL);
		stash[end] = '\0';
		buffer[fd] = ft_strjoin(buffer[fd], stash);
	}
	line = get_line(buffer[fd]);
	buffer[fd] = free_buffer(buffer[fd]);
	free(stash);
	return (line);
}

// #include <stdio.h>
// int main()
// {
//     int fd1 = open("get_next_line.c", O_RDONLY);
//     int fd2 = open("get_next_line.h", O_RDONLY);
// 	int fd3 = open("get_next_line_bonus.h", O_RDONLY);
//     char *line1;
//     char *line2;
// 	char *line3;
//     line1 = get_next_line(fd1);
//     line2 = get_next_line(fd2);
// 	line3 = get_next_line(fd3);
//     printf("%s", line1);
//     printf("%s", line2);
// 	printf("%s", line3);
//     free(line1);
//     free(line2);
// 	free(line3);
//     printf("\n---------------------------------------\n");
//      line1 = get_next_line(fd1);
//     line2 = get_next_line(fd2);
// 	line3 = get_next_line(fd3);
//     printf("%s", line1);
//     printf("%s", line2);
// 	printf("%s", line3);
//     free(line1);
//     free(line2);
// 	free(line3);
//     printf("\n---------------------------------------\n");
//     line1 = get_next_line(fd1);
//     line2 = get_next_line(fd2);
// 	line3 = get_next_line(fd3);
//     printf("%s", line1);
//     printf("%s", line2);
// 	printf("%s", line3);
//     free(line1);
//     free(line2);
// 	free(line3);
// }