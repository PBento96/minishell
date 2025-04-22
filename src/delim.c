/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:48:25 by pda-silv          #+#    #+#             */
/*   Updated: 2025/04/22 20:06:24 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*   Handles here-document (<<) input processing                             */
/*   Reads input until delimiter is encountered                              */
/*   Stores the collected input in the command structure                     */
/*   Handles special cases like EOF and error conditions                     */
/* ************************************************************************** */
static void	ft_process_eof(char *delim)
{
	write(2, "minishell: warning: here-document delimited by end-of-file ", 60);
	write(2, "(wanted '", 10);
	write(2, delim, ft_strlen(delim));
	write(2, "')\n", 4);
}

static int	ft_check_delimiter(char *new, char *delim)
{
	if (ft_strncmp(new, delim, ft_strlen(delim) + 1) == 0)
	{
		free(new);
		return (1);
	}
	return (0);
}

static void	ft_append_line(t_command *command, char **temp, char *new)
{
	char	*with_newline;
	char	*combined;

	with_newline = ft_strjoin(new, "\n");
	combined = ft_strjoin(*temp, with_newline);
	free(*temp);
	free(with_newline);
	*temp = combined;
}

void	ft_get_delim_buf(t_command *command, char *delim)
{
	char	*temp;
	char	*new;
	char	*buffer;

	temp = ft_strdup("");
	if (!temp)
		return ;
	buffer = ft_strdup(" > "RESET_COLOR);
	while (1)
	{
		new = readline(buffer);
		if (!new)
		{
			if (ft_strncmp(delim, "EOF", 4) != 0)
				ft_process_eof(delim);
			break ;
		}
		if (ft_check_delimiter(new, delim))
			break ;
		ft_append_line(command, &temp, new);
		free(new);
	}
	command->redir.delim_buf = temp;
	free(buffer);
}
