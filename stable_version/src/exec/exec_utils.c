#include "minishell.h"

int    count_pipes(t_command *cmd)
{
    int    count;

    count = 0;
    while (cmd && cmd->next)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}

void    close_pipe_ends(t_pipe_ends *pipes)
{
    if (!pipes)
        return ;
    if (pipes->read != -1)
    {
        close(pipes->read);
        pipes->read = -1;
    }
    if (pipes->write != -1)
    {
        close(pipes->write);
        pipes->write = -1;
    }
}

int    setup_pipes(t_pipe_ends *pipes)
{
    int    pipe_fds[2];

    if (!pipes)
        return (-1);
    if (pipe(pipe_fds) == -1)
        return (-1);
    pipes->read = pipe_fds[0];
    pipes->write = pipe_fds[1];
    return (0);
}


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

void    wait_all_children(t_shell *shell, t_exec_data *exec)
{
    t_command   *cmd;
    int         status;

    cmd = shell->cmds;
    while (cmd)
    {
        if (exec->pid > 0)
        {
            waitpid(exec->pid, &status, 0);
            if (WIFEXITED(status))
                shell->exit_status = WEXITSTATUS(status);
        }
        cmd = cmd->next;
    }
}