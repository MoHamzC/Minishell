/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:21:20 by calberti          #+#    #+#             */
/*   Updated: 2025/02/27 04:13:25 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_builtin(t_exec_data *exec, t_command *cmd, t_shell *shell, char **files)
{
	rl_outstream = stderr;
	backup_std_fds(exec);
	handle_redirections(cmd);
	exec_builtin(shell->cmds, shell->env, shell, exec);
	restore_std_fds(exec);
	clean_heredoc_f(files, 1);
	return (shell->exit_status);
}

int	exec_command(t_shell *shell, t_command *cmd, t_exec_data *exec,
		t_pipe_data *pipe_data)
{
	if (pipe_data->prev_pipe_read != -1)
	{
		dup2(pipe_data->prev_pipe_read, STDIN_FILENO);
		close(pipe_data->prev_pipe_read);
	}
	if (cmd->next)
	{
		close(pipe_data->pipe_fds[0]);
		dup2(pipe_data->pipe_fds[1], STDOUT_FILENO);
		close(pipe_data->pipe_fds[1]);
	}
	return (exec_single_cmd(shell, cmd, exec));
}

int	handle_command2(t_command *cmd, int pipe_fds[2], char **heredoc_files)
{
	cmd->pid = pipe_fork(cmd, pipe_fds, heredoc_files);
	return (cmd->pid == 1);
}

int	is_single_builtin(t_command *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
	return ((is_builtin(cmd->args[0]) != NOT_BUILTIN) && cmd_size(cmd) == 1
		&& !cmd->next && cmd_size_redi(cmd) == 0);
}
