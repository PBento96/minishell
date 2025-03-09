/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/09 11:48:28 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char **cmd_args)
{
	(void)data;
	(void)cmd_args;
	kill(getppid(), SIGTERM);
}

void	ft_export(t_data *data, char **cmd_args)
{
	(void)data;
	(void)cmd_args;
}

void	ft_unset(t_data *data, char **cmd_args)
{
	(void)data;
	(void)cmd_args;
}

void	ft_cd(t_data *data, char **cmd_args)
{
	(void)data;
	(void)cmd_args;
}
