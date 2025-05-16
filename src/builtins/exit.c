/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/16 13:56:11 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_arg(char *arg, int *exit_value)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			neg = 1;
		i++;
	}
	*exit_value = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		*exit_value = *exit_value * 10 + (arg[i] - '0');
		i++;
	}
	if (neg)
		*exit_value = -*exit_value;
	return (1);
}

static void	handle_exit_error(char *arg)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	exit(2);
}

/*********************/
/*PWD Builtin Command*/
/*********************/
void	ft_exit(t_data *data, char **cmd_args)
{
	int	exit_status;

	write(1, "exit\n", 5);
	exit_status = 0;
	if (!cmd_args[1] && data->piped == 0)
	{
		ft_free_cmd(data,cmd_args);
		ft_cleanup_execution(data);
		ft_shutdown(&data, (unsigned char)exit_status);
	}
	if (!is_numeric_arg(cmd_args[1], &exit_status))
		handle_exit_error(cmd_args[1]);
	if (cmd_args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		data->status = 1;
		return ;
	}
}
