/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:20:01 by calberti          #+#    #+#             */
/*   Updated: 2025/02/27 04:12:28 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_size(t_command	*cmds)
{
	t_command	*current;
	int			size;

	current = cmds;
	size = 0;
	while (current != NULL)
	{
		current = current->next;
		size++;
	}
	return (size);
}

int	cmd_size_redi(t_command *cmds)
{
	t_command	*current;
	int			i;
	int			redi;

	current = cmds;
	i = 0;
	redi = 0;
	if (current->redir)
	{
		while (current->redir[i])
		{
			if (current->redir[i]->type == HERE_DOC
				|| current->redir[i]->type == REDIRIN)
			{
				redi = 1;
				return (redi);
			}
			i++;
		}
	}
	return (redi);
}

int	verif_heredoc(char	**files, t_command *cmds, t_shell *shell)
{
	t_command	*current;
	int			i;

	i = 0;
	current = cmds;
	if (!files && current && current->redir)
	{
		i = 0;
		while (shell->cmds->redir[i])
		{
			if (shell->cmds->redir[i]->type == HERE_DOC)
			{
				shell->exit_status = 1;
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	pipe_fork(t_command *cmds, int *pipe_fds, char **file)
{
	t_command	*current;

	current = cmds;
	if (current->next && pipe(pipe_fds) < 0)
	{
		clean_heredoc_f(file, 1);
		return (print_file_error("pipe", strerror(errno)));
	}
	current->pid = fork();
	if (current->pid < 0)
	{
		clean_heredoc_f(file, 1);
		return (print_file_error("fork", strerror(errno)));
	}
	return (current->pid);
}

int	update_pipe_read(int prev_pipe_read, t_command *cmds, int *pipe_fds)
{
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	if (cmds->next)
	{
		close(pipe_fds[1]);
		prev_pipe_read = pipe_fds[0];
	}
	return (prev_pipe_read);
}
