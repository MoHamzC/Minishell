/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:47:12 by axburin-          #+#    #+#             */
/*   Updated: 2024/11/04 20:38:05 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_process_buffer(char *buf)
{
	char	*newline;
	size_t	i;

	if (!buf)
		return (NULL);
	newline = ft_strchr(buf, '\n');
	if (!newline)
	{
		buf[0] = '\0';
		return (buf);
	}
	i = 0;
	newline++;
	while (newline[i])
	{
		buf[i] = newline[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

static char	*ft_extract_line(char *buf)
{
	size_t	i;
	char	*line;

	if (!buf || !buf[0])
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = ft_substr(buf, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*ft_read_file(int fd, char *buf, char *temp)
{
	ssize_t	bytes;
	char	*new_buf;

	if (!buf)
		return (NULL);
	while (!ft_strchr(buf, '\n'))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		temp[bytes] = '\0';
		new_buf = ft_strjoin(buf, temp);
		free(buf);
		if (!new_buf)
			return (NULL);
		buf = new_buf;
	}
	return (buf);
}

static char	*ft_init_buffer(char *buf, char **temp)
{
	*temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*temp)
	{
		free(buf);
		return (NULL);
	}
	if (!buf)
	{
		buf = malloc(1);
		if (!buf)
		{
			free(*temp);
			return (NULL);
		}
		buf[0] = '\0';
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf[1024];
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf[fd] = ft_init_buffer(buf[fd], &temp);
	if (!buf[fd])
		return (NULL);
	buf[fd] = ft_read_file(fd, buf[fd], temp);
	free(temp);
	if (!buf[fd])
		return (NULL);
	line = ft_extract_line(buf[fd]);
	if (!line)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	buf[fd] = ft_process_buffer(buf[fd]);
	return (line);
}
