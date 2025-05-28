/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:37:51 by pda-silv          #+#    #+#             */
/*   Updated: 2025/04/29 22:27:42 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->cmd_count)
	{
		j = 0;
		while (j < data->commands[i].token_count)
		{
			if (data->commands[i].tokens[j].value)
				ft_free((void **)&data->commands[i].tokens[j].value);
			j++;
		}
		i++;
	}
	if (data->cmd_path)
		ft_free((void **)&data->cmd_path);
	if (data->pids)
		ft_free((void **)&data->pids);
}

void	ft_free_env_array(t_data *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return ;
	while (data->env[i])
	{
		if (data->env[i])
			ft_free((void **)&data->env[i]);
		i++;
	}
	ft_free((void **)&data->env);
}

void	ft_shutdown(t_data **data, int retval)
{
	ft_printf(C_YELLOW"\nExiting Minishell...\n"RESET_COLOR);
	if (*data)
	{
		clear_history();
		if ((*data)->input)
			ft_free((void **)&((*data)->input));
		ft_free_tokens(*data);
		if ((*data)->env)
			ft_free_array((void **)(*data)->env);
		ft_free((void **)data);
	}
	exit(retval);
}
