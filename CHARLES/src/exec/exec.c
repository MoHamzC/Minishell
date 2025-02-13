#include "../../minishell.h"


/*POUR GERER LE CAS OU IL Y A PLUSIEURS OUTPUT ET QU'IL FAUT PRENDRE LE DERNIER*/
void    backup_std_fds(t_exec_data *exec)
{
    exec->stdin_backup = dup(STDIN_FILENO);
    exec->stdout_backup = dup(STDOUT_FILENO);
}

void    restore_std_fds(t_exec_data *exec)
{
    dup2(exec->stdin_backup, STDIN_FILENO);
    dup2(exec->stdout_backup, STDOUT_FILENO);
    close(exec->stdin_backup);
    close(exec->stdout_backup);
}


int    exec_single_cmd(t_shell *shell, t_command *cmd, t_exec_data *exec)
{
    char    *cmd_path;
    char    **path_dirs;

    if (!cmd->args || !cmd->args[0])
        return (0);
    if (handle_redirections(cmd) != 0)
        return (1);
    if (cmd->builtin_value != NOT_BUILTIN)
        return (exec_builtin(cmd, shell->env, shell));
    path_dirs = get_path_dirs(exec->env_arr);
    cmd_path = find_command_path(cmd->args[0], path_dirs);
    if (!cmd_path)
    {
        handle_cmd_not_found(cmd->args[0]);
        return (127);
    }
    if (execve(cmd_path, cmd->args, exec->env_arr) == -1)
    {
        free(cmd_path);
        print_exec_error(cmd->args[0], strerror(errno));
        return (126);
    }
    return (0);
}

void    init_exec_data(t_exec_data *exec, t_shell *shell)
{
    exec->env_arr = env_list_to_array(shell->env);
    exec->last_status = 0;
    exec->stdin_backup = dup(STDIN_FILENO);
    exec->stdout_backup = dup(STDOUT_FILENO);
}

int    executor(t_shell *shell)
{
    t_exec_data exec;
    t_command   *current;
    int         pipe_fds[2];
    int         prev_pipe_read;
    init_exec_data(&exec, shell);
    current = shell->cmds;
    prev_pipe_read = -1;
    while (current)
    {
        if (current->next && pipe(pipe_fds) < 0)
            return (print_file_error("pipe", strerror(errno)));
        exec.pid = fork();
        if (exec.pid < 0)
            return (print_file_error("fork", strerror(errno)));
        if (exec.pid == 0)
        {
            if (prev_pipe_read != -1)
            {
                dup2(prev_pipe_read, STDIN_FILENO);
                close(prev_pipe_read);
            }
            if (current->next)
            {
                close(pipe_fds[0]);
                dup2(pipe_fds[1], STDOUT_FILENO);
                close(pipe_fds[1]);
            }
            exit(exec_single_cmd(shell, current, &exec));
        }
        if (prev_pipe_read != -1)
            close(prev_pipe_read);
        if (current->next)
        {
            close(pipe_fds[1]);
            prev_pipe_read = pipe_fds[0];
        }
        current = current->next;
    }
    wait_all_children(shell, &exec);
    return (shell->exit_status);
}

