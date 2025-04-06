/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:36 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/05 13:55:36 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd(t_data *data, char	**cmd_args)
{
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
}

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
		if (*(*ptr + 1) == '<')
		{
			token.type = REDIR_DELIM;
			token.value = ft_strdup("<<");
			(*ptr) += 2;
		}
		else
		{
			token.type = REDIR_IN;
			token.value = ft_strdup("<");
			(*ptr)++;
		}
	}
	return (token);
}

static char	*ft_skip_whitespace(char *ptr)
{
	while (*ptr == ' ')
		ptr++;
	return (ptr);
}

static t_token ft_parse_token(char **ptr, t_data *data)
{
	t_token token;

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
		token.value = ft_parse_word(ptr, data);
		if (ft_is_builtin(token.value))
			token.type = BUILTIN;
	}
	return token;
}

static int ft_is_quote_balanced(const char *str)
{
	int single_quotes = 0;
	int double_quotes = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\'' && !(double_quotes % 2))
			single_quotes++;
		else if (str[i] == '\"' && !(single_quotes % 2))
			double_quotes++;
		i++;
	}

	return ((single_quotes % 2 == 0) && (double_quotes % 2 == 0));
}

static int ft_handle_quotes_in_input(t_data *data)
{
	if (!ft_is_quote_balanced(data->input))
	{
		ft_putendl_fd("minishell: unclosed quotes detected", 2);
		data->status = 1;
		return (0);
	}
	return (1);
}

void ft_tokenize_input(t_data *data)
{
	t_token token;
	char *ptr;
	int count;

	ft_bzero(data->commands, MAX_PIPE_COUNT * sizeof(t_command));
	if (!ft_handle_quotes_in_input(data))
		return;
	ptr = data->input;
	count = 0;
	data->cmd_count = 0;
	while (*ptr)
	{
		token = ft_parse_token(&ptr, data);
		if (token.value && token.type != PIPE)
		{
			data->commands[data->cmd_count].tokens[count++] = token;
			data->commands[data->cmd_count].token_count = count;
			data->commands[data->cmd_count].redir.in_fd = 0;
			data->commands[data->cmd_count].redir.out_fd = 1;
			ft_printf("Token Value: %s, Token Type:%d\n",token.value,token.type );
		}
		if (token.type == PIPE)
		{
			data->cmd_count++;
			count = 0;
		}
		ptr = ft_skip_whitespace(ptr);
	}
}
