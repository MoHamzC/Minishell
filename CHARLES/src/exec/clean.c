#include "../../minishell.h"

void    free_command(t_command *cmd)
{
    int i;

    if (!cmd)
        return;
    
    // Free command arguments
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
    }

    // Free redirections
    if (cmd->redir)
    {
        i = 0;
        while (cmd->redir[i])
        {
            if (cmd->redir[i]->file)
                free(cmd->redir[i]->file);
            free(cmd->redir[i]);
            i++;
        }
        free(cmd->redir);
    }

    free(cmd);
}

void    free_command_list(t_command *cmd)
{
    t_command *temp;

    while (cmd)
    {
        temp = cmd->next;
        free_command(cmd);
        cmd = temp;
    }
}

void    clean_shell(t_shell *shell)
{
    if (!shell)
        return;

    // Free command list
    free_command_list(shell->cmds);
    shell->cmds = NULL;

    // Free environment
    free_env(shell->env);
    shell->env = NULL;
}