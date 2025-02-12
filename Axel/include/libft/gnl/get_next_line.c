/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:48:08 by axburin-          #+#    #+#             */
/*   Updated: 2024/11/04 19:06:23 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*buf = NULL;
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_init_buffer(buf, &temp);
	if (!buf)
		return (NULL);
	buf = ft_read_file(fd, buf, temp);
	free(temp);
	if (!buf)
		return (NULL);
	line = ft_extract_line(buf);
	if (!line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	buf = ft_process_buffer(buf);
	return (line);
}
