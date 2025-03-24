/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:30:00 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/24 10:22:46 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_wait_children(t_data *data, pid_t *pids)
{
    int i;
    int status;

    i = 0;
    while (i <= data->cmd_count)
    {
        // Only wait for valid pids (greater than 0)
        if (pids[i] > 0)
        {
            waitpid(pids[i], &status, 0);
        }
        i++;
    }
    // Free the pids array after waiting
    free(pids);
    data->pids = NULL;
}

void	ft_handle_pipes(t_data *data, int pipefd[2], int command)
{
	if (data->prev_pipe != -1)
	{
		dup2(data->prev_pipe, STDIN_FILENO);
		close(data->prev_pipe);
	}
	if (command < data->cmd_count)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (command < data->cmd_count)
		close(pipefd[0]);
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
