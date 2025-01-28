/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:36 by joseferr          #+#    #+#             */
/*   Updated: 2025/01/28 11:59:24 by pda-silv         ###   ########.fr       */
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

t_token	*ft_tokenize_input(char *input, int *token_count)
{
	t_token	*tokens;
	t_token	token;
	char	*ptr;
	int		count;

	tokens = malloc(sizeof(t_token) * MAX_TOKENS);
	ptr = input;
	count = 0;
	while (*ptr)
	{
		token = ft_parse_token(&ptr);
		if (token.value != NULL)
			tokens[count++] = token;
		ptr = ft_skip_whitespace(ptr);
	}
	tokens[count] = (t_token){0, NULL};
	*token_count = count;
	return (tokens);
}
