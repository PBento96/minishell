/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/01/29 18:38:11 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_word(char **ptr)
{
	char	*start;
	char	*word;

	start = *ptr;
	while (**ptr && !ft_isspace(**ptr) && **ptr != OP_PIPE
		&& **ptr != OP_REDIRECT_OUT && **ptr != OP_REDIRECT_IN)
		(*ptr)++;
	word = ft_substr(start, 0, *ptr - start);
	return (word);
}

bool	ft_is_builtin(const char *command)
{
	int	is;

	is = 0;
	if (strcmp(command, OP_PWD) == 0)
		is = 1;
	else if (strcmp(command, OP_ENV) == 0)
		is = 1;
	else if (strcmp(command, OP_ECHO) == 0)
		is = 1;
	else if (strcmp(command, OP_EXT) == 0)
		is = 1;
	else if (strcmp(command, OP_EXP) == 0)
		is = 1;
	else if (strcmp(command, OP_UNS) == 0)
		is = 1;
	else
		is = 0;
	return (is);
}

t_command	*ft_parse_tokens(t_token *tokens, int token_count, int *cmd_count)
{
	t_command	*commands;
	int			cmd_index;
	int			i;

	commands = ft_calloc(MAX_PIPE_COUNT, sizeof(t_command));
	cmd_index = 0;
	i = 0;
	commands[cmd_index].tokens = ft_calloc(MAX_TOKENS, sizeof(t_token));
	commands[cmd_index].token_count = 0;
	while (i < token_count)
	{
		if (tokens[i].type == PIPE)
		{
			commands[++cmd_index].tokens = ft_calloc(MAX_TOKENS, sizeof(t_token));
			commands[cmd_index].token_count = 0;
		}
		else
			commands[cmd_index].tokens[commands[cmd_index]
				.token_count++] = tokens[i];
		i++;
	}
	*cmd_count = cmd_index + 1;
	return (commands);
}

void	ft_free_commands(t_command *commands, int command_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < command_count)
	{
		while (j < commands[i].token_count)
		{
			ft_free((void **)&commands[i].tokens[j].value);
			j++;
		}
		ft_free((void **)&commands[i].tokens);
		i++;
	}
	free((void **)&commands);
}

/* The Journey of Tokens starts here */
t_command	*ft_parse_input(char *input, int *command_count)
{
	int			token_count;
	t_token		*tokens;
	t_command	*commands;

	tokens = ft_tokenize_input(input, &token_count);
	commands = ft_parse_tokens(tokens, token_count, command_count);
	ft_free((void **)&tokens);
	return (commands);
}
