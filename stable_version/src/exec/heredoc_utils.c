/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:35:44 by calberti          #+#    #+#             */
/*   Updated: 2025/02/24 19:39:51 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_line2(int fd, char *line)
{
	if (line)
		free(line);
	close(fd);
}

int	count_heredocs(t_command *cmds)
{
	int		count;
	int		i;

	count = 0;
	while (cmds)
	{
		i = 0;
		while (cmds->redir && cmds->redir[i])
		{
			if (cmds->redir[i]->type == HERE_DOC)
				count++;
			i++;
		}
		cmds = cmds->next;
	}
	return (count);
}

void	cleanup_heredocs(char **heredoc_fi, int count)
{
	while (count > 0)
	{
		unlink(heredoc_fi[count - 1]);
		free(heredoc_fi[--count]);
	}
	free(heredoc_fi);
}

char	*get_heredoc_filename(void)
{
	static int	count;
	char		*num;
	char		*filename;

	num = ft_itoa(count++);
	count = 0;
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (filename);
}
