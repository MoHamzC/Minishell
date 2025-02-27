/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:14:06 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/27 04:16:50 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_loop(t_shell *shell)
{
	t_token				**tokens;
	char				*line;

	while (1)
	{
		line = readline("\033[0;31mM\033[0;33m2\033[0;31mAC-Shell$\033[0m");
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
		(free_tokens(tokens), executor(shell));
		if (shell->cmds)
			frcm(&shell->cmds);
		free(line);
	}
	(free(line), rl_clear_history());
}
