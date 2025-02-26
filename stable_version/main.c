/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:31:10 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/26 01:35:08 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_sig_received == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_sig_received = 0;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	free_env(t_env *env)
{
	t_env	*head;
	t_env	*tmp;

	head = env;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
	head = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				shell;
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
	free_env(shell.env);
	return (0);
}
