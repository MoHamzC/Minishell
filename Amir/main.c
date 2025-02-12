/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:52 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 07:17:53 by mochamsa         ###   ########.fr       */
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
    char *line = "echo $? $?$?$?$$$  $ $ $ $$HOME";
    t_token	**tokens;
    int		i;
    t_shell    shell;

    shell.env = init_env(environ);
    tokens = take_ur_token_and_leave_me_alone(shell.env, line);
    printf("%s\n", line);
    i = 0;
    while (tokens[i] && tokens[i]->value)
    {
        printf("Token %d: %s de type : %d\n", i, tokens[i]->value, tokens[i]->type);
        i++;
    }
    i = 0;
    while (tokens[i] && tokens[i]->value)
    {
        printf("%s ", tokens[i]->value);
        i++;
    }
    free_tokens(tokens);
    free_env(shell.env);
    return (0);
}