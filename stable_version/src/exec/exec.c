/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:27:52 by calberti          #+#    #+#             */
/*   Updated: 2025/02/26 21:47:14 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int exec_builtin_command(t_command *cmd, t_shell *shell, t_exec_data *exec)
{
	int status;

	if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
	{
		if (cmd->next)
		{
			if (cmd->pid == 0)
			{
				 status = exec_builtin(cmd, shell->env, shell, exec);
				 free_env_array(&exec->env_arr);
				 free_env(shell->env);
				 ft_free_commands(&shell->cmds);
				 exit(status);
			}
			return (free_env_array(&exec->env_arr), free_env(shell->env), 0);
		}
		status = exec_builtin(cmd, shell->env, shell, exec);
		free_env_array(&exec->env_arr);
		return (status);
	}
	return (-1);// Indicate that it's not a builtin
}

int	exec_single_cmd(t_shell *shell, t_command *cmd, t_exec_data *exec)
{
	char	*cmd_path;
	char	**path_dirs;
	int 	status;
	
	if (handle_redirections(cmd) != 0)
		return (1);
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
	{
		if (cmd->next)
		{
			if (cmd->pid == 0)
			{
				status = exec_builtin(cmd, shell->env, shell, exec);
				free_env_array(&exec->env_arr);
				free_env(shell->env);
				ft_free_commands(&shell->cmds);
				exit(status);
			}
			return (free_env_array(&exec->env_arr), free_env(shell->env), 0);
		}
		status = exec_builtin(cmd, shell->env, shell, exec);
		free_env_array(&exec->env_arr);
		return (status);
	}
	path_dirs = get_path_dirs(exec->env_arr);
	cmd_path = find_command_path(cmd->args[0], path_dirs);
	ft_free_args(path_dirs);
	if (!cmd_path)
		return (handle_cmd_not_found(cmd->args[0]), clean_heredoc_f(shell->here_docs), 127);
	if (execve(cmd_path, cmd->args, exec->env_arr) == -1)
		return (free(cmd_path), print_exec_error(cmd->args[0], strerror(errno)), 126);
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
		g_sig_received = 0;
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
			free(heredoc_files);
			heredoc_files = NULL;
			exit(status);
		}
		pipe_data.prev_pipe_read = update_pipe_read(pipe_data.prev_pipe_read,
				current, pipe_data.pipe_fds);
		current = current->next;
	}
	g_sig_received = 2;
	free_env_array(&exec.env_arr);
	clean_heredoc_f(heredoc_files);
	free(heredoc_files);
	heredoc_files = NULL;
	return (wait_c(shell), shell->exit_status);
}
