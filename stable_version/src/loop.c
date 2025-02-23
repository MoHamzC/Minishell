/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:14:06 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/23 17:47:34 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_loop(t_shell *shell)
{
	t_token				**tokens;
	char				*line;

	while (1)
	{
		line = readline("2MAC-Shell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = take_ur_token_and_leave_me_alone(line, shell);
		if (!tokens || !tokens[0])
		{
			if (tokens)
				free(tokens);
			free(line);
			continue ;
		}
		shell->cmds = parse_tokens(tokens);
		executor(shell);
		free_tokens(tokens);
		free(line);
	}
	(free(line), rl_clear_history());
	free_env(shell->env);
}
