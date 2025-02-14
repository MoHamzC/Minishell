/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:52 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 12:39:16 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env *create_simple_env(void)
{
    t_env *env;
    t_env *path;
    t_env *home;

    // Create basic PATH
    path = ft_envlst_new("PATH", "/usr/local/bin:/usr/bin:/bin");
    if (!path)
        return (NULL);
    
    // Create HOME
    home = ft_envlst_new("HOME", "/Users/user");
    if (!home)
    {
        free_env(path);
        return (NULL);
    }

    // Link them together
    env = path;
    env->next = home;
    
    return (env);
}

int main()
{

    t_shell shell;

    t_token	**tokens;

    char *line = "echo $ \"$HOME\"";

    shell.env = create_simple_env();
    tokens = take_ur_token_and_leave_me_alone(shell.env, line);
    shell.cmds = parse_tokens(tokens);

    executor(&shell);

    // free_env(shell.env);
    free_tokens(tokens);
    return (0);
}

//"<\"<\"echo>'oui'>oui"