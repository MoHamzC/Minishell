/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:52 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 09:19:55 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
		return;
	i = 0;
	while (tokens[i] && tokens[i]->value) 
    {
        free(tokens[i]->value);
        free(tokens[i]);
        i++;
    }
	free(tokens);
}

/*
** is_redir_token
** Retourne 1 si le type correspond à une redirection.
*/


int main()
{

    extern char **environ;
    t_shell    shell;
	t_env *head;

    shell.env = init_env(environ);
	head = shell.env;
	ft_env(shell.env);
    free_env(shell.env);
    return (0);
}