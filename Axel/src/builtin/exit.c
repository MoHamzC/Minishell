/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:12:54 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/12 20:55:41 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_is_numeric(char *cmd)
{
	int i;

	i = 0;
	if(cmd[i] == '-' || cmd[i] == '+')
	{
		i++;
	}
	while(cmd[i])
	{
		if(!ft_isdigit(cmd[i]))
			return(false);
		i++;
	}
	return(true);
}

void ft_exit(int argc, char **argv, t_shell *shell)
{
    int exit_code;

	exit_code = 0;
	if (argc > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		shell->exit_code = 1;
		return;
	}
	if (argc == 2)
	{
		if (!ft_is_numeric(argv[1]))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			exit_code = 2;
			(free(shell), exit(exit_code));
		}
		exit_code = atoi(argv[1]);
	}
	if (exit_code < 0)
		exit_code += 256;  // Ajuster pour être dans la plage 0-255
	exit_code %= 256;  // Assurer que exit_code est dans la plage [0, 255]
	free(shell);
	printf("exit\n");
	exit(exit_code);
}
