/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:12:54 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/27 04:16:50 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_free(t_shell *shell, t_exec_data *exec)
{
	free_env_array(&exec->env_arr);
	restore_std_fds(exec);
	frcm(&shell->cmds);
	free_env(shell->env);
	clean_heredoc_f(shell->here_docs, 1);
	free(shell->here_docs);
}

bool	ft_is_numeric(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(int argc, char **argv, t_shell *shell, t_exec_data *exec)
{
	int	exit_status;

	exit_status = 0;
	if (argc > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		shell->exit_status = 1;
		return (-1);
	}
	if (argc == 2)
	{
		if (!ft_is_numeric(argv[1]))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			exit_status = 2;
			(exit_free(shell, exec), (exit(exit_status)));
		}
		exit_status = ft_atoi(argv[1]);
	}
	if (exit_status < 0)
		exit_status += 256;
	exit_status %= 256;
	exit_free(shell, exec);
	exit(exit_status);
}
