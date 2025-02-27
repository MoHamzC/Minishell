/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:25:13 by calberti          #+#    #+#             */
/*   Updated: 2025/02/27 03:32:23 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (NOT_BUILTIN);
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (NOT_BUILTIN);
}

void	wait_c(t_shell *shell)
{
	t_command	*cmd;
	int			status;

	status = 0;
	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
}

void	backup_std_fds(t_exec_data *exec)
{
	exec->stdin_backup = dup(STDIN_FILENO);
	exec->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_std_fds(t_exec_data *exec)
{
	if (exec->stdin_backup != -1)
	{
		dup2(exec->stdin_backup, STDIN_FILENO);
		close(exec->stdin_backup);
		exec->stdin_backup = -1;
	}
	if (exec->stdout_backup != -1)
	{
		dup2(exec->stdout_backup, STDOUT_FILENO);
		close(exec->stdout_backup);
		exec->stdout_backup = -1;
	}
}

void	clean_heredoc_f(char **heredoc_files, int pid)
{
	int	count;

	count = 0;
	if (!heredoc_files)
		return ;
	if (!heredoc_files[0])
		return ;
	while (heredoc_files[count])
		count++;
	cleanup_heredocs(heredoc_files, count, pid);
	heredoc_files = NULL;
}
