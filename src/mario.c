/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:30:00 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/27 12:04:48 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_children(t_data *data, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	if (pids)
	{
		while (i <= data->cmd_count)
		{
			if (pids[i] > 0)
			{
				waitpid(pids[i], &status, 0);
				if (i == data->cmd_count)
				{
					if (status & 0x7F)
						data->status = 128 + (status & 0x7F);
					else
						data->status = (status >> 8) & 0xFF;
				}
			}
			i++;
		}
		free(pids);
	}
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
}

/* ************************************************************************** */
/*                                                                            */
/*   Manages pipe and redirection setup for command execution                */
/*   Handles input from heredocs, files, or previous pipes                   */
/*   Sets up output redirections to files or pipes                           */
/*   Ensures proper synchronization of heredoc processing                    */
/* ************************************************************************** */
void	ft_handle_heredoc(t_data *data, t_command cmd, int cmd_index)
{
	int	heredoc_pipe[2];

	ft_get_delim_buf(&cmd, cmd.redir.delim);
	if (cmd_index < data->cmd_count)
	{
		write(data->heredoc_sync[cmd_index][1], "", 1);
		close(data->heredoc_sync[cmd_index][1]);
	}
	if (cmd.redir.delim_buf)
	{
		if (pipe(heredoc_pipe) == -1)
		{
			perror("pipe");
			return ;
		}
		write(heredoc_pipe[1], cmd.redir.delim_buf,
			ft_strlen(cmd.redir.delim_buf));
		close(heredoc_pipe[1]);
		dup2(heredoc_pipe[0], STDIN_FILENO);
		close(heredoc_pipe[0]);
	}
}

void	ft_setup_pipes(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	ft_pipe_error(t_data *data, char **cmd_args)
{
	perror("fork");
	ft_free_cmd(data, cmd_args);
	return ;
}
