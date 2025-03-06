/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/05 14:33:27 by pda-silv         ###   ########.fr       */
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
	if (strcmp(command, OP_PWD) == 0
		|| strcmp(command, OP_ENV) == 0
		|| strcmp(command, OP_ECHO) == 0
		|| strcmp(command, OP_EXT) == 0
		|| strcmp(command, OP_EXP) == 0
		|| strcmp(command, OP_UNS) == 0)
		return (true);
	return (false);
}
