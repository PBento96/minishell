/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:36 by joseferr          #+#    #+#             */
/*   Updated: 2025/02/20 11:27:25 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	ft_parse_redirection(char **ptr)
{
	t_token	token;

	if (**ptr == '>')
	{
		if (*(*ptr + 1) == '>')
		{
			token.type = REDIR_APPEND;
			token.value = ft_strdup(">>");
			(*ptr) += 2;
		}
		else
		{
			token.type = REDIR_OUT;
			token.value = ft_strdup(">");
			(*ptr)++;
		}
	}
	else if (**ptr == '<')
	{
		token.type = REDIR_IN;
		token.value = ft_strdup("<");
		(*ptr)++;
	}
	return (token);
}

static char	*ft_skip_whitespace(char *ptr)
{
	while (*ptr == ' ')
		ptr++;
	return (ptr);
}

static t_token	ft_parse_token(char **ptr)
{
	t_token	token;

	*ptr = ft_skip_whitespace(*ptr);
	if (**ptr == '|')
	{
		token.type = PIPE;
		token.value = ft_strdup("|");
		(*ptr)++;
	}
	else if (**ptr == '>' || **ptr == '<')
		token = ft_parse_redirection(ptr);
	else
	{
		token.type = CMD;
		token.value = ft_parse_word(ptr);
		if (ft_is_builtin(token.value))
			token.type = BUILTIN;
	}
	return (token);
}

void	ft_tokenize_input(t_data *data)
{
	t_token	token;
	char	*ptr;
	int		count;

	ft_bzero(data->commands, MAX_PIPE_COUNT * sizeof(t_command));
	ptr = data->input;
	count = 0;
	data->cmd_count = 0;
	while (*ptr)
	{
		token = ft_parse_token(&ptr);
		if (token.value && token.type != PIPE)
		{
			data->commands[data->cmd_count].tokens[count++] = token;
			data->commands[data->cmd_count].token_count = count;
		}
		if (token.type == PIPE)
		{
			data->cmd_count++;
			count = 0;
		}
		ptr = ft_skip_whitespace(ptr);
	}
}
