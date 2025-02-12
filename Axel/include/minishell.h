/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:09:04 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/12 09:27:17 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# include <stdbool.h>

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

typedef enum token_type
{
	WORD,
	REDIRIN,
	REDIROUT,
	APPEND,
	HERE_DOC,	
	PIPE,
}	t_cmd_type;

typedef enum word_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_word_type;

typedef struct s_token
{
	char		*value;
	t_cmd_type	type;
	t_word_type	quote;
}	t_token;

typedef struct s_redir
{
	char	*file;
	int		type;
	bool	append;
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
	int					builtin_value;
	struct s_command	*next;
}				t_command;

typedef struct s_shell
{
	t_command	*cmds;
	t_env		*env;
}	t_shell;

void	free_tokens(t_token **tokens);
t_env	*ft_envlst_new(char *key, char *value);
void	ft_envlst_add_back(t_env **lst, t_env *new);
t_env	*init_env(char **envp);
void	free_env(t_env *env);



//builtins

void ft_env(t_env *envp);