/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:23:01 by joseferr          #+#    #+#             */
/*   Updated: 2025/02/20 11:26:17 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setup_pipes(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	ft_pipe_error(t_data *data, char	**cmd_args)
{
	perror("fork");
	ft_free_cmd(data, cmd_args);
	return ;
}

void	ft_free_cmd(t_data *data, char	**cmd_args)
{
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
}
