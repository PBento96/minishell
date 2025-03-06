/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/03 14:27:23 by joseferr         ###   ########.fr       */
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

char	**ft_tokens_to_args(t_token *tokens, int token_count)
{
	char	**args;
	int		i;

	args = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		args[i] = ft_strdup(tokens[i].value);
		i++;
	}
	args[i] = NULL;
	return (args);
}

bool	ft_is_builtin(const char *command)
{
	if (strcmp(command, OP_PWD) == 0
		|| strcmp(command, OP_ENV) == 0
		|| strcmp(command, OP_ECHO) == 0
		|| strcmp(command, OP_EXT) == 0
		|| strcmp(command, OP_EXP) == 0
		|| strcmp(command, OP_UNS) == 0)
		return (true);
	return (false);
}
