/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:57:22 by pda-silv          #+#    #+#             */
/*   Updated: 2025/04/04 09:49:40 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_redirect_fds(t_redir *redir)
{
	redir->in_fd = -1;
	redir->out_fd = -1;
	if (redir->in_file && *redir->in_file)
	{
		redir->in_fd = open(redir->in_file, O_RDONLY);
	}
	if (redir->out_file && *redir->out_file)
	{
		if (redir->append)
			redir->out_fd = open(redir->out_file, O_CREAT | O_APPEND | O_WRONLY, 0664);
		else
			redir->out_fd = open(redir->out_file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	}
}

void	ft_close_redirect_fds(t_redir *redir)
{
	if (redir->in_fd >= 0)
		close(redir->in_fd);
	if (redir->out_fd >= 0)
		close(redir->out_fd);
}
