/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:52 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 02:02:11 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// static t_redir *create_redir(char *file, int type, bool append)
// {
//     t_redir *redir;

//     redir = malloc(sizeof(t_redir));
//     if (!redir)
//         return (NULL);
//     redir->file = strdup(file);
//     redir->type = type;
//     redir->append = append;
//     return (redir);
// }

// static t_command *create_simple_command(char **args, t_redir **redirs)
// {
//     t_command *cmd;

//     cmd = malloc(sizeof(t_command));
//     if (!cmd)
//         return (NULL);
//     cmd->args = args;
//     cmd->redir = redirs;
//     cmd->builtin_value = -1;
//     cmd->next = NULL;
//     return (cmd);
// }

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

int main(void)
{
    t_shell shell;
    // t_command *cmd1;
    // t_command *cmd2;
	// t_command *cmd3;
    // char **args1;
    // char **args2;
	// char **args3;
    // t_redir **redirs1;
    // t_redir **redirs2;
	// t_redir **redirs3;
    char *line = "sleep 2 | sleep 2";
    t_token	**tokens;
    
    // Initialize shell structure
    shell.env = create_simple_env();
    tokens = take_ur_token_and_leave_me_alone(shell.env, line);
    shell.cmds = parse_tokens(tokens);
    // // Create command "ls -l > output.txt"
    // args1 = malloc(sizeof(char *) * 3);
    // args1[0] = strdup("ls");
    // args1[1] = strdup("-l");
    // args1[2] = NULL;

    // redirs1 = malloc(sizeof(t_redir *) * 1);
    // redirs1[0] = NULL;

    // cmd1 = create_simple_command(args1, redirs1);

	// // Create command "grep mini"
    // args2 = malloc(sizeof(char *) * 3);
    // args2[0] = strdup("grep");
    // args2[1] = strdup("mini");
    // args2[2] = NULL;

	// redirs2 = malloc(sizeof(t_redir *) * 2);
    // redirs2[0] = NULL;

    // cmd2 = create_simple_command(args2, redirs2);

    // // Create command "wc -l"
    // args3 = malloc(sizeof(char *) * 3);
    // args3[0] = strdup("wc");
    // args3[1] = strdup("-l");
    // args3[2] = NULL;

	// redirs3 = malloc(sizeof(t_redir *) * 2);
    // redirs3[0] = create_redir("output.txt", REDIROUT, false);
    // redirs3[1] = NULL;

    // cmd3 = create_simple_command(args3, redirs3);

    // // Link commands for pipe
    // shell.cmds = cmd1;
    // cmd1->next = cmd2;
	// cmd2->next = cmd3;
    // Execute commands
    executor(&shell);

    // Clean up (you would need to implement proper cleanup functions)
    // This is just basic cleanup to avoid leaks
    // TODO: Implement proper cleanup functions

    // free(args1[0]);
    // free(args1[1]);
    // free(redirs1[0]);
    // free(redirs1);
    // free(cmd1);
    // free(args2[0]);
    // free(args2[1]);
    // free(args2);
    // free(redirs2);
    // free(cmd2);
   	
    //free_env(shell.env);
    return (0);
}