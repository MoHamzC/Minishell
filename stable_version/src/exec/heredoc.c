/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:29:45 by calberti          #+#    #+#             */
/*   Updated: 2025/02/24 20:34:56 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_heredoc_interrupted = 0;

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
}

static int	create_heredoc_file(char *delimiter, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_heredoc_interrupted)
		{
			error_line2(fd, line);
			if (g_heredoc_interrupted)
				return (-1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
			return (free(line), 0);
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}

static int	handle_heredoc(t_redir *redir, char **heredoc_fi, int *index)
{
	heredoc_fi[*index] = get_heredoc_filename();
	if (!heredoc_fi[*index]
		|| create_heredoc_file(redir->file, heredoc_fi[*index]) < 0)
		return (-1);
	redir->file = ft_strdup(heredoc_fi[*index]);
	(*index)++;
	return (0);
}

static int	process_each_heredoc(t_command *cmds, char **heredoc_fi)
{
	int		index;
	int		i;

	index = 0;
	while (cmds && !g_heredoc_interrupted)
	{
		i = -1;
		while (cmds->redir && cmds->redir[++i] && !g_heredoc_interrupted)
		{
			if (cmds->redir[i]->type == HERE_DOC
				&& handle_heredoc(cmds->redir[i], heredoc_fi, &index) < 0)
			{
				cleanup_heredocs(heredoc_fi, index);
				return (-1);
			}
		}
		cmds = cmds->next;
	}
	return (index);
}

char	**process_heredocs(t_command *cmds)
{
	int					heredoc_count;
	char				**heredoc_fi;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	heredoc_count = count_heredocs(cmds);
	if (heredoc_count == 0)
		return (NULL);
	heredoc_fi = malloc(sizeof(char *) * (heredoc_count + 1));
	if (!heredoc_fi)
		return (NULL);
	sa_new.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	g_heredoc_interrupted = 0;
	if (process_each_heredoc(cmds, heredoc_fi) < 0 || g_heredoc_interrupted)
		return (sigaction(SIGINT, &sa_old, NULL), NULL);
	sigaction(SIGINT, &sa_old, NULL);
	heredoc_fi[heredoc_count] = NULL;
	return (heredoc_fi);
}
