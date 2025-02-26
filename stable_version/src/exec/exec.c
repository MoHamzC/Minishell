/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:27:52 by calberti          #+#    #+#             */
/*   Updated: 2025/02/26 01:51:59 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

int	exec_single_cmd(t_shell *shell, t_command *cmd, t_exec_data *exec)
{
	char	*cmd_path;
	char	**path_dirs;
	int 	status;
	
	if (!cmd->args || !cmd->args[0])
		return (0);
	backup_std_fds(exec);
	if (handle_redirections(cmd) != 0)
		return (restore_std_fds(exec), 1);
	if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
	{
		if (cmd->next)
		{
			if (cmd->pid == 0)
			{
				status = exec_builtin(cmd, shell->env, shell);
				free_env_array(&exec->env_arr);
				free_env(shell->env);
				ft_free_commands(&shell->cmds);
				restore_std_fds(exec);
				exit(status);
			}
			return (free_env_array(&exec->env_arr), free_env(shell->env), restore_std_fds(exec), 0);
		}
		status = exec_builtin(cmd, shell->env, shell);
		free_env_array(&exec->env_arr);
		restore_std_fds(exec);
		return (status);
	}
	path_dirs = get_path_dirs(exec->env_arr);
	cmd_path = find_command_path(cmd->args[0], path_dirs);
	ft_free_args(path_dirs);
	if (!cmd_path)
		return (handle_cmd_not_found(cmd->args[0]),restore_std_fds(exec),clean_heredoc_f(shell->here_docs), 127);
	if (execve(cmd_path, cmd->args, exec->env_arr) == -1)
		return (free(cmd_path),ft_free_commands(&cmd),free_env_array(&exec->env_arr), print_exec_error(cmd->args[0], strerror(errno)),
				restore_std_fds(exec), 126);
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
	t_command	*current;
	t_pipe_data	pipe_data;
	char		**heredoc_files;
	int 		status;
	
	current = shell->cmds;
	init_exec_data(&exec, shell);
	heredoc_files = process_heredocs(shell->cmds);
	shell->here_docs = heredoc_files;
	if (verif_heredoc(heredoc_files, current, shell) == 1)
	{
		clean_heredoc_f(heredoc_files);
		free_env_array(&exec.env_arr);
		ft_free_commands(&shell->cmds);
		return (1);
	}
	if (is_single_builtin(current))
	{
		status = do_builtin(&exec, current, shell, heredoc_files);
		free_env_array(&exec.env_arr);
		return (status);
	}
	pipe_data.prev_pipe_read = -1;
	while (current)
	{
		if (handle_command2(current, pipe_data.pipe_fds, heredoc_files) == 1)
			return (1);
		if (current->pid == 0)
		{
			status = exec_command(shell, current, &exec, &pipe_data);
			free_env_array(&exec.env_arr);
			free_env(shell->env);
			ft_free_commands(&shell->cmds);
			clean_heredoc_f(heredoc_files);
			exit(status);
		}
		pipe_data.prev_pipe_read = update_pipe_read(pipe_data.prev_pipe_read,
				current, pipe_data.pipe_fds);
		current = current->next;
	}
	g_sig_received = 0;
	free_env_array(&exec.env_arr);
	return (wait_c(shell), clean_heredoc_f(heredoc_files), shell->exit_status);
}
