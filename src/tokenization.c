/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:36 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/22 21:26:11 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd(t_data *data, char	**cmd_args)
{
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
}

static void	ft_add_token_to_command(t_data *data, t_token token, int *count)
{
	data->commands[data->cmd_count].tokens[(*count)++] = token;
	data->commands[data->cmd_count].token_count = *count;
	data->commands[data->cmd_count].redir.in_fd = 0;
	data->commands[data->cmd_count].redir.out_fd = 1;
	ft_printf("Token Value: %s, Token Type:%d\n", token.value, token.type);
}

static void	ft_handle_pipe_token(t_data *data, int *count)
{
	data->cmd_count++;
	*count = 0;
}

char	*ft_skip_whitespace(char *ptr)
{
	while (*ptr == ' ')
		ptr++;
	return (ptr);
}

void	ft_tokenize_input(t_data *data)
{
	t_token	token;
	char	*ptr;
	int		count;

	ft_bzero(data->commands, MAX_PIPE_COUNT * sizeof(t_command));
	if (!ft_handle_quotes_in_input(data))
		return ;
	ptr = data->input;
	count = 0;
	data->cmd_count = 0;
	while (*ptr)
	{
		token = ft_parse_token(&ptr, data);
		if (token.value && token.type != PIPE)
			ft_add_token_to_command(data, token, &count);
		if (token.type == PIPE)
			ft_handle_pipe_token(data, &count);
		ptr = ft_skip_whitespace(ptr);
	}
}
