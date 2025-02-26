/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:22:28 by calberti          #+#    #+#             */
/*   Updated: 2025/02/26 17:58:25 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_command *cmd, t_env *env, t_shell *shell, t_exec_data *exec)
{
	(void)env;
	if (cmd->builtin_value == ECHO)
		shell->exit_status = ft_echo(cmd->argc, cmd->args);
	else if (cmd->builtin_value == CD)
		shell->exit_status = ft_cd(shell);
	else if (cmd->builtin_value == PWD)
		shell->exit_status = ft_pwd(shell->env);
	else if (cmd->builtin_value == EXPORT)
		shell->exit_status = ft_export(cmd->args, shell);
	else if (cmd->builtin_value == UNSET)
		shell->exit_status = ft_unset(&shell->env, cmd->args);
	else if (cmd->builtin_value == ENV)
		shell->exit_status = ft_env(shell->env);
	else if (cmd->builtin_value == EXIT)
		shell->exit_status = ft_exit(cmd->argc, cmd->args, shell, exec);
	return (shell->exit_status);
}
