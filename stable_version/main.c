/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:31:10 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/23 17:48:10 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (sig_received == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		sig_received = 0;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				shell;
	// t_token				**tokens;
	// char				*line;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	rl_outstream = stderr;
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	shell.env = init_env(envp);
	ft_loop(&shell);
	return (0);
}
