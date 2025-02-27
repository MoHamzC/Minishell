/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:33:10 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/27 02:51:52 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (print_file_error(redir->file, strerror(errno)));
	close(fd);
	return (0);
}

int	handle_redirout(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (print_file_error(redir->file, strerror(errno)));
	close(fd);
	return (0);
}

int	handle_redirin(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		return (print_file_error(redir->file, strerror(errno)));
	close(fd);
	return (0);
}

int	process_redirection(t_redir *redir, int type)
{
	if (type == APPEND)
		return (handle_append(redir));
	else if (type == REDIROUT)
		return (handle_redirout(redir));
	else if (type == REDIRIN)
		return (handle_redirin(redir));
	return (0);
}
