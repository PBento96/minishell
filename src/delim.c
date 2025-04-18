/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:48:25 by pda-silv          #+#    #+#             */
/*   Updated: 2025/04/18 16:40:42 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_delim_buf(t_command *command, char *delim)
{
	char *temp;
	char *new;
	char *buffer;

	temp = ft_strdup("");
	if (!temp)
		return;
	buffer = ft_strdup(" > "RESET_COLOR);
	while (1)
	{
		new = readline(buffer);
		if (!new) // EOF condition (Ctrl+D)
		{
			if (ft_strncmp(delim, "EOF", 4) == 0)
				break;
			write(2, "minishell: warning: here-document delimited by end-of-file ", 60);
			write(2, "(wanted '", 10);
			write(2, &delim, ft_strlen(delim));
			write(2, "')\n", 4);
			// Otherwise it's just an EOF in the middle of input
			break;
		}

		if (ft_strncmp(new, delim, ft_strlen(delim) + 1) == 0)
		{
			free(new);
			break;
		}

		new = ft_strjoin(new, "\n");
		command->redir.delim_buf = ft_strjoin(temp, new);

		free(temp);
		free(new);
		temp = command->redir.delim_buf;
	}

	command->redir.delim_buf = temp;
	free(buffer);
}
