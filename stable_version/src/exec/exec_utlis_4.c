/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utlis_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 01:05:18 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/27 04:16:50 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_hrdc_e(t_executor *executor)
{
	if (verif_heredoc(executor->heredoc_files, executor->current,
			executor->shell) == 1)
	{
		clean_heredoc_f(executor->heredoc_files, 1);
		free_env_array(&executor->exec->env_arr);
		frcm(&executor->shell->cmds);
		return (1);
	}
	return (0);
}

int	handle_btn_e(t_executor *executor)
{
	int	status;

	if (is_single_builtin(executor->current))
	{
		status = do_builtin(executor->exec, executor->current, executor->shell,
				executor->heredoc_files);
		free_env_array(&executor->exec->env_arr);
		g_sig_received = 0;
		return (status);
	}
	return (-2);
}

int	execute_cmd_e(t_executor *executor)
{
	int			status;
	t_pipe_data	*pipe_data;

	pipe_data = executor->pipe_data;
	while (executor->current)
	{
		if (handle_command2(executor->current, pipe_data->pipe_fds,
				executor->heredoc_files) == 1)
			return (1);
		if (executor->current->pid == 0)
		{
			status = exec_command(executor->shell, executor->current,
					executor->exec, pipe_data);
			free_env_array(&executor->exec->env_arr);
			(free_env(executor->shell->env), frcm(&executor->shell->cmds));
			clean_heredoc_f(executor->heredoc_files, 0);
			free(executor->heredoc_files);
			executor->heredoc_files = NULL;
			exit(status);
		}
		pipe_data->prev_pipe_read = update_pipe_read(pipe_data->prev_pipe_read,
				executor->current, pipe_data->pipe_fds);
		executor->current = executor->current->next;
	}
	return (0);
}

void	init_executor(t_executor *executor, t_shell *shell, t_exec_data *exec,
		t_pipe_data *pipe_data)
{
	init_exec_data(exec, shell);
	executor->heredoc_files = process_heredocs(shell->cmds);
	shell->here_docs = executor->heredoc_files;
	executor->shell = shell;
	executor->current = shell->cmds;
	executor->exec = exec;
	executor->pipe_data = pipe_data;
	executor->status = 0;
}
