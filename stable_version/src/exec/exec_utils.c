#include "minishell.h"

int    is_builtin(char *cmd)
{
    if (!cmd)
        return (NOT_BUILTIN);
    if (!strcmp(cmd, "echo"))
        return (ECHO);
    if (!strcmp(cmd, "cd"))
        return (CD);
    if (!strcmp(cmd, "pwd"))
        return (PWD);
    if (!strcmp(cmd, "export"))
        return (EXPORT);
    if (!strcmp(cmd, "unset"))
        return (UNSET);
    if (!strcmp(cmd, "env"))
        return (ENV);
    if (!strcmp(cmd, "exit"))
        return (EXIT);
    return (NOT_BUILTIN);
}

void    wait_all_children(t_shell *shell)
{
    t_command   *cmd;
    int         status;

    cmd = shell->cmds;
    while (cmd)
    {
        if (cmd->pid > 0)
        {
            waitpid(cmd->pid, &status, 0);
            if (WIFEXITED(status))
                shell->exit_status = WEXITSTATUS(status);
        }
        cmd = cmd->next;
    }
}