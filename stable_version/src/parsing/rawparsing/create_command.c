#include "parsing.h"


t_command	*new_command(void)
{
	t_command *cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->redir = NULL;
	cmd->args = NULL;
	cmd->argc = 0; 
	cmd->builtin_value = NOT_BUILTIN;
	cmd->next = NULL;
	return (cmd);
}

void	add_argument(t_command *cmd, char *arg)
{
	char	**new_args;
	int		size;

	if (!arg)
		return ;
	size = ft_strlen_tab(cmd->args);
	new_args = ft_calloc(size + 2, sizeof(char *)); 
	if (!new_args)
		return ;
	ft_memcpy(new_args, cmd->args, size * sizeof(char *)); 
	new_args[size] = ft_strdup(arg);
	free(cmd->args); 
	cmd->args = new_args;
	cmd->argc = size + 1;
}

void	add_redirection(t_command *cmd, t_token *token)
{
	t_redir	**new_redir;
	int		size;

	size = 0;
	if (!token)
		return ;
	while (cmd->redir && cmd->redir[size])
		size++;
	new_redir = ft_calloc(size + 2, sizeof(t_redir *));
	if (cmd->redir)
		ft_memcpy(new_redir, cmd->redir, size * sizeof(t_redir *));

	new_redir[size] = malloc(sizeof(t_redir));
	if (!new_redir[size])
		return ;
	new_redir[size]->file = ft_strdup(token->value);
	new_redir[size]->type = token->type;
	new_redir[size]->append = (token->type == APPEND);
	free(cmd->redir);
	cmd->redir = new_redir;
}

void init_parse(t_command **cmds, t_command **current)
{
	*cmds = new_command();
	*current = *cmds;
}

t_command	*parse_tokens(t_token **tokens)
{
	t_command	*cmds;
	t_command	*current;
	int			i;

	init_parse(&cmds, &current);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == WORD)
			add_argument(current, tokens[i]->value);
		else if (is_redir_token(tokens[i]->type))
			add_redirection(current, tokens[i]);
		else if (tokens[i]->type == PIPE)
		{
			if (current->args && current->args[0])
				current->builtin_value = whichbuiltin(current->args[0]);
			current->next = new_command();
			if (!current->next)
				return (cmds);
			current = current->next;
		}
		i++;
	}
	if (current->args && current->args[0])
		current->builtin_value = whichbuiltin(current->args[0]);
	return (cmds);
}

t_token *create_token(char *value, t_cmd_type type, t_word_type quote)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->value = strdup(value);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
    token->type = type;
    token->quote = quote;
    return (token);
}

// int main(void)
// {
//     t_token **tokens;
//     t_command *commands;
//     t_command *cmd;
//     int i;
//     int cmd_no;

//     tokens = malloc(sizeof(t_token *) * 11);
//     if (!tokens)
//         return (1);
	
// 	// tokens[0] = create_token("echo", WORD, NO_QUOTE);
// 	// tokens[1] = create_token("hello", WORD, NO_QUOTE);
// 	// tokens[2] = create_token("world", WORD, NO_QUOTE);
// 	// tokens[3] = create_token("|", PIPE, NO_QUOTE);
// 	// tokens[4] = create_token("pwd", WORD, NO_QUOTE);
// 	// tokens[5] = NULL; 
// 	// tokens[6] = NULL;
// 		tokens[0] = create_token("echo", WORD, NO_QUOTE);
//     tokens[1] = create_token("hello", WORD, NO_QUOTE);
//     tokens[2] = create_token("world", WORD, NO_QUOTE);
//     tokens[3] = create_token("|", PIPE, NO_QUOTE);
//     tokens[4] = create_token("pwd", WORD, NO_QUOTE);
//     tokens[5] = create_token("hello", WORD, NO_QUOTE);
//     tokens[6] = create_token("output.txt", REDIROUT, NO_QUOTE);
// 	tokens[7] = create_token("output.txt", APPEND, NO_QUOTE);
// 	tokens[8] = create_token("output.txt", REDIRIN, NO_QUOTE);
// 	tokens[9] = create_token("output.txt", REDIROUT, NO_QUOTE);
// 	tokens[10] = NULL;
// 	// printf("tokens[0] = %s\n", tokens[0]->value);
// 	// printf("tokens[1] = %s\n", tokens[1]->value);
// 	// printf("tokens[2] = %s\n", tokens[2]->value);
//     // tokens[0] = create_token("echo", WORD, NO_QUOTE);
//     // tokens[1] = create_token("hello", WORD, NO_QUOTE);
//     // tokens[2] = create_token("world", WORD, NO_QUOTE);
//     // tokens[3] = create_token("|", PIPE, NO_QUOTE);
//     // tokens[4] = create_token("pwd", WORD, NO_QUOTE);
//     // tokens[5] = create_token("hello", WORD, NO_QUOTE);
//     // tokens[6] = create_token("output.txt", REDIROUT, NO_QUOTE);
// 	// tokens[7] = create_token("output.txt", APPEND, NO_QUOTE);
// 	// tokens[8] = create_token("output.txt", REDIRIN, NO_QUOTE);
// 	// tokens[9] = create_token("output.txt", REDIROUT, NO_QUOTE);
//     // tokens[10] = NULL;
	
// 	printf("tokens[0] = %s\n", tokens[0]->value);
//     commands = parse_tokens(tokens);


//     cmd = commands;
//     cmd_no = 1;
//     while (cmd != NULL)
//     {
//         printf("cmd %d:\n", cmd_no);

//         i = 0;
//         while (cmd->args && cmd->args[i])
//         {
//             printf("  Arg[%d] : %s\n", i, cmd->args[i]);
//             i++;
//         }
//         printf("  Builtin value : %d\n", cmd->builtin_value);
//         printf("  Argc          : %d\n", cmd->argc);

//         i = 0;
//        while (cmd->redir && cmd->redir[i])
//         {
//             printf("  Redirection[%d] : file = %s, type = %d, append = %d\n", 
//                    i, cmd->redir[i]->file, cmd->redir[i]->type, cmd->redir[i]->append);
//             i++;
//         }
//         printf("\n");
//         cmd = cmd->next;
//         cmd_no++;
//     }
//     return (0);
// }



//gcc -I../../../include create_command.c whichbuiltin.c -lft -L../../../include/libft


// gcc create_command.c whichbuiltin.c -L../../../include/libft -lft
