/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:58 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 00:28:11 by mochamsa         ###   ########.fr       */
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

typedef struct s_redir
{
	char	*file;
	int		type;
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_command
{
	t_redir				**redir;
	char				**args;
	int					append;
	int					builtin_value;
	struct s_command	*next;
}				t_command;

typedef struct s_shell
{
	t_command	*cmds;
	t_env		*env;
}	t_shell;

int		ft_isspace(char c);
int		count_tokens(char *line);
char	*extract_token(char **line);
char	**tokenize(char *line, t_env *env);
void	free_tokens(char **tokens);

char	*expand_variables(char *str, t_env *env);

t_env	*ft_envlst_new(char *key, char *value);
void	ft_envlst_add_back(t_env **lst, t_env *new);
t_env	*init_env(char **envp);
void	free_env(t_env *env);

#endif
