/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:10:49 by ymazini           #+#    #+#             */
/*   Updated: 2024/12/10 17:46:14 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char **saved)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(*saved), *saved = NULL, NULL);
	while (!ft_strchr(*saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(*saved), *saved = NULL, NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = *saved;
		*saved = ft_strjoin(*saved, buffer);
		free(temp);
		if (!*saved)
			return (free(buffer), NULL);
	}
	return (free(buffer), *saved);
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
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
		saved = ft_strdup("");
	if (!saved || !read_line(fd, &saved))
		return (free(saved), saved = NULL, NULL);
	line = extract_line(&saved);
	if (!line)
		return (free(saved), saved = NULL, NULL);
	return (line);
}
