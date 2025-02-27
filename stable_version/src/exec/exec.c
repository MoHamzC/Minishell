/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:27:52 by calberti          #+#    #+#             */
/*   Updated: 2025/02/27 04:21:05 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin_cmd(t_shell *shell, t_command *cmd, t_exec_data *exec)
{
	int	status;

	if (cmd->next)
	{
		if (cmd->pid == 0)
		{
			status = exec_builtin(cmd, shell->env, shell, exec);
			free_env_array(&exec->env_arr);
			free_env(shell->env);
			frcm(&shell->cmds);
			exit(status);
		}
		free_env_array(&exec->env_arr);
		free_env(shell->env);
		return (0);
	}
	status = exec_builtin(cmd, shell->env, shell, exec);
	free_env_array(&exec->env_arr);
	return (status);
}

int	exec_single_cmd(t_shell *shell, t_command *cmd, t_exec_data *exec)
{
	char	*cmd_path;
	char	**path_dirs;

	if (handle_redirections(cmd) != 0)
		return (1);
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
		return (exec_builtin_cmd(shell, cmd, exec));
	path_dirs = get_path_dirs(exec->env_arr);
	cmd_path = find_command_path(cmd->args[0], path_dirs);
	ft_free_args(path_dirs);
	if (!cmd_path)
		return (hcnf(cmd->args[0]), clean_heredoc_f(shell->here_docs, cmd->pid),
			127);
	if (execve(cmd_path, cmd->args, exec->env_arr) == -1)
		return (free(cmd_path), print_exec_error(cmd->args[0], strerror(errno)),
			126);
	return (0);
}

void	init_exec_data(t_exec_data *exec, t_shell *shell)
{
	exec->env_arr = env_list_to_array(shell->env);
	exec->last_status = 0;
	exec->stdin_backup = -1;
	exec->stdout_backup = -1;
	g_sig_received = 1;
}

int	executor(t_shell *shell)
{
	t_exec_data	exec;
	t_pipe_data	pipe_data;
	t_executor	executor;
	int			status;

	init_executor(&executor, shell, &exec, &pipe_data);
	if (handle_hrdc_e(&executor) == 1)
		return (1);
	status = handle_btn_e(&executor);
	if (status == 0)
		return (status);
	if (status == -1)
		return (-1);
	executor.pipe_data->prev_pipe_read = -1;
	if (execute_cmd_e(&executor) == 1)
		return (1);
	g_sig_received = 2;
	free_env_array(&executor.exec->env_arr);
	clean_heredoc_f(executor.heredoc_files, 1);
	free(executor.heredoc_files);
	executor.heredoc_files = NULL;
	return (wait_c(shell), shell->exit_status);
}
