/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:52 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 00:19:18 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int main()
{
    extern char **environ;
    char	*line = "ls -l | $HOME | echo \"Hello world!\"";
    char	**tokens;
    int		i;
    t_shell    shell;

    shell.env = init_env(environ);
    tokens = tokenize(line, shell.env);
    i = 0;
    while (tokens[i])
    {
        printf("Token %d: %s\n", i, tokens[i]);
        i++;
    }
    free_tokens(tokens);
    return (0);
}