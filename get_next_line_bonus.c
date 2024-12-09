/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:10:17 by ymazini           #+#    #+#             */
/*   Updated: 2024/12/09 18:28:05 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(int fd, char **saved)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	bytes_read;

	while (!ft_strchr(*saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*saved);
			*saved = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = *saved;
		*saved = ft_strjoin(*saved, buffer);
		free(temp);
		if (!*saved)
			return (NULL);
	}
	return (*saved);
}

static char	*extract_line(char **saved)
{
	char	*line;
	char	*temp;
	size_t	len;

	if (!*saved || !**saved)
		return (NULL);
	len = 0;
	while ((*saved)[len] && (*saved)[len] != '\n')
		len++;
	line = ft_substr(*saved, 0, len + ((*saved)[len] == '\n'));
	temp = *saved;
	*saved = ft_strdup(*saved + len + ((*saved)[len] == '\n'));
	free(temp);
	if (!line || !*saved)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved[FD_SETSIZE];
	char		*line;

	if (fd < 0 || fd >= FD_SETSIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved[fd])
		saved[fd] = ft_strdup("");
	if (!saved[fd] || !read_line(fd, &saved[fd]))
		return (free(saved[fd]), saved[fd] = NULL, NULL);
	line = extract_line(&saved[fd]);
	if (!line)
		return (free(saved[fd]), saved[fd] = NULL, NULL);
	return (line);
}
