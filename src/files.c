/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:57:22 by pda-silv          #+#    #+#             */
/*   Updated: 2025/04/07 20:17:43 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_redirect_fds(t_redir *redir, const char *in, const char *out)
{
	if (redir->in_fd > 0)
		close(redir->in_fd);
	if (redir->out_fd > 1)
		close(redir->out_fd);
	if (in && *in)
	{
		redir->in_fd = open(in, O_RDONLY);
	}
	if (out && *out)
	{
		if (redir->append)
			redir->out_fd = open(out, O_CREAT | O_APPEND | O_WRONLY, FILE_PERM);
		else
			redir->out_fd = open(out, O_CREAT | O_TRUNC | O_WRONLY, FILE_PERM);
		redir->append = false;
	}
}

void	ft_close_redirect_fds(t_redir *redir)
{
	if (redir->in_fd > 0)
		close(redir->in_fd);
	if (redir->out_fd > 1)
		close(redir->out_fd);
	redir->in_fd = STDIN_FILENO;
	redir->out_fd = STDOUT_FILENO;
}
