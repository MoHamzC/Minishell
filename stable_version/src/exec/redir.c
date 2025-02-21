#include "minishell.h"


static t_redir *get_last_redir_of_type(t_redir **redirs, int type)
{
    int     i;
    t_redir *last;

    i = 0;
    last = NULL;
    while (redirs[i])
    {
        if (redirs[i]->type == type || 
            (type == REDIROUT && redirs[i]->type == APPEND))
            last = redirs[i];
        i++;
    }
    return (last);
}


static int create_output_files(t_redir **redirs)
{
    int     i;
    int     fd;

    i = 0;
    while (redirs[i])
    {
        if (redirs[i]->type == REDIROUT || redirs[i]->type == APPEND)
        {
            fd = open(redirs[i]->file, O_WRONLY | O_CREAT, 0644);
            if (fd < 0)
                return (print_file_error(redirs[i]->file, strerror(errno)));
            close(fd);
        }
        if (redirs[i]->type == REDIRIN)
        {
            fd = open(redirs[i]->file, O_RDONLY);
            if (fd<0)
                return (print_file_error(redirs[i]->file, strerror(errno)));
            close(fd);
        }
        i++;
    }
    return (0);
}

int    handle_input_redir(char *file, t_exec_data *exec)
{
    int    fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (print_file_error(file, strerror(errno)));
    exec->stdin_backup = fd;
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close(fd);
        return (print_file_error(file, strerror(errno)));
    }
    close(fd);
    return (0);
}

int    handle_output_redir(char *file, int append, t_exec_data *exec)
{
    int    fd;
    int    flags;

    flags = O_WRONLY | O_CREAT;
    flags |= (append ? O_APPEND : O_TRUNC);
    fd = open(file, flags, 0644);
    if (fd < 0)
        return (print_file_error(file, strerror(errno)));
    exec->stdout_backup = fd;
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        close(fd);
        return (print_file_error(file, strerror(errno)));
    }
    close(fd);
    return (0);
}

int handle_redirections(t_command *cmd, t_exec_data *exec)
{
    t_redir *last_in;
    t_redir *last_out;
    int i;

    if (!cmd->redir)
        return (0);

    if (create_output_files(cmd->redir) != 0)
        return (1);

    // Trouve la dernière redirection d'entrée (REDIRIN ou HERE_DOC)
    last_in = NULL;
    i = 0;
    while (cmd->redir[i])
    {
        if (cmd->redir[i]->type == REDIRIN || cmd->redir[i]->type == HERE_DOC)
            last_in = cmd->redir[i];
        i++;
    }

    // Trouve la dernière redirection de sortie
    last_out = get_last_redir_of_type(cmd->redir, REDIROUT);

    // Gérer l'entrée
    if (last_in)
    {
        if (handle_input_redir(last_in->file, exec) != 0)
            return (1);
    }

    // Gérer la sortie
    if (last_out)
    {
        if (handle_output_redir(last_out->file, last_out->type == APPEND, exec) != 0)
            return (1);
    }

    return (0);
}


