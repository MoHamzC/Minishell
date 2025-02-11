/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:58 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/11 21:57:58 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

typedef enum e_builtin
{
    NOT_BUILTIN = -1,
	ECHO = 0,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	
}				t_builtin;

typedef struct s_command
{
	char			**args;         
	char			*input;         
	char			*output;        
	int				append;         
	int				builtin_value;  
	struct s_command	*next;
}				t_command;

int		ft_isspace(char c);
int		count_tokens(char *line);
char	*extract_token(char **line);
char	**tokenize(char *line);
void	free_tokens(char **tokens);

#endif
