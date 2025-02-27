/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:35:44 by calberti          #+#    #+#             */
/*   Updated: 2025/02/27 03:45:53 by mochamsa         ###   ########.fr       */
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

void	cleanup_heredocs(char **heredoc_fi, int count, int pid)
{
	int	i;

	i = 0;
	if (!heredoc_fi)
		return ;
	while (i < count)
	{
		if (pid == 0)
			unlink(heredoc_fi[i]);
		if (heredoc_fi[i])
		{
			free(heredoc_fi[i]);
			heredoc_fi[i] = NULL;
		}
		i++;
	}
}

char	*get_heredoc_filename(void)
{
	static int	count = 0;
	char		*num;
	char		*filename;

	num = ft_itoa(count++);
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (filename);
}
