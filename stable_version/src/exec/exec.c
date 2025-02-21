#include "minishell.h"

int    exec_single_cmd(t_shell *shell, t_command *cmd, t_exec_data *exec)
{
    char    *cmd_path;
    char    **path_dirs;

    if (!cmd->args || !cmd->args[0])
		return (0);
    if (handle_redirections(cmd, exec) != 0)
        return (1);
    if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
    {
        if (cmd->next) // Si le built-in est dans un pipeline, il faut le forker
        {
            if (fork() == 0)
            {
                exec_builtin(cmd, shell->env, shell);
                exit(shell->exit_status); // On sort du processus enfant
            }
            return (0); // On ne l'exécute pas dans le parent
        }
        return (exec_builtin(cmd, shell->env, shell));
    }
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
    sig_received = 1;
}

int executor(t_shell *shell)
{
    t_exec_data exec;
    t_command *current;
    t_command *current2;
    int pipe_fds[2];
    int prev_pipe_read;
    char **heredoc_files;

    current = shell->cmds;
    current2 = shell->cmds;
    int size = 0;
    while (current2 != NULL)
    {
        current2 = current2->next;
        size++;
    }
    init_exec_data(&exec, shell);

    heredoc_files = process_heredocs(shell->cmds);
    if (!heredoc_files && shell->cmds && shell->cmds->redir)
    {
        // Check si heredoc a ete interompu
        int i = 0;
        while (shell->cmds->redir[i])
        {
            if (shell->cmds->redir[i]->type == HERE_DOC)
            {
                shell->exit_status = 1;
                return (1);
            }
            i++;
        }
    }
    //pour voir si y a pas de redir d'entrer poour un builtin seul
    current2 = shell->cmds;
    int j = 0;
    int redi = 0;
    if (current2->redir)
    {
        while (current2->redir[j])
        {
            if (current2->redir[j]->type == HERE_DOC || current2->redir[j]->type == REDIRIN)
                redi = 1;
            j++;
        }
    }
    if ((is_builtin(current->args[0]) != NOT_BUILTIN) && size == 1 && !current->next
            && redi == 0)
    {
        rl_outstream = stderr;
        handle_redirections(current, &exec);
        exec_builtin(shell->cmds, shell->env, shell);
        dup2(exec.stdout_backup, STDOUT_FILENO);
        close(exec.stdout_backup);
        cleanup_heredoc_files(heredoc_files);
        return (shell->exit_status);
    }

    prev_pipe_read = -1;

    while (current)
    {
        if (current->next && pipe(pipe_fds) < 0)
        {
            cleanup_heredoc_files(heredoc_files);
            return (print_file_error("pipe", strerror(errno)));
        }

        current->pid = fork();
        if (current->pid < 0)
        {
            cleanup_heredoc_files(heredoc_files);
            return (print_file_error("fork", strerror(errno)));
        }

        if (current->pid == 0)
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

    wait_all_children(shell);
    cleanup_heredoc_files(heredoc_files);
    sig_received = 0;
    return (shell->exit_status);
}

