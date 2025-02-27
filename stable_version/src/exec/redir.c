/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:46:39 by calberti          #+#    #+#             */
/*   Updated: 2025/02/27 04:14:12 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*get_last_redir_of_type(t_redir **redirs, int type)
{
	int		i;
	t_redir	*last;

	i = 0;
	last = NULL;
	while (redirs[i])
	{
		if (redirs[i]->type == type
			|| (type == REDIROUT && redirs[i]->type == APPEND))
			last = redirs[i];
		i++;
	}
	return (last);
}

int	create_output_files(t_redir **redirs)
{
	int	i;
	int	ret;

	i = 0;
	while (redirs[i])
	{
		ret = process_redirection(redirs[i], redirs[i]->type);
		if (ret)
			return (ret);
		i++;
	}
	return (0);
}

int	handle_input_redir(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_file_error(file, strerror(errno)));
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		printf("2 error\n");
		close(fd);
		return (print_file_error(file, strerror(errno)));
	}
	close(fd);
	return (0);
}

int	handle_output_redir(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	if (!append)
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
		return (print_file_error(file, strerror(errno)));
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (print_file_error(file, strerror(errno)));
	}
	close(fd);
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	t_redir	*last_in;
	t_redir	*last_out;
	int		i;

	if (!cmd->redir)
		return (0);
	if (create_output_files(cmd->redir) != 0)
		return (1);
	last_in = NULL;
	i = 0;
	while (cmd->redir[i])
	{
		if (cmd->redir[i]->type == REDIRIN || cmd->redir[i]->type == HERE_DOC)
			last_in = cmd->redir[i];
		i++;
	}
	last_out = get_last_redir_of_type(cmd->redir, REDIROUT);
	if (last_in && handle_input_redir(last_in->file) != 0)
		return (1);
	if (last_out)
	{
		if (handle_output_redir(last_out->file, last_out->type == APPEND) != 0)
			return (1);
	}
	return (0);
}
