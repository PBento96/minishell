/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/06 20:13:00 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_echo_flag(const char *flag)
{
	const char *ch = flag + 1;
	while (*ch != '\0')
	{
		if (*ch != 'n')
			return (0);
		ch++;
	}
	return (1);
}

void	ft_echo(char **cmd_args)
{
	int newline;
	int start;
	int i;

	newline = 1;
	start = 1;
	if (cmd_args[1] != NULL && cmd_args[1][0] == '-' && is_valid_echo_flag(cmd_args[1]))
	{
		newline = 0;
		start = 2;
	}
	i = start;
	while (cmd_args[i] != NULL)
	{
		ft_printf("%s", cmd_args[i]);
		if (cmd_args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}

	if (newline)
		ft_printf("\n");
}

void	ft_pwd(t_data *data)
{
	ft_printf("%s\n", data->cwd);
}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
}

void	ft_exit(t_data *data, char **cmd_args)
{
	(void)data;
	(void)cmd_args;
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

void	ft_execute_builtin(t_data *data, char **cmd_args)
{
	char	*cmd;
	size_t	len;

	cmd = cmd_args[0];
	len = ft_strlen(cmd) + 1;
	if (!ft_strncmp(OP_EXT, cmd, len))
		kill(getppid(), SIGTERM);
	if (!ft_strncmp(OP_PWD, cmd, len))
		return ;
	if (!ft_strncmp(OP_ECHO, cmd, len))
		return ;
	if (!ft_strncmp(OP_ENV, cmd, len))
		return ;
	if (!ft_strncmp(OP_EXP, cmd, len))
		return ;
	if (!ft_strncmp(OP_UNS, cmd, len))
		return ;
	(void) data;
}
