/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:57:22 by pda-silv          #+#    #+#             */
/*   Updated: 2025/04/07 20:36:56 by joseferr         ###   ########.fr       */
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
			redir->out_fd = open(out, O_CREAT | O_APPEND | O_WRONLY, 0664);
		else
			redir->out_fd = open(out, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		redir->append = false;
	}
	if(redir->in_fd < 0 || redir->out_fd < 0)
		perror("FDs");
}

void	ft_close_redirect_fds(t_redir *redir)
{
	if (redir->in_fd > 0)
		close(redir->in_fd);
	if (redir->out_fd > 1)
		close(redir->out_fd);

	// Reset the file descriptors to their default values
	redir->in_fd = 0;  // STDIN
	redir->out_fd = 1; // STDOUT
}
