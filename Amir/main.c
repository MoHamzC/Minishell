/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:52 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/11 22:12:14 by mochamsa         ###   ########.fr       */
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
    char	*line = "                 ls -l | cat -e | echo \"Hello world!\"";
    char	**tokens;
    int		i;

    tokens = tokenize(line);
    i = 0;
    printf("Tokens: [");
    while (tokens[i])
    {
        printf("\"%s\";", tokens[i]);
        i++;
    }
    printf("NULL]\n");
    free_tokens(tokens);
    return (0);
}